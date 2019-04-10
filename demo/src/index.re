[%bs.raw {|require('./index.css')|}];

Css.(global("body, html", [
  margin(px(0)),
  padding(px(0)),
  backgroundColor(InvertedTheme.colors.bodyBackground),
]));

[@bs.module "./serviceWorker"]
external registerServiceWorker: unit => unit = "register";
[@bs.module "./serviceWorker"]
external unregisterServiceWorker: unit => unit = "unregister";

ReactDOMRe.renderToElementWithId(
  React.createElement(App.make, App.makeProps()),
  "root",
);