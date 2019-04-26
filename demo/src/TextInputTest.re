open Revy.UI;

[@react.component]
let make = () => {
  let (value, setValue) = React.useState(() => "");
  let onChange =
    React.useCallback(e => {
      let v = e->ReactEvent.Form.currentTarget##value;
      setValue(_ => v);
    });
  <ComponentsCard title="Inputs">
    <Box
      direction=`column
      m=Revy.Core.(Space.(Margin4(NoSpace, NoSpace, Single, Single)))>
      <TextInput.Label htmlFor="foo">
        "Enabled"->React.string
      </TextInput.Label>
      <TextInput.Input
        label="String"
        id="foo"
        placeholder="Type something nice"
        value
        onChange
      />
    </Box>
    <Box
      direction=`column
      m=Revy.Core.(Space.(Margin4(NoSpace, NoSpace, Single, Single)))>
      <TextInput.Label htmlFor="bar">
        "Disabled"->React.string
      </TextInput.Label>
      <TextInput.Input
        disabled=true
        label="Bar"
        id="bar"
        placeholder="Number"
        type_="number"
        value={value |> String.length |> string_of_int}
        onChange
      />
    </Box>
  </ComponentsCard>;
};