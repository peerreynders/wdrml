type retainedProps = {
  qty: string,
  size: string,
  sleeve: string,
  color: string,
  pattern: string,
  actionLabel: string,
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
    ~qty: string,
    ~size: string,
    ~sleeve: string,
    ~color: string,
    ~pattern: string,
    ~actionLabel: string,
    ~changeQty: ReactEvent.Form.t => unit,
    ~changeSize: ReactEvent.Form.t => unit,
    ~changeSleeve: ReactEvent.Form.t => unit,
    ~changeColor: ReactEvent.Form.t => unit,
    ~changePattern: ReactEvent.Form.t => unit,
    ~commitOrder: ReactEvent.Mouse.t => unit,
    array(ReasonReact.reactElement)
  ) =>
  t;
