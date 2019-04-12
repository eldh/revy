
[@bs.module "react"]
external createDOMElement: (string, Js.t({..})) => React.element =
  "createElement";

[@react.component]
let make = (~tag="div", ~props, ()) => {
  createDOMElement(tag, props);
};

let use = (tag, props) => createDOMElement(tag, props);