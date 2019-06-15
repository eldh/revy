open UI;

[@react.component]
let make = () => {
  let (bar, setBar) = React.useState(() => true);
  let (foo, setFoo) = React.useState(() => false);
  let (baz, setBaz) = React.useState(() => false);
  <ComponentsCard title="Checkbox">
    <Box
      direction=`column m={`margin4((`noSpace, `noSpace, `single, `single))}>
      <Checkbox
        value="bar"
        name="bar"
        label="Bar"
        id="bar"
        checked=bar
        onChange={_ => setBar(v => !v)}
      />
      <Checkbox
        value="foo"
        name="bar"
        label="Foo"
        id="foo"
        checked=foo
        onChange={_ => setFoo(v => !v)}
      />
      <Checkbox
        value="baz"
        name="bar"
        disabled=true
        label="Baz"
        id="baz"
        checked=baz
        onChange={_ => setBaz(v => !v)}
      />
    </Box>
  </ComponentsCard>;
};