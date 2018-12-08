type t =
  ReasonReact.componentSpec(
    State.t,
    State.t,
    ReasonReact.noRetainedProps,
    ReasonReact.noRetainedProps,
    Action.t,
  );

let make:
  (
    ~withEdit: (~state: State.t, ~dispatch: Action.t => unit) =>
               ReasonReact.reactElement,
    ~withError: (~state: State.t) => ReasonReact.reactElement,
    ~withView: (~state: State.t, ~dispatch: Action.t => unit) =>
               ReasonReact.reactElement,
    array(ReasonReact.reactElement)
  ) =>
  t;
