/* Original:
     https://media.pragprog.com/titles/reasonml/code/interop/server/src/Stats.re
   */
module Error = {
  [@bs.deriving abstract]
  type t = {
    [@bs.as "type"]
    type_: string,
    code: string,
    message: string,
    row: int,
  };
};

module Meta = {
  [@bs.deriving abstract]
  type t = {
    delimiter: string,
    linebreak: string,
    aborted: bool,
    fields: array(string),
    truncated: bool,
  };
};

module Results = {
  [@bs.deriving abstract]
  type t = {
    data: array(array(string)),
    errors: array(Error.t),
    meta: array(Meta.t),
  };
};

/* import papaparse.parse */
[@bs.val] [@bs.module "papaparse"]
external parseString: string => Results.t = "parse";

let maybeIntFromString: string => option(int) =
  str =>
    switch (int_of_string(str)) {
    | anInt => Some(anInt)
    | exception (Failure("int_of_string")) => None
    };

let map2: (option('a), option('b), ('a, 'b) => 'c) => option('c) =
  (maybe1, maybe2, f2) =>
    switch (maybe1, maybe2) {
    | (Some(arg1), Some(arg2)) => Some(f2(arg1, arg2))
    | (_, _) => None
    };

let maybeOrderFromItems: array(string) => option(Order.t) =
  items =>
    map2(
      Some(Order.makeEmpty()),
      maybeIntFromString(items[0]),
      Order.quantitySet,
    )
    ->map2(Shirts.Size.fromString(items[1]), Order.sizeSet)
    ->map2(Shirts.Color.fromString(items[2]), Order.colorSet)
    ->map2(Shirts.Pattern.fromString(items[3]), Order.patternSet)
    ->map2(Shirts.Collar.fromString(items[4]), Order.collarSet)
    ->map2(Shirts.Sleeve.fromString(items[5]), Order.sleeveSet)
    ->map2(Shirts.Cuff.fromString(items[6]), Order.cuffSet);

let lineReducer: (list(Order.t), array(string)) => list(Order.t) =
  (orders, items) =>
    Belt.Array.length(items) != 7 ?
      orders :
      maybeOrderFromItems(items)
      ->Belt.Option.mapWithDefault(orders, order => [order, ...orders]);

let makeObject: (string, Belt.Map.t('k, int, 'id), 'k => string) => Js.Json.t =
  (title, counts, toString) => {
    let (choices, totals) =
      Belt.Map.toArray(counts)
      ->Belt.Array.map(((key, count)) => (toString(key), count))
      ->Belt.Array.unzip;

    Json.Encode.object_([
      ("title", Json.Encode.string(title)),
      ("choices", Json.Encode.stringArray(choices)),
      ("totals", Json.Encode.array(Json.Encode.int, totals)),
    ]);
  };

let makeCounts = /* (Belt.Map.id('k, int), Order.t => 'k, list(Order.t)) =>
  Belt.Map.t('k, int, 'id) */
    (comparator, getOrderProperty, orders) => {
  let counter:
    (Belt.Map.t('k, int, 'id), Order.t) => Belt.Map.t('k, int, 'id) =
    (counts, order) => {
      let property = getOrderProperty(order);
      let total = Belt.Map.getWithDefault(counts, property, 0);
      Belt.Map.set(counts, property, total + order.quantity);
    };
  let emptyCounts = Belt.Map.make(~id=comparator);
  Belt.List.reduce(orders, emptyCounts, counter);
};

let statisticsToJson: (string, list(Order.t)) => Js.Json.t =
  (choice, orders) =>
    switch (choice) {
    | "size" =>
      makeObject(
        "Size",
        makeCounts((module Shirts.Size.Comparator), Order.sizeGet, orders),
        Shirts.Size.toString,
      )
    | "color" =>
      makeObject(
        "Color",
        makeCounts((module Shirts.Color.Comparator), Order.colorGet, orders),
        Shirts.Color.toString,
      )
    | "pattern" =>
      makeObject(
        "Pattern",
        makeCounts(
          (module Shirts.Pattern.Comparator),
          Order.patternGet,
          orders,
        ),
        Shirts.Pattern.toString,
      )
    | "sleeve" =>
      makeObject(
        "Sleeve",
        makeCounts(
          (module Shirts.Sleeve.Comparator),
          Order.sleeveGet,
          orders,
        ),
        Shirts.Sleeve.toString,
      )
    | "collar" =>
      makeObject(
        "Collar",
        makeCounts(
          (module Shirts.Collar.Comparator),
          Order.collarGet,
          orders,
        ),
        Shirts.Collar.toString,
      )
    | "cuff" =>
      makeObject(
        "Cuff",
        makeCounts((module Shirts.Cuff.Comparator), Order.cuffGet, orders),
        Shirts.Cuff.toString,
      )
    | _ =>
      makeObject(
        "Error",
        Belt.Map.make(~id=(module Shirts.Size.Comparator)),
        Shirts.Size.toString,
      )
    };

let processFile: (string, string) => Js.Json.t =
  (inFileName, choice) => {
    let fileContents = Node.Fs.readFileAsUtf8Sync(inFileName);
    let lines =
      parseString(fileContents)->Results.dataGet->Belt.Array.sliceToEnd(1);
    let orders = Belt.Array.reduce(lines, [], lineReducer);
    statisticsToJson(choice, orders);
  };
