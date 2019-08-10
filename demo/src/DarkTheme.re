open Core;

let fonts = {
  body: ["-apple-system", "BlinkMacSystemFont", "sans-serif"],
  title: ["-apple-system", "BlinkMacSystemFont", "sans-serif"],
  mono: ["monospace"],
  alt: ["-apple-system", "BlinkMacSystemFont", "sans-serif"],
};
let hues = {
  neutral: `rgb(0, 0, 0) |> Lab.fromRGB,
  primary: `rgb(193, 219, 255) |> Lab.fromRGB,
  secondary: `rgb(150, 150, 150) |> Lab.fromRGB,
  warning: `rgb(235, 160, 71) |> Lab.fromRGB,
  success: `rgb(88, 214, 21) |> Lab.fromRGB,
  error: `rgb(250, 20, 20) |> Lab.fromRGB,
  brand1: `rgb(213, 54, 222) |> Lab.fromRGB,
  brand2: `rgb(54, 213, 222) |> Lab.fromRGB,
  bodyBackground: `rgb(20, 20, 20) |> Lab.fromRGB,
  bodyText: `rgb(255, 255, 255) |> Lab.fromRGB,
  quiet: `rgb(180, 180, 180) |> Lab.fromRGB,
};
let borderRadii = {small: 0, medium: 8, large: 8};
let theme =
  createTheme(
    // ~fontScale=1.2,
    // ~baseFontSize=16,
    // ~baseGridUnit=5,
    ~baseLightness=80.,
    ~fonts,
    ~hues,
    // ~gridWidth=700,
    ~borderRadii,
    (),
  );