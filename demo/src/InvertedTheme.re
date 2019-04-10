open Css;
open Theme;

let fonts = {
  body: ["Inter", "-apple-system", "BlinkMacSystemFont", "sans-serif"],
  title: ["Inter", "-apple-system", "BlinkMacSystemFont", "sans-serif"],
  mono: ["monospace"],
  alt: ["Inter", "-apple-system", "BlinkMacSystemFont", "sans-serif"],
};
let colors = {
  primary: Lab.(fromRGB((110, 181, 247, 1.)) |> toCssRGB),
  primaryText:
    Lab.(fromRGB((110, 181, 247, 1.)) |> highlight(70) |> toCssRGB),
  secondary: Lab.(fromRGB((227, 230, 232, 1.)) |> toCssRGB),
  secondaryText: Lab.(fromRGB((227, 230, 232, 1.)) |> highlight(90) |> toCssRGB),
  warning: Lab.(fromRGB((235, 180, 71, 1.)) |> toCssRGB),
  warningText: Lab.(fromRGB((235, 180, 71, 1.)) |> lighten(-90) |> toCssRGB),
  success: Css.rgb(88,214,21),
  successText: Lab.(fromRGB((88,214,21, 1.)) |> lighten(-90) |> toCssRGB),
  error: rgb(240, 35, 35),
  errorText: Lab.(fromRGB((240, 35, 35, 1.)) |> lighten(-90) |> toCssRGB),
  bodyBackground: rgb(20,20,20),
  bodyText: rgb(255,255,255),
  quietText: rgb(180,180,180),
};
let theme =
  make(
    ~fontScale=1.1333,
    ~baseFontSize=16,
    ~baseGridUnit=5,
    ~fonts,
    ~colors,
    (),
  );