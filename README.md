# wdrml

Fiddling around with code from [Web Development with ReasonML](https://pragprog.com/book/reasonml/web-development-with-reasonml). The code _is_ the code supplied with the book after my usual _Scratch Refactoring_ (Michael C. Feathers; [Working Effectively with Legacy Code](http://www.informit.com/store/working-effectively-with-legacy-code-9780131177055) (2005)), p.212) that is part of my learning process and some minimal project scaffolding.

* **[table-dom](table-dom/README.md)**: A browser application uses [bs-xmlhttprequest](https://github.com/stefanduberg/bs-xmlhttprequest) to obtain data about the distribution of product variances across a batch of orders. [bs-json](https://github.com/glennsl/bs-json) is used to decode the data, then [bs-webapi](https://github.com/reasonml-community/bs-webapi-incubator) is used to create the HTML table representation in the browser DOM. The server is express-based (via [bs-express](https://github.com/reasonml-community/bs-express)), parses an orders file with [PapaParse](https://github.com/mholt/PapaParse) and then encodes the processing results with [bs-json](https://github.com/glennsl/bs-json). Part of the [Chapter 8: Connecting to JavaScript](https://pragprog.com/book/reasonml/web-development-with-reasonml#toc) discussion.
