type themes =
  | Light
  | Dark;
let getTheme =
  fun
  | Dark => DarkTheme.theme
  | Light => Core.DefaultTheme.theme;
let getThemeKey =
  fun
  | Dark => "0"
  | Light => "1";

let darkMode =
  Core.Styles.matchMedia("(prefers-color-scheme: dark)")##matches;

(darkMode ? Dark : Light) |> getTheme |> Core.setTheme;

[@react.component]
let make = () => {
  let default = Core.Styles.usePrefersDarkMode() ? Dark : Light;
  let (themeVariant, setThemeVariant) = React.useState(() => default);
  let setTheme = themeVariant => {
    Core.setTheme(themeVariant |> getTheme);
    setThemeVariant(_ => themeVariant);
  };

  let toggleTheme = () =>
    setTheme(
      switch (themeVariant) {
      | Dark => Light
      | Light => Dark
      },
    );
  Core.Styles.useBodyStyle(
    Css.[
      backgroundColor(Core.getTheme().colors.bodyBackground |> Lab.toCss),
      margin(px(0)),
      padding(px(0)),
    ],
  );

  <React.Fragment key={themeVariant |> getThemeKey}>
    <Topbar toggleTheme />
    <Box alignContent=`center margin={`margin(`auto)}>
      <Test toggleTheme />
    </Box>
  </React.Fragment>;
};