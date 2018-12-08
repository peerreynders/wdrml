# orders-edit
An implementation of the _It's Your Turn_ exercise which adds order editing capability to the `shirt-react` base project from [Chapter 9: Making Applications with Reason/React](https://pragprog.com/book/reasonml/web-development-with-reasonml#toc) of [Web Development with ReasonML](https://pragprog.com/book/reasonml/web-development-with-reasonml) (ISBN: 978-1-68050-633-4). In this case the refactored `orders-react` project was modified.

Primary differences to the original:
* [`OrderForm.re`](https://media.pragprog.com/titles/reasonml/code/reason-react/shirt-react/src/OrderForm.re) has been split into container component [`Orders.re`](src/component/Orders.re) and presentational components [`OrderEditView.re`](src/component/OrderEditView.re), [`ErrorView.re`](src/component/ErrorView.re) and [`OrdersView.re`](src/component/Orders.re).
* The presentational components are injected into the container component via render callbacks in [`Index.re`](src/Index.re).
* [`Order.re`](src/Order.re) was extracted from [`Shirt.re`](https://media.pragprog.com/titles/reasonml/code/reason-react/shirt-react/src/Shirt.re).
* [`Action.re`](src/Action.re) was extracted from `OrderForm.re` to make the actions available to [`Index.re`](src/Index.re) to allow it to define quasi-action creators for the render callbacks.
* [`State.re`](src/State.re) was extracted from `OrderForm.re` to make its structure available to the [`Index.re`](src/Index.re) `mapStateToProps`-style functionality. 

Assumes BuckleScript 4.0.8 is globally installed.

## Building the bundle
```
# install/link only for the first time
orders-edit $ npm install
orders-edit $ npm run link-bs
orders-edit $ npm run rebuild
```
In your file system locate `orders-edit/dist/index.html` and open it with a browser.

## Live reloading with [DevServer](https://webpack.js.org/configuration/dev-server/)

```
# 2 terminals; 1st for BuckleScript compilation, 2nd for webpack/DevServer bundling

# compiles the ReasonML source when modified
1st $ npm run bsb-watch

# bundles modified JavaScript and reloads it in the browser.
2nd $ npm run webpack-server
```

Check http://localhost:8000 in the browser.

Look in the `package.json` for more npm scripts ([bsb -make-world -w exits early when backgrounded #2750](https://github.com/BuckleScript/bucklescript/issues/2750)).

Further reading:
* [React - Main Concepts > 10. Lifting State Up](https://reactjs.org/docs/lifting-state-up.html)
* [Dan Abramov - React Components, Elements, and Instances](https://reactjs.org/blog/2015/12/18/react-components-elements-and-instances.html#elements-describe-the-tree)
* [Dan Abramov - Presentational and Container Components](https://medium.com/@dan_abramov/smart-and-dumb-components-7ca2f9a7c7d0) - ([Caveat](https://twitter.com/dan_abramov/status/802569801906475008?lang=en): "Almost regretting I wrote that.")
* [Dan Abramov - You Might Not Need Redux](https://medium.com/@dan_abramov/you-might-not-need-redux-be46360cf367)
* [Soham Kamani - React-redux "connect" explained](https://www.sohamkamani.com/blog/2017/03/31/react-redux-connect-explained/)
* [React - Advanced Guides > Render Props](https://reactjs.org/docs/render-props.html)
* [Donavon West - Function as Child Components are an Anti-Pattern](https://americanexpress.io/faccs-are-an-antipattern/)
* [Cheng Lou - Component as Prop](https://github.com/reasonml/reason-react/blob/master/docs/component-as-prop.md)
* [Jared Forsyth - Main ReasonReact API Types](https://jaredforsyth.com/reason-react/api/ReasonReact.html)
* [ReasonReact -  Core > Lifecycles](https://reasonml.github.io/reason-react/docs/en/lifecycles)
* [BuckleScript - Build System > Automatic Interface Generation](https://bucklescript.github.io/docs/en/automatic-interface-generation)
* [webpack - Guides > Environment Variables](https://webpack.js.org/guides/environment-variables/)
* [webpack - API > Command Line Interface > Environment Options](https://webpack.js.org/api/cli/#environment-options)
* [webpack - Configuration > Configuration Types > Exporting a Function]( https://webpack.js.org/configuration/configuration-types/#exporting-a-function)
* [webpack - Loaders > css-loader](https://webpack.js.org/loaders/css-loader/)
* [webpack - Loaders > style-loader](https://webpack.js.org/loaders/style-loader/)
* [webpack - Plugins > HtmlWebpackPlugin](https://webpack.js.org/plugins/html-webpack-plugin/)
* [mini-css-extract-plugin](https://github.com/webpack-contrib/mini-css-extract-plugin)
* [Linux Documentation Project - GNU/Linux Command-Line Tools Summary > 20. Mini-Guides > Wildcards > Standard Wildcards (globbing patterns)](http://tldp.org/LDP/GNU-Linux-Tools-Summary/html/x11655.htm#STANDARD-WILDCARDS)
