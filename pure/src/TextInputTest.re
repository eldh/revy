[@react.component]
let make = () => {
  let (value, setValue) = React.useState(() => "");
  let onChange =
    React.useCallback(e => {
      let v = e->ReactEvent.Form.currentTarget##value;
      // Js.log2("e", v);
      setValue(_ => v);
    });
  <ComponentsCard title="Inputs">
    <Box direction=`column m=Theme.Space.Single>
      <TextInput.Label htmlFor="foo"> "Foo"->React.string </TextInput.Label>
      <TextInput.Input
        label="String"
        id="foo"
        placeholder="String"
        value
        onChange
      />
    </Box>
    <Box direction=`column m=Theme.Space.Single>
      <TextInput.Label htmlFor="bar"> "Bar"->React.string </TextInput.Label>
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