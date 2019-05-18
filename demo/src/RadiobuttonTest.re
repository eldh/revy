open Revy.UI;

[@react.component]
let make = () => {
  let (value, setValue) = React.useState(() => "bar");
  
  <ComponentsCard title="Radiobutton">
    <Box
      direction=`column m={`margin4((`noSpace, `noSpace, `single, `single))}>
      <Radiobutton
        value="bar"
        name="bar-radio"
        label="Bar"
        id="bar-radio"
        checked={value == "bar"}
        onChange={_ => setValue(_ => "bar")}
      />
      <Radiobutton
        value="foo"
        name="bar-radio"
        label="Foo"
        id="foo-radio"
        checked={value == "foo"}
        onChange={_ => setValue(_ => "foo")}
      />
      <Radiobutton
        value="baz"
        name="bar-radio"
        disabled=true
        label="Baz"
        id="baz-radio"
        checked={value == "baz"}
        onChange={_ => setValue(_ => "baz")}
      />
    </Box>
  </ComponentsCard>;
};