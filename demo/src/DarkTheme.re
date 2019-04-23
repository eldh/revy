open Css;
open Theme;

let fonts = {
  body: ["-apple-system", "BlinkMacSystemFont", "sans-serif"],
  title: ["-apple-system", "BlinkMacSystemFont", "sans-serif"],
  mono: ["monospace"],
  alt: ["-apple-system", "BlinkMacSystemFont", "sans-serif"],
};
let colors = {
  primary: Lab.(fromRGB((110, 181, 247)) |> toCssRGB),
  primaryText: Lab.(fromRGB((110, 181, 247)) |> highlight(70) |> toCssRGB),
  secondary: Lab.(fromRGB((227, 230, 232)) |> toCssRGB),
  secondaryText: Lab.(fromRGB((227, 230, 232)) |> highlight(90) |> toCssRGB),
  warning: Lab.(fromRGB((235, 180, 71)) |> toCssRGB),
  warningText: Lab.(fromRGB((235, 180, 71)) |> lighten(-90) |> toCssRGB),
  success: Css.rgb(88, 214, 21),
  successText: Lab.(fromRGB((88, 214, 21)) |> lighten(-90) |> toCssRGB),
  error: rgb(240, 72, 72),
  errorText: rgb(0, 0, 0),
  bodyBackground: rgb(20, 20, 20),
  bodyText: rgb(255, 255, 255),
  quietText: rgb(180, 180, 180),
};
let theme =
  make(
    ~fontScale=1.2,
    ~baseFontSize=16,
    ~baseGridUnit=4,
    ~fonts,
    ~colors,
    (),
  );