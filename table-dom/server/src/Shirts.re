/* Original:
     https://media.pragprog.com/titles/reasonml/code/records/shirt-stats/src/Stats.re
   */

module Size = {
  type t =
    | XSmall(int)
    | Small
    | Medium
    | Large
    | XLarge(int);

  type size = t;

  let toString: t => string =
    fun
    | XSmall(n) => Js.String.repeat(n, "X") ++ "S"
    | Small => "S"
    | Medium => "M"
    | Large => "L"
    | XLarge(n) => Js.String.repeat(n, "X") ++ "L";

  let fromString: string => option(t) =
    str =>
      switch (Js.String.toUpperCase(str)) {
      | "S" => Some(Small)
      | "M" => Some(Medium)
      | "L" => Some(Large)
      | s when Js.Re.test(s, [%bs.re {|/^X+S$/|}]) =>
        Some(XSmall(Js.String.length(s) - 1))
      | s when Js.Re.test(s, [%bs.re {|/^X+L$/|}]) =>
        Some(XLarge(Js.String.length(s) - 1))
      | _ => None
      };

  let toOrdinal: t => int =
    fun
    | Small => 0
    | Medium => 1
    | Large => 2
    | XLarge(n) => 2 + n
    | XSmall(n) => - n;

  module Comparator =
    Belt.Id.MakeComparable({
      type t = size;
      let cmp = (lhs, rhs) => compare(toOrdinal(lhs), toOrdinal(rhs));
    });
};

module Sleeve = {
  type t =
    | Short
    | Long
    | XLong;

  type sleeve = t;

  let toString: t => string =
    fun
    | Short => "short"
    | Long => "long"
    | XLong => "xlong";

  let fromString: string => option(t) =
    s =>
      switch (Js.String.toLowerCase(s)) {
      | "short" => Some(Short)
      | "long" => Some(Long)
      | "xlong" => Some(XLong)
      | _ => None
      };

  module Comparator =
    Belt.Id.MakeComparable({
      type t = sleeve;
      let cmp = compare;
    });
};

module Color = {
  type t =
    | White
    | Blue
    | Red
    | Green
    | Brown;

  type color = t;

  let toString: t => string =
    fun
    | White => "white"
    | Blue => "blue"
    | Red => "red"
    | Green => "green"
    | Brown => "brown";

  let fromString: string => option(t) =
    s =>
      switch (Js.String.toLowerCase(s)) {
      | "white" => Some(White)
      | "blue" => Some(Blue)
      | "red" => Some(Red)
      | "green" => Some(Green)
      | "brown" => Some(Brown)
      | _ => None
      };

  module Comparator =
    Belt.Id.MakeComparable({
      type t = color;
      let cmp = compare;
    });
};

module Pattern = {
  type t =
    | Solid
    | Pinstripe
    | Check;

  type pattern = t;

  let toString: t => string =
    fun
    | Solid => "solid"
    | Pinstripe => "pinstripe"
    | Check => "check";

  let fromString: string => option(t) =
    s =>
      switch (Js.String.toLowerCase(s)) {
      | "solid" => Some(Solid)
      | "pinstripe" => Some(Pinstripe)
      | "check" => Some(Check)
      | _ => None
      };

  module Comparator =
    Belt.Id.MakeComparable({
      type t = pattern;
      let cmp = compare;
    });
};

module Cuff = {
  type t =
    | Button
    | French
    | NoCuff;

  type cuff = t;

  let toString: t => string =
    fun
    | Button => "button"
    | French => "french"
    | NoCuff => "none";

  let fromString: string => option(t) =
    s =>
      switch (Js.String.toLowerCase(s)) {
      | "button" => Some(Button)
      | "french" => Some(French)
      | ""
      | "none"
      | "nocuff" => Some(NoCuff)
      | _ => None
      };

  module Comparator =
    Belt.Id.MakeComparable({
      type t = cuff;
      let cmp = compare;
    });
};

module Collar = {
  type t =
    | Button
    | Straight
    | Spread;

  type collar = t;

  let toString: t => string =
    fun
    | Button => "button"
    | Straight => "straight"
    | Spread => "spread";

  let fromString: string => option(t) =
    s =>
      switch (Js.String.toLowerCase(s)) {
      | "button" => Some(Button)
      | "straight" => Some(Straight)
      | "spread" => Some(Spread)
      | _ => None
      };

  module Comparator =
    Belt.Id.MakeComparable({
      type t = collar;
      let cmp = compare;
    });
};
