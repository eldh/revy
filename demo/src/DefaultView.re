
[@react.component]
let make = () =>
  <ThemeContext.Provider value=DefaultTheme.theme>
    <Test />
  </ThemeContext.Provider>;