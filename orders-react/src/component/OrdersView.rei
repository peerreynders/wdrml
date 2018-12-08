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
    ~onOrderDelete: (int, ReactEvent.Mouse.t) => unit,
    array(ReasonReact.reactElement)
  ) =>
  t;
