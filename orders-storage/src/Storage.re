/* file: src/Storage.re

     Extracted from:
     https://media.pragprog.com/titles/reasonml/code/reason-react/shirt-storage/src/OrderForm.re

     To clear storage associated with this key execute the
     following in the browser console:
     > window.localStorage.removeItem("shirt-orders")
   */
module J = AppJson;

let localStorageKey: string = "shirt-orders";

let putStoredState: State.t => unit =
  state =>
    J.encodeState(state)
    ->Js.Json.stringify
    ->Dom.Storage.setItem(localStorageKey, _, Dom.Storage.localStorage);

let parseState: string => State.t =
  json =>
    switch (Js.Json.parseExn(json)) {
    | result => J.decodeState(result)
    | exception _ => State.emptyState
    };

let getStoredState: unit => State.t =
  () =>
    switch (Dom.Storage.getItem(localStorageKey, Dom.Storage.localStorage)) {
    | Some(state) => parseState(state)
    | None => State.emptyState
    };
