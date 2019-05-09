open Css;
open Revy;
open Revy.Core;

let fonts = {
  body: ["-apple-system", "BlinkMacSystemFont", "sans-serif"],
  title: ["-apple-system", "BlinkMacSystemFont", "sans-serif"],
  mono: ["monospace"],
  alt: ["-apple-system", "BlinkMacSystemFont", "sans-serif"],
};

let colors = {
  primary: Lab.(fromRGB(`rgb(110, 181, 247)) |> toCssRGB),
  primaryText: Lab.(getContrastColor(`rgb(110, 181, 247)) |> fromRGB |> toCssRGB),
  secondary: Lab.(fromRGB(`rgb(227, 230, 232)) |> toCssRGB),
  secondaryText: Lab.(getContrastColor(`rgb(227, 230, 232)) |> fromRGB |> toCssRGB),
  warning: Lab.(fromRGB(`rgb(235, 180, 71)) |> toCssRGB),
  warningText: Lab.(getContrastColor(`rgb(235, 180, 71)) |> fromRGB |> toCssRGB),
  success: Css.rgb(88, 214, 21),
  successText: Lab.(getContrastColor(`rgb(88, 214, 21)) |> fromRGB |> toCssRGB),
  error: rgb(240, 72, 72),
  errorText: Lab.(getContrastColor(`rgb(240, 72, 72)) |> fromRGB |> toCssRGB),
  bodyBackground: rgb(20, 20, 20),
  bodyText: rgb(255, 255, 255),
  quietText: rgb(180, 180, 180),
};
let theme =
  createTheme(
    ~fontScale=1.2,
    ~baseFontSize=16,
    ~baseGridUnit=4,
    ~fonts,
    ~colors,
    ~gridWidth=700,
    (),
  );