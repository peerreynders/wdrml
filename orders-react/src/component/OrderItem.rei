type retainedProps = {
  order: Order.t,
};

type t =
  ReasonReact.componentSpec(
    ReasonReact.stateless,
    ReasonReact.stateless,
    retainedProps,
    retainedProps,
    ReasonReact.actionless,
  );

let make:
  (
    ~order: Order.t,
    ~onDelete: ReactEvent.Mouse.t => unit,
    array(ReasonReact.reactElement)
  ) =>
  t;
