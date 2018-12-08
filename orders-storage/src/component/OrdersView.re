/* file: src/component/OrdersView.re

     Extracted from:
     https://media.pragprog.com/titles/reasonml/code/reason-react/shirt-storage/src/OrderForm.re
   */
module Rr = ReasonReact;

type t =
  Rr.componentSpec(
    Rr.stateless,
    Rr.stateless,
    Rr.noRetainedProps, /* passed to the lifecycle methods */
    Rr.noRetainedProps, /* in the component record from "make" */
    Rr.actionless,
  );

let component = Rr.statelessComponent("OrdersView");

let equalOrderNumber = (maybeNumber, orderNumber) =>
  switch (maybeNumber) {
  | None => false
  | Some(otherNumber) => otherNumber == orderNumber
  };

let make:
  (
    ~orders: array(Order.t),
    ~editNumber: option(int),
    ~onOrderDelete: (int, ReactEvent.Mouse.t) => unit,
    ~onOrderEdit: (int, ReactEvent.Mouse.t) => unit,
    array(Rr.reactElement)
  ) =>
  t =
  (~orders, ~editNumber, ~onOrderDelete, ~onOrderEdit, _children) => {
    let render = _self => {
      let makeOrderItem: Order.t => Rr.reactElement =
        order => {
          let key = string_of_int(order.orderNumber);
          let onDelete = onOrderDelete(order.orderNumber);
          let onEdit = onOrderEdit(order.orderNumber);
          let editing = equalOrderNumber(editNumber, order.orderNumber);
          <OrderItem key order onDelete onEdit editing />;
        };

      let orderItems = Belt.Array.map(orders, makeOrderItem)->Rr.array;

      Belt.Array.length(orders) > 0 ?
        <table>
          <thead>
            <tr>
              <th> {Rr.string("Qty")} </th>
              <th> {Rr.string("Size")} </th>
              <th> {Rr.string("Sleeve")} </th>
              <th> {Rr.string("Color")} </th>
              <th> {Rr.string("Pattern")} </th>
              <th> {Rr.string("Action")} </th>
            </tr>
          </thead>
          <tbody> orderItems </tbody>
        </table> :
        <p> {Rr.string("No orders entered yet.")} </p>;
    };

    {...component, render};
  };
