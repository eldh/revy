type themes =
  | Light
  | Dark;

[@react.component]
let make = () => {
  let default = ThemeUtil.Hooks.usePrefersDarkMode() ? Dark : Light;
  let (theme, setTheme) = React.useState(() => None);

  let toggleTheme = () =>
    setTheme(current =>
      Some(
        switch (default, current) {
        | (Dark, None)
        | (_, Some(Dark)) => Light
        | (Light, None)
        | (_, Some(Light)) => Dark
        },
      )
    );
  let selected =
    switch (theme) {
    | None => default
    | Some(d) => d
    };
  let themeObj = {
    switch (selected) {
    | Dark => DarkTheme.theme
    | Light => Theme.DefaultTheme.theme
    };
  };
  ThemeUtil.Hooks.useBodyStyle(
    Css.[
      backgroundColor(themeObj.colors.bodyBackground),
      margin(px(0)),
      padding(px(0)),
    ],
  );
  <Theme.Context.Provider value=themeObj>
  <>
    <Topbar toggleTheme />
    <Box alignContent=`center m={Theme.Margin(Theme.Space.Auto)}>
      <Test toggleTheme />
    </Box>
  </>
  </Theme.Context.Provider>;
};