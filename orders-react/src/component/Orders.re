/* file: src/component/Orders.re

     Extracted from:
     https://media.pragprog.com/titles/reasonml/code/reason-react/shirt-react/src/OrderForm.re
   */
module Rr = ReasonReact;

type t =
  Rr.componentSpec(
    State.t,
    State.t,
    Rr.noRetainedProps,
    Rr.noRetainedProps,
    Action.t,
  );

type s = Rr.self(State.t, Rr.noRetainedProps, Action.t);
type u = Rr.update(State.t, Rr.noRetainedProps, Action.t);

let component = Rr.reducerComponent("Orders");

let putEditQty: (string, State.t) => State.t =
  (qty, state) => {
    let edit = {...state.edit, qty};
    {...state, edit};
  };

let putEditSize: (string, State.t) => State.t =
  (size, state) => {
    let edit = {...state.edit, size};
    {...state, edit};
  };

let putEditSleeve: (string, State.t) => State.t =
  (sleeve, state) => {
    let edit = {...state.edit, sleeve};
    {...state, edit};
  };

let putEditColor: (string, State.t) => State.t =
  (color, state) => {
    let edit = {...state.edit, color};
    {...state, edit};
  };

let putEditPattern: (string, State.t) => State.t =
  (pattern, state) => {
    let edit = {...state.edit, pattern};
    {...state, edit};
  };

let convertWithDefault: (string, 'a, string => option('a)) => 'a =
  (str, defaultValue, convert) =>
    Belt.Option.getWithDefault(convert(str), defaultValue);

let toIntWithDefault: (string, int) => int =
  (s, defaultValue) =>
    switch (int_of_string(s)) {
    | result => result
    | exception (Failure("int_of_string")) => defaultValue
    };

let convertToOrder: State.editInfo => Belt.Result.t(Order.t, string) =
  info => {
    let quantity = toIntWithDefault(info.qty, 0);
    quantity < 1 || quantity > 100 ?
      Belt.Result.Error("Quantity must be between 1 and 100") :
      Belt.Result.Ok({
        orderNumber: 0,
        quantity,
        size:
          convertWithDefault(
            info.size,
            Shirt.Size.Medium,
            Shirt.Size.fromString,
          ),
        sleeve:
          convertWithDefault(
            info.sleeve,
            Shirt.Sleeve.Long,
            Shirt.Sleeve.fromString,
          ),
        color:
          convertWithDefault(
            info.color,
            Shirt.Color.White,
            Shirt.Color.fromString,
          ),
        pattern:
          convertWithDefault(
            info.pattern,
            Shirt.Pattern.Solid,
            Shirt.Pattern.fromString,
          ),
      });
  };

let commitOrder: State.t => State.t =
  state =>
    switch (convertToOrder(state.edit)) {
    | Error(message) => {...state, error: Some(message)}
    | Ok(aOrder) =>
      let orderNumber = state.current.orderNumber;
      let newOrder = {...aOrder, orderNumber};
      let current: State.orderInfo = {orderNumber: orderNumber + 1};
      let orders = Belt.Array.concat(state.orders, [|newOrder|]);
      let error = None;
      {...state, error, current, orders};
    };

let deleteOrder: (int, State.t) => State.t =
  (deleteNumber, state) => {
    let keepOrder: Order.t => bool =
      order => order.orderNumber != deleteNumber;
    let orders = Belt.Array.keep(state.orders, keepOrder);
    {...state, orders};
  };

let reducer: (Action.t, State.t) => u =
  (action, state) =>
    switch (action) {
    | CommitOrder => Rr.Update(commitOrder(state))
    | ChangeQty(qty) => Rr.Update(putEditQty(qty, state))
    | ChangeSize(size) => Rr.Update(putEditSize(size, state))
    | ChangeSleeve(sleeve) => Rr.Update(putEditSleeve(sleeve, state))
    | ChangeColor(color) => Rr.Update(putEditColor(color, state))
    | ChangePattern(pattern) => Rr.Update(putEditPattern(pattern, state))
    | Delete(orderNumber) => Rr.Update(deleteOrder(orderNumber, state))
    };

let initialState = State.emptyState;

let make = (~withEdit, ~withError, ~withView, _children) => {
  /* Rendering is delegated to the components that are passed in via render callbacks */
  let render: s => Rr.reactElement =
    ({state, send}) => {
      let dispatch = send;
      Rr.array([|
        withEdit(~state, ~dispatch),
        withError(~state),
        withView(~state, ~dispatch),
      |]);
    };

  {...component, initialState, reducer, render};
};
