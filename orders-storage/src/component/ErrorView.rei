type retainedProps = {error: option(string)};

type t =
  ReasonReact.componentSpec(
    ReasonReact.stateless,
    ReasonReact.stateless,
    retainedProps,
    retainedProps,
    ReasonReact.actionless,
  );

let make: (~error: option(string), array(ReasonReact.reactElement)) => t;
