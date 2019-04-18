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
      backgroundColor(themeObj.color(Theme.Color.BodyBackground)),
      margin(px(0)),
      padding(px(0)),
    ],
  );
  <Theme.Context.Provider value=themeObj>
    <Box direction=`row wrap=`nowrap>
      <>
        <Sidebar />
        <Box
          alignContent=`center
          style=Css.[maxWidth(Calc.(-)(vw(100.), px(200)))]>
          <> <Test toggleTheme /> </>
        </Box>
      </>
    </Box>
  </Theme.Context.Provider>;
};