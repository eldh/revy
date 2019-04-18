[%bs.raw {|require('./index.css')|}];

ReactDOMRe.renderToElementWithId(
  React.createElement(App.make, App.makeProps()),
  "root",
);