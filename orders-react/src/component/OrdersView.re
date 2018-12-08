/* file: src/component/OrdersView.re

     Extracted from:
     https://media.pragprog.com/titles/reasonml/code/reason-react/shirt-react/src/OrderForm.re
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

let make:
  (
    ~orders: array(Order.t),
    ~onOrderDelete: (int, ReactEvent.Mouse.t) => unit,
    array(Rr.reactElement)
  ) =>
  t =
  (~orders, ~onOrderDelete, _children) => {
    let render = _self => {
      let makeOrderItem: Order.t => Rr.reactElement =
        order => {
          let key = string_of_int(order.orderNumber);
          let onDelete = onOrderDelete(order.orderNumber);
          <OrderItem key order onDelete />;
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