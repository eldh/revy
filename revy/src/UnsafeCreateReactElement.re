[@bs.module "react"]
external createElement: (string, Js.t({..})) => React.element =
  "createElement";

[@react.component]
let make = (~tag="div", ~props, ()) => createElement(tag, props);

let create = (tag, props) => createElement(tag, props);