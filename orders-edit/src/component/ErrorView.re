/* file: src/component/ErrorView.re
 */
type retainedProps = {error: option(string)};

type t =
  ReasonReact.componentSpec(
    ReasonReact.stateless,
    ReasonReact.stateless,
    retainedProps,
    retainedProps,
    ReasonReact.actionless,
  );

/* lcea: lifecycle event argument */
type lcea =
  ReasonReact.oldNewSelf(
    ReasonReact.stateless,
    retainedProps,
    ReasonReact.actionless,
  );

let component = ReasonReact.statelessComponentWithRetainedProps("ErrorView");

let make: (~error: option(string), array(ReasonReact.reactElement)) => t =
  (~error, _children) => {
    let retainedProps = {error: error};

    /* Only need to render if a DIFFERENT error message (including NO error message) has been issued */
    let shouldUpdate: lcea => bool =
      ({oldSelf, newSelf}) => oldSelf.retainedProps != newSelf.retainedProps;

    let render = _self =>
      switch (error) {
      | Some(message) =>
        <p className="error"> {ReasonReact.string(message)} </p>
      | None => <p />
      };

    {...component, retainedProps, shouldUpdate, render};
  };
