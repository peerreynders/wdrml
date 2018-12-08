/* file: src/Index.re

    Original:
    https://media.pragprog.com/titles/reasonml/code/reason-react/shirt-storage/src/Index.re

    Some references:
    https://medium.com/@dan_abramov/smart-and-dumb-components-7ca2f9a7c7d0
    https://reactjs.org/docs/lifting-state-up.html
    https://github.com/reasonml/reason-react/blob/master/docs/component-as-prop.md
    https://reasonml.github.io/reason-react/docs/en/lifecycles
    https://jaredforsyth.com/reason-react/api/ReasonReact.html

    Functions to wire presentational components to container component
    These render callbacks also contain functionality typically provided by
    mapStateToProps / mapDispatchToProps in Redux
    as they adapt the container's state and dispatch
    to the presentation components props.
 */
[%%bs.raw "require('./styles.css');"]; /* for webpack */

type cbf = (Action.t => unit, ReactEvent.Form.t) => unit;
type cbm = (Action.t => unit, ReactEvent.Mouse.t) => unit;

let changeQty: cbf =
  (dispatch, event) =>
    dispatch(ChangeQty(ReactEvent.Form.target(event)##value));
let changeSize: cbf =
  (dispatch, event) =>
    dispatch(ChangeSize(ReactEvent.Form.target(event)##value));
let changeSleeve: cbf =
  (dispatch, event) =>
    dispatch(ChangeSleeve(ReactEvent.Form.target(event)##value));
let changeColor: cbf =
  (dispatch, event) =>
    dispatch(ChangeColor(ReactEvent.Form.target(event)##value));
let changePattern: cbf =
  (dispatch, event) =>
    dispatch(ChangePattern(ReactEvent.Form.target(event)##value));
let commitOrder: cbm = (dispatch, _event) => dispatch(CommitOrder);

/* render callback performing mapStateToProps & mapDispatchToProps */
let withEdit:
  (~state: State.t, ~dispatch: Action.t => unit) => ReasonReact.reactElement =
  (
    ~state as {edit: {qty, size, sleeve, color, pattern, actionLabel}},
    ~dispatch,
  ) =>
    <OrderEditView
      key="orderEditView"
      qty
      size
      sleeve
      color
      pattern
      actionLabel
      changeQty={changeQty(dispatch)}
      changeSize={changeSize(dispatch)}
      changeSleeve={changeSleeve(dispatch)}
      changeColor={changeColor(dispatch)}
      changePattern={changePattern(dispatch)}
      commitOrder={commitOrder(dispatch)}
    />;

/* render callback performing mapStateToProps & mapDispatchToProps */
let withError: (~state: State.t) => ReasonReact.reactElement =
  (~state as {error}) => <ErrorView key="errorView" error />;

let makeDeleteListener: (Action.t => unit, int, ReactEvent.Mouse.t) => unit =
  (dispatch, orderNumber, _event) => dispatch(Delete(orderNumber));

let makeEditListener: (Action.t => unit, int, ReactEvent.Mouse.t) => unit =
  (dispatch, orderNumber, _event) => dispatch(Edit(orderNumber));

/* render callback performing mapStateToProps & mapDispatchToProps */
let withView:
  (~state: State.t, ~dispatch: Action.t => unit) => ReasonReact.reactElement =
  (~state as {orders, current: {editNumber}}, ~dispatch) => {
    let onOrderDelete = makeDeleteListener(dispatch);
    let onOrderEdit = makeEditListener(dispatch);

    <OrdersView
      key="ordersView"
      orders
      editNumber
      onOrderDelete
      onOrderEdit
    />;
  };

/* "Render" the container component passing the presentational components through
     render callbacks. The container component is the top level component
     "lifting the state up".
   */
ReactDOMRe.renderToElementWithId(
  <Orders withEdit withError withView />,
  "root",
);
