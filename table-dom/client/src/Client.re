/* Original:
     https://media.pragprog.com/titles/reasonml/code/interop/client/src/Client.re
   */
module D = Webapi.Dom;
module Doc = D.Document;
module Elem = D.Element;

let getValue: option(Elem.t) => option(string) =
  element =>
    Belt.Option.map(element, Elem.unsafeAsHtmlElement)
    ->Belt.Option.map(_, D.HtmlElement.value);

let capitalize: string => string =
  s =>
    Js.String.toUpperCase(Js.String.get(s, 0))
    ++ Js.String.toLowerCase(Js.String.substr(s, ~from=1));

let appendTableRow: (string, (string, int)) => string =
  (rows, (choice, total)) => {
    let count = string_of_int(total);
    rows ++ {j|<tr><td>$choice</td><td>$count</td></tr>\n|j};
  };

let makeTableRows = (choices, totals) =>
  Belt.Array.zip(choices, totals)->Belt.Array.reduce("", appendTableRow);

/* Note the _missing_ "json" parameter name ; i.e. the "decode"
   values are partially applied functions
   */
let decodeTitle: Js.Json.t => string =
  Json.Decode.field("title", Json.Decode.string);
let decodeChoices: Js.Json.t => array(string) =
  Json.Decode.field("choices", Json.Decode.array(Json.Decode.string));
let decodeTotals: Js.Json.t => array(int) =
  Json.Decode.field("totals", Json.Decode.array(Json.Decode.int));

let processResponse: XmlHttpRequest.t => unit =
  xhr => {
    let status = XmlHttpRequest.status(xhr);
    let optBody = Js.Nullable.toOption(XmlHttpRequest.responseText(xhr));
    let optResult = Doc.getElementById("resultTable", D.document);

    switch (optBody, optResult, status) {
    | (Some(body), Some(resultElement), 200) =>
      let json = Json.parseOrRaise(body);
      let title = capitalize(decodeTitle(json));
      let rows = makeTableRows(decodeChoices(json), decodeTotals(json));
      Elem.setInnerHTML(
        resultElement,
        {j|<table><thead><tr><th>$title</th><th>Total</th></tr>\n$rows</table>\n|j},
      );
    | (_, _, _) => ()
    };
  };

let requestCounts: string => unit =
  category => {
    let method = "GET";
    let url = {j|http://localhost:3000/json?choice=$category|j};
    let async = true;
    let xhr = XmlHttpRequest.make();
    XmlHttpRequest.open_(xhr, ~method, ~url, ~async, ());
    XmlHttpRequest.addEventListener(
      xhr,
      `load(_event => processResponse(xhr)),
    );
    XmlHttpRequest.send(xhr);
  };

let sendRequest: Dom.event => unit =
  _ =>
    Doc.getElementById("category", D.document)
    ->getValue
    ->Belt.Option.map(category =>
        category != "" ? requestCounts(category) : ()
      )
    ->ignore;

let addCategoryListener: Elem.t => unit =
  element =>
    D.EventTarget.addEventListener(
      "change",
      sendRequest,
      D.Element.asEventTarget(element),
    );

let maybeCategory = Doc.getElementById("category", D.document);
Belt.Option.map(maybeCategory, addCategoryListener);
