type retainedProps = {
  order: Order.t,
  editing: bool,
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
    ~editing: bool,
    ~onDelete: ReactEvent.Mouse.t => unit,
    ~onEdit: ReactEvent.Mouse.t => unit,
    array(ReasonReact.reactElement)
  ) =>
  t;
