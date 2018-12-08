/* file: src/AppJson.re

     Excerpted from:
     https://media.pragprog.com/titles/reasonml/code/reason-react/shirt-storage/src/Shirt.re
     https://media.pragprog.com/titles/reasonml/code/reason-react/shirt-storage/src/OrderForm.re
   */
module E = Json.Encode;
module D = Json.Decode;

exception InvalidSize;

let decodeSize: string => Shirt.Size.t =
  value =>
    switch (Shirt.Size.fromString(value)) {
    | Some(size) => size
    | None => raise(InvalidSize)
    };

exception InvalidSleeve;

let decodeSleeve: string => Shirt.Sleeve.t =
  value =>
    switch (Shirt.Sleeve.fromString(value)) {
    | Some(sleeve) => sleeve
    | None => raise(InvalidSleeve)
    };

exception InvalidColor;

let decodeColor: string => Shirt.Color.t =
  value =>
    switch (Shirt.Color.fromString(value)) {
    | Some(color) => color
    | None => raise(InvalidColor)
    };

exception InvalidPattern;

let decodePattern: string => Shirt.Pattern.t =
  value =>
    switch (Shirt.Pattern.fromString(value)) {
    | Some(pattern) => pattern
    | None => raise(InvalidPattern)
    };

let encodeOrder: Order.t => Js.Json.t =
  order =>
    E.object_([
      ("orderNumber", E.int(order.orderNumber)),
      ("quantity", E.int(order.quantity)),
      ("size", Shirt.Size.toString(order.size)->E.string),
      ("sleeve", Shirt.Sleeve.toString(order.sleeve)->E.string),
      ("color", Shirt.Color.toString(order.color)->E.string),
      ("pattern", Shirt.Pattern.toString(order.pattern)->E.string),
    ]);

let decodeOrder: Js.Json.t => Order.t =
  json => {
    orderNumber: D.field("orderNumber", D.int, json),
    quantity: D.field("quantity", D.int, json),
    size: D.field("size", D.string, json)->decodeSize,
    sleeve: D.field("sleeve", D.string, json)->decodeSleeve,
    color: D.field("color", D.string, json)->decodeColor,
    pattern: D.field("pattern", D.string, json)->decodePattern,
  };

let encodeEditInfo: State.editInfo => Js.Json.t =
  info =>
    E.object_([
      ("qty", E.string(info.qty)),
      ("size", E.string(info.size)),
      ("sleeve", E.string(info.sleeve)),
      ("color", E.string(info.color)),
      ("pattern", E.string(info.pattern)),
      ("actionLabel", E.string(info.actionLabel)),
    ]);

let decodeEditInfo: Js.Json.t => State.editInfo =
  json => {
    qty: D.field("qty", D.string, json),
    size: D.field("size", D.string, json),
    sleeve: D.field("sleeve", D.string, json),
    color: D.field("color", D.string, json),
    pattern: D.field("pattern", D.string, json),
    actionLabel: D.field("actionLabel", D.string, json),
  };

let encodeOrderInfo: State.orderInfo => Js.Json.t =
  info =>
    E.object_([
      ("orderNumber", E.int(info.orderNumber)),
      (
        "editNumber",
        switch (info.editNumber) {
        | Some(number) => E.int(number)
        | None => E.null
        },
      ),
    ]);

let decodeOrderInfo: Js.Json.t => State.orderInfo =
  json => {
    orderNumber: D.field("orderNumber", D.int, json),
    editNumber: D.optional(D.field("editNumber", D.int), json),
  };

let encodeState: State.t => Js.Json.t =
  s =>
    Json.Encode.object_([
      ("edit", encodeEditInfo(s.edit)),
      ("current", encodeOrderInfo(s.current)),
      ("orders", E.array(encodeOrder, s.orders)),
      (
        "error",
        switch (s.error) {
        | Some(message) => E.string(message)
        | None => E.null
        },
      ),
    ]);

let decodeState: Js.Json.t => State.t =
  json => {
    edit: D.field("edit", decodeEditInfo, json),
    current: D.field("current", decodeOrderInfo, json),
    orders: D.field("orders", D.array(decodeOrder), json),
    error: D.optional(D.field("errorText", Json.Decode.string), json),
  };
