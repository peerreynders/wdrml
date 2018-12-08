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

let maybeIntFromString: string => option(int) =
  s =>
    switch (int_of_string(s)) {
    | result => Some(result)
    | exception (Failure("int_of_string")) => None
    };

let orderQtyFromString:
  (Belt.Result.t(Order.t, string), string) => Belt.Result.t(Order.t, string) =
  (orderResult, qty) =>
    switch (orderResult, maybeIntFromString(qty)) {
    | (Ok(order), Some(quantity)) when quantity > 0 || quantity < 101 =>
      Ok({...order, quantity})
    | (Error(_), _) => orderResult
    | (Ok(_), Some(_)) => Error("Quantity must be between 1 and 100")
    | (_, None) => Error("Please specify a quantity")
    };

let putOrderSize: (Order.t, Shirt.Size.t) => Order.t =
  (order, size) => {...order, size};

let putOrderSleeve: (Order.t, Shirt.Sleeve.t) => Order.t =
  (order, sleeve) => {...order, sleeve};

let putOrderColor: (Order.t, Shirt.Color.t) => Order.t =
  (order, color) => {...order, color};

let putOrderPattern: (Order.t, Shirt.Pattern.t) => Order.t =
  (order, pattern) => {...order, pattern};

let mapOrderField:
  (
    Belt.Result.t(Order.t, string),
    option('a),
    (Order.t, 'a) => Order.t,
    string
  ) =>
  Belt.Result.t(Order.t, string) =
  (orderResult, maybeValue, f, error) =>
    switch (orderResult, maybeValue) {
    | (Ok(order), Some(value)) => Ok(f(order, value))
    | (Error(_), _) => orderResult
    | (_, None) => Error(error)
    };

let convertToOrder: State.editInfo => Belt.Result.t(Order.t, string) =
  info =>
    orderQtyFromString(Ok(Order.empty), info.qty)
    ->mapOrderField(
        Shirt.Size.fromString(info.size),
        putOrderSize,
        "Please select a size",
      )
    ->mapOrderField(
        Shirt.Sleeve.fromString(info.sleeve),
        putOrderSleeve,
        "Please select a sleeve",
      )
    ->mapOrderField(
        Shirt.Color.fromString(info.color),
        putOrderColor,
        "Please select a color",
      )
    ->mapOrderField(
        Shirt.Pattern.fromString(info.pattern),
        putOrderPattern,
        "Please select a pattern",
      );

let updateStateOrders: (Order.t, State.t) => State.t =
  (order, state) => {
    let (current, orders) =
      switch (state.current.editNumber) {
      | Some(orderNumber) =>
        /* order being edited */
        let updatedOrder = {...order, orderNumber};
        let next: State.orderInfo = {...state.current, editNumber: None};
        let replaceOrder: Order.t => Order.t = (
          order => order.orderNumber == orderNumber ? updatedOrder : order
        );
        let updated = Belt.Array.map(state.orders, replaceOrder);
        (next, updated);
      | None =>
        /* new order */
        let orderNumber = state.current.orderNumber;
        let newOrder = {...order, orderNumber};
        let next: State.orderInfo = {
          ...state.current,
          orderNumber: orderNumber + 1,
        };
        let updated = Belt.Array.concat(state.orders, [|newOrder|]);

        (next, updated);
      };

    let error = None;
    let edit = State.emptyEdit;

    {edit, error, current, orders};
  };

let commitOrder: State.t => State.t =
  state =>
    switch (convertToOrder(state.edit)) {
    | Error(message) => {...state, error: Some(message)}
    | Ok(order) => updateStateOrders(order, state)
    };

let deleteOrder: (int, State.t) => State.t =
  (deleteNumber, state) => {
    let keepOrder: Order.t => bool =
      order => order.orderNumber != deleteNumber;
    let orders = Belt.Array.keep(state.orders, keepOrder);
    let error = None;
    let (edit, current) =
      switch (state.current.editNumber) {
      | Some(number) when number == deleteNumber => (
          State.emptyEdit,
          {...state.current, editNumber: None},
        )
      | _ => (state.edit, state.current)
      };

    {edit, error, current, orders};
  };

let editOrder: (int, State.t) => State.t =
  (editNumber, state) => {
    let findOrder: Order.t => bool = order => order.orderNumber == editNumber;
    switch (Belt.Array.keep(state.orders, findOrder)) {
    | [|order|] =>
      let current = {...state.current, editNumber: Some(editNumber)};
      let error = None;
      let edit = State.editFromOrder(order, ~actionLabel="Update", ());

      {...state, error, current, edit};
    | _ => state
    };
  };

let initialState = () => State.emptyState;

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
    | Edit(orderNumber) => Rr.Update(editOrder(orderNumber, state))
    };

type rp = (~state: State.t, ~dispatch: Action.t => unit) => Rr.reactElement;
type rps = (~state: State.t) => Rr.reactElement;

let make:
  (~withEdit: rp, ~withError: rps, ~withView: rp, array(Rr.reactElement)) => t =
  (~withEdit, ~withError, ~withView, _children) => {
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
