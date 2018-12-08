/* file: src/Shirt.re

     Original:
     https://media.pragprog.com/titles/reasonml/code/reason-react/shirt-storage/src/Shirt.re

   */
module Size = {
  type t =
    | XSmall(int)
    | Small
    | Medium
    | Large
    | XLarge(int);

  let toString = (size: t): string =>
    switch (size) {
    | XSmall(n) => String.make(n, 'X') ++ "S"
    | Small => "S"
    | Medium => "M"
    | Large => "L"
    | XLarge(n) => String.make(n, 'X') ++ "L"
    };

  let fromString = (str: string): option(t) =>
    switch (Js.String.toUpperCase(str)) {
    | "S" => Some(Small)
    | "M" => Some(Medium)
    | "L" => Some(Large)
    | s when Js.Re.test(s, [%re "/^X+S$/"]) =>
      Some(XSmall(String.length(s) - 1))
    | s when Js.Re.test(s, [%re "/^X+L$/"]) =>
      Some(XLarge(String.length(s) - 1))
    | _ => None
    };
};

module Sleeve = {
  type t =
    | Short
    | Long
    | XLong; /* for tall people */

  let toString = (sleeve: t): string =>
    switch (sleeve) {
    | Short => "Short sleeve"
    | Long => "Long sleeve"
    | XLong => "Extra-long sleeve"
    };

  let fromString = (str: string): option(t) =>
    switch (Js.String.toLowerCase(str)) {
    | "short"
    | "short sleeve" => Some(Short)
    | "long"
    | "long sleeve" => Some(Long)
    | "extra-long"
    | "extra-long sleeve"
    | "xlong"
    | "xlong sleeve" => Some(XLong)
    | _ => None
    };
};

module Color = {
  type t =
    | White
    | Blue
    | Red
    | Green
    | Brown;

  let toString = (color: t): string =>
    switch (color) {
    | White => "White"
    | Blue => "Blue"
    | Red => "Red"
    | Green => "Green"
    | Brown => "Brown"
    };

  let fromString = (s: string): option(t) =>
    switch (Js.String.toLowerCase(s)) {
    | "white" => Some(White)
    | "blue" => Some(Blue)
    | "red" => Some(Red)
    | "green" => Some(Green)
    | "brown" => Some(Brown)
    | _ => None
    };
};

module Pattern = {
  type t =
    | Solid
    | Pinstripe
    | Check;

  let toString = (pattern: t): string =>
    switch (pattern) {
    | Solid => "Solid"
    | Pinstripe => "Pinstripe"
    | Check => "Checked"
    };

  let fromString = (s: string): option(t) =>
    switch (Js.String.toLowerCase(s)) {
    | "solid" => Some(Solid)
    | "pinstripe" => Some(Pinstripe)
    | "check"
    | "checked" => Some(Check)
    | _ => None
    };
};
