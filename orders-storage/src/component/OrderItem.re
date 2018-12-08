/* file src/component/OrderItem.re

     Original:
     https://media.pragprog.com/titles/reasonml/code/reason-react/shirt-storage/src/OrderItem.re
   */
module Rr = ReasonReact;

type retainedProps = {
  order: Order.t,
  editing: bool,
};

type t =
  Rr.componentSpec(
    Rr.stateless,
    Rr.stateless,
    retainedProps, /* passed to the lifecycle methods */
    retainedProps, /* in the component record from "make" */
    Rr.actionless,
  );

type lcea = Rr.oldNewSelf(Rr.stateless, retainedProps, Rr.actionless);

let component = Rr.statelessComponentWithRetainedProps("OrderItem");

let make:
  (
    ~order: Order.t,
    ~editing: bool,
    ~onDelete: ReactEvent.Mouse.t => unit,
    ~onEdit: ReactEvent.Mouse.t => unit,
    array(Rr.reactElement)
  ) =>
  t =
  (~order, ~editing, ~onDelete, ~onEdit, _children) => {
    let retainedProps = {order, editing};

    let shouldUpdate: lcea => bool =
      ({oldSelf, newSelf}) => oldSelf.retainedProps != newSelf.retainedProps;

    let render = _self => {
      let quantity = Rr.string(string_of_int(order.quantity));
      let size = Rr.string(Shirt.Size.toString(order.size));
      let sleeve = Rr.string(Shirt.Sleeve.toString(order.sleeve));
      let color = Rr.string(Shirt.Color.toString(order.color));
      let pattern = Rr.string(Shirt.Pattern.toString(order.pattern));
      let (disabled, editClass) =
        editing ? (true, Some("editing")) : (false, None);

      /* https://reasonml.github.io/reason-react/docs/en/creation-props-self#neat-trick-with-props-forwarding */

      <tr className=?editClass>
        <td> quantity </td>
        <td> size </td>
        <td> sleeve </td>
        <td> color </td>
        <td> pattern </td>
        <td>
          <button disabled onClick=onEdit> {Rr.string("Edit")} </button>
          <button onClick=onDelete> {Rr.string("Delete")} </button>
        </td>
      </tr>;
    };

    {...component, retainedProps, shouldUpdate, render};
  };
