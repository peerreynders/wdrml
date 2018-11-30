# table-dom

Two side-by-side `client` and `server` projects that serve a local DOM page ReasonML playground project.

Based largely on the [Chapter 8: Connecting to JavaScript](https://pragprog.com/book/reasonml/web-development-with-reasonml#toc) client/server sample project from [Web Development with ReasonML](https://pragprog.com/book/reasonml/web-development-with-reasonml) (ISBN: 978-1-68050-633-4)

Assumes BuckleScript 4.0.7 is globally installed.

## Run it all from the server
```
# install/link only for the first time
client $ npm install
client $ npm run link-bs
client $ npm run rebuild
client $ cd ../server

# install/link only the first time
server $ npm install
server $ npm run link-bs
server $ npm run rebuild
server $ npm run start

```
Check `http://localhost:3000` in the browser.


## Parcel watches and serves client assets

```
# 3 terminals; 2 for the "client" directory and 1 for the "server" directory

# install/link only for the first time
client1 $ npm install
client1 $ npm run link-bs

# compiles the ReasonML source when modified
client1 $ npm run bsb-watch

# bundles modified JavaScript and loads in to the browser.
client2 $ npm run parcel-watch

# link/install only for the first time
server $ npm install
server $ npm run link-bs
server $ npm run bsb-build
server $ npm run start
```

Check `http://localhost:1234` in the browser. JSON is served via `http://localhost:3000`.

Look in the `server/package.json` and `client/package.json` for more npm scripts.

Some further reading:
* [Web Development with ReasonML](https://pragprog.com/book/reasonml/web-development-with-reasonml)
* [Modern JavaScript Explained For Dinosaurs](https://medium.com/the-node-js-collection/modern-javascript-explained-for-dinosaurs-f695e9747b70)
* [CLI - Parcel](https://parceljs.org/cli.html)
* [npm-install](https://docs.npmjs.com/cli/install)
* [npm-uninstall](https://docs.npmjs.com/cli/uninstall)
* [How to Use npm as a Build Tool](https://www.keithcirkel.co.uk/how-to-use-npm-as-a-build-tool/)
* [Awesome npm scripts](https://github.com/RyanZim/awesome-npm-scripts#articles)
* [CORS on ExpressJS](https://enable-cors.org/server_expressjs.html)
* [Exploring ReasonML](http://reasonmlhub.com/exploring-reasonml/toc.html)
