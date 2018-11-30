/* Original:
     https://media.pragprog.com/titles/reasonml/code/interop/server/src/Server.re
   */
let onListen: Js.nullable(Js.Exn.t) => unit =
  e =>
    switch (e) {
    | exception (Js.Exn.Error(e)) =>
      Js.log(e);
      Node.Process.exit(1);
    | _ => Js.log("Listening at http://127.0.0.1:3000")
    };

let app: Express.App.t = Express.express();

[@bs.deriving abstract]
type options = {root: string};

let indexHandler:
  (Express.Middleware.next, Express.Request.t, Express.Response.t) =>
  Express.complete =
  (_next, _req) =>
    Express.Response.sendFile("index.html", options(~root="./dist"));

let jsonHandler:
  (Express.Middleware.next, Express.Request.t, Express.Response.t) =>
  Express.complete =
  (_, req) =>
    Express.Request.query(req)
    ->Js.Dict.unsafeGet("choice")
    ->Json.Decode.string
    ->Stats.processFile("orders.csv", _)
    ->Express.Response.sendJson;

let fileHandler:
  (Express.Middleware.next, Express.Request.t, Express.Response.t) =>
  Express.complete =
  (_, req) =>
    Express.Request.params(req)
    ->Js.Dict.unsafeGet("filename")
    ->Json.Decode.string
    ->Express.Response.sendFile(options(~root="./dist"));

/* CORS: allow access from page served by parcel server */
let authorizeOrigin:
  ((Express.Request.t, Express.Response.t)) =>
  (option(string), Express.Response.t) =
  ((req, res)) =>
    switch (Express.Request.get("Origin", req)) {
    | Some(origin) as result =>
      Js.String.startsWith("http://localhost:1234", origin) ?
        (result, res) : (None, res)
    | None => (None, res)
    };

let attachCorsHeaders:
  ((option(string), Express.Response.t)) => Express.Response.t =
  ((maybeOrigin, res)) =>
    switch (maybeOrigin) {
    | Some(origin) =>
      Express.Response.setHeader("Access-Control-Allow-Origin", origin, res)
      ->Express.Response.setHeader(
          "Access-Control-Allow-Headers",
          "Origin, X-Requested-With, Content-Type, Accept",
          _,
        )
    | None => res
    };

let corsHandler:
  (Express.Middleware.next, Express.Request.t, Express.Response.t) =>
  Express.complete =
  (next, req, res) =>
    authorizeOrigin((req, res))
    ->attachCorsHeaders
    ->next(Express.Next.middleware, _);
let _ = Express.Middleware.from(corsHandler)->Express.App.use(app, _);

/* CORS END */

let appendRoute:
  (
    Express.App.t,
    string,
    (Express.Middleware.next, Express.Request.t, Express.Response.t) =>
    Express.complete
  ) =>
  unit =
  (app, path, handler) =>
    Express.Middleware.from(handler)->Express.App.get(app, ~path, _);

let _ = appendRoute(app, "/", indexHandler);
let _ = appendRoute(app, "/json", jsonHandler);
let _ = appendRoute(app, "/:filename", fileHandler);

let server: Express.HttpServer.t =
  Express.App.listen(app, ~port=3000, ~onListen, ());
