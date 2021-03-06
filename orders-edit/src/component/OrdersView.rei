type t =
  ReasonReact.componentSpec(
    ReasonReact.stateless,
    ReasonReact.stateless,
    ReasonReact.noRetainedProps,
    ReasonReact.noRetainedProps,
    ReasonReact.actionless,
  );

let make:
  (
    ~orders: array(Order.t),
    ~editNumber: option(int),
    ~onOrderDelete: (int, ReactEvent.Mouse.t) => unit,
    ~onOrderEdit: (int, ReactEvent.Mouse.t) => unit,
    array(ReasonReact.reactElement)
  ) =>
  t;
