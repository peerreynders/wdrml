/* file: src/component/OrderEditView.re

     Extracted from:
     https://media.pragprog.com/titles/reasonml/code/reason-react/shirt-react/src/OrderForm.re
   */
module Rr = ReasonReact;

type retainedProps = {
  qty: string,
  size: string,
  sleeve: string,
  color: string,
  pattern: string,
  actionLabel: string,
};

type t =
  Rr.componentSpec(
    Rr.stateless,
    Rr.stateless,
    retainedProps, /* passed to the lifecycle methods */
    retainedProps, /* in the component record from "make" */
    Rr.actionless,
  );

type s = Rr.self(Rr.stateless, retainedProps, Rr.actionless);

type cbf = ReactEvent.Form.t => unit;
type cbm = ReactEvent.Mouse.t => unit;

type lcea = Rr.oldNewSelf(Rr.stateless, retainedProps, Rr.actionless);

let component = Rr.statelessComponentWithRetainedProps("OrderEditView");

let makeOptionElement: (string, string) => Rr.reactElement =
  (name, value) => {
    let key = value;
    let label = Rr.string(name);
    <option key value> label </option>;
  };

let makeOptionValueElement: string => Rr.reactElement =
  value => makeOptionElement(value, value);

let makeSelect:
  (string, string, array(string), string, ReactEvent.Form.t => unit) =>
  Rr.reactElement =
  (_id, name, choices, value, onChange) => {
    let label = Rr.string(" " ++ name ++ ": ");
    let options =
      Belt.Array.map(choices, makeOptionValueElement)
      ->Belt.Array.concat([|makeOptionElement(name, "")|], _)
      ->Rr.array;

    <label className="item">
      label
      <select value onChange> options </select>
    </label>;
  };

let make:
  (
    ~qty: string,
    ~size: string,
    ~sleeve: string,
    ~color: string,
    ~pattern: string,
    ~actionLabel: string,
    ~changeQty: cbf,
    ~changeSize: cbf,
    ~changeSleeve: cbf,
    ~changeColor: cbf,
    ~changePattern: cbf,
    ~commitOrder: cbm,
    array(Rr.reactElement)
  ) =>
  t =
  (
    ~qty,
    ~size,
    ~sleeve,
    ~color,
    ~pattern,
    ~actionLabel,
    ~changeQty,
    ~changeSize,
    ~changeSleeve,
    ~changeColor,
    ~changePattern,
    ~commitOrder,
    _children,
  ) => {
    let retainedProps = {qty, size, sleeve, color, pattern, actionLabel};

    let shouldUpdate: lcea => bool =
      ({oldSelf, newSelf}) => oldSelf.retainedProps != newSelf.retainedProps;

    let render: s => Rr.reactElement =
      _self => {
        let qtyLabel = Rr.string("Qty: ");
        let onChange = changeQty;
        let onClick = commitOrder;
        let sizeSelect =
          makeSelect(
            "sizeMenu",
            "Size",
            [|"XS", "S", "M", "L", "XL", "XXL", "XXXL"|],
            size,
            changeSize,
          );
        let sleeveSelect =
          makeSelect(
            "sleeveMenu",
            "Sleeve",
            [|"Short sleeve", "Long sleeve", "Extra-long sleeve"|],
            sleeve,
            changeSleeve,
          );
        let colorSelect =
          makeSelect(
            "colorMenu",
            "Color",
            [|"White", "Blue", "Red", "Green", "Brown"|],
            color,
            changeColor,
          );
        let patternSelect =
          makeSelect(
            "patternMenu",
            "Pattern",
            [|"Solid", "Pinstripe", "Checked"|],
            pattern,
            changePattern,
          );

        <p className="flex">
          <label className="item">
            qtyLabel
            <input type_="text" size=4 value=qty onChange />
          </label>
          sizeSelect
          sleeveSelect
          colorSelect
          patternSelect
          <span className="item">
            <button onClick> {Rr.string(actionLabel)} </button>
          </span>
        </p>;
      };

    {...component, retainedProps, shouldUpdate, render};
  };
