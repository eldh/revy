open Revy.UI;

[@react.component]
let make = () => {
  let (value, setValue) = React.useState(() => "bar");
  <ComponentsCard title="Radiobutton">
    <Box
      direction=`column m={`margin4((`noSpace, `noSpace, `single, `single))}>
      <Radiobutton
        value="bar"
        name="bar"
        label="Bar"
        id="bar"
        checked={value == "bar"}
        onChange={_ => setValue(_ => "bar")}
      />
      <Radiobutton
        value="foo"
        name="bar"
        label="Foo"
        id="foo"
        checked={value == "foo"}
        onChange={_ => setValue(_ => "foo")}
      />
      <Radiobutton
        value="baz"
        name="bar"
        disabled=true
        label="Baz"
        id="baz"
        checked={value == "baz"}
        onChange={_ => setValue(_ => "baz")}
      />
    </Box>
  </ComponentsCard>;
};