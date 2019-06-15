type themes =
  | Light
  | Dark;

[@react.component]
let make = () => {
  let default = Core.Styles.usePrefersDarkMode() ? Dark : Light;
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
    | Light => Core.DefaultTheme.theme
    };
  };
  Core.Styles.useBodyStyle(
    Css.[
      backgroundColor(themeObj.colors.bodyBackground),
      margin(px(0)),
      padding(px(0)),
    ],
  );
  <Core.Context.Provider value=themeObj>
  <>
    <Topbar toggleTheme />
    <Box alignContent=`center m={`margin(`auto)}>
      <Test toggleTheme />
    </Box>
  </>
  </Core.Context.Provider>;
};