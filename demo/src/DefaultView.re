[@bs.config {jsx: 3}];

[@react.component __MODULE__]
let make = () =>
  <ThemeContext.Provider value=DefaultTheme.theme>
    <Test />
  </ThemeContext.Provider>;