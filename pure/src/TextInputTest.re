
[@bs.send] external blur: Js.t({..}) => unit = "blur";
let highlightBoxShadow =
  Css.unsafe(
    "box-shadow",
    "0 1px 0 hsla(0,0%,100%, 0.2) inset, 0 -1px 0 hsla(0,0%,0%, 0.2) inset",
  );

[@react.component]
let make = () => {
  let (value, setValue) = React.useState(() => "");
  let onChange = e => {
    let v = e->ReactEvent.Form.currentTarget##value;
    // Js.log2("e", v);
    setValue(_ => v);
  };
  <>
    <TextInput
      placeholder="Foo bar"
      value
      onChange
      m=Theme.(margin(Space.Single))
    />
    <TextInput
      placeholder="Foo bar"
      type_="number"
      value
      onChange
      m=Theme.(margin(Space.Single))
    />
  </>;
};