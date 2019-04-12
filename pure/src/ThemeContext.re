let context = React.createContext(DefaultTheme.theme);
let provider = React.Context.provider(context);

module Provider = {
  [@react.component]
  let make = (~value, ~children) => {
    EscapeHatch.use(
      Obj.magic(provider),
      {"value": value, "children": children},
    );
  };
};