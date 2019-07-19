open Core;

let fonts = {
  body: ["-apple-system", "BlinkMacSystemFont", "sans-serif"],
  title: ["-apple-system", "BlinkMacSystemFont", "sans-serif"],
  mono: ["monospace"],
  alt: ["-apple-system", "BlinkMacSystemFont", "sans-serif"],
};
// Primary [71.60567363141296, -3.7400822778627663, -39.52681667409359]
// Secondary [91.12129013553876, -0.6419275839839589, -1.3229677188405065]
// Success [76.20376970565414, -63.92615916697536, 72.12169225502674]
// Error [55.719220981282675, 63.76077827576321, 37.791751999217404]
// Warning [76.53542703170206, 9.351090400586736, 60.97554225863063]
// Brand1 [54.09192323841317, 78.54727771667736, -52.699580772277386]
// Brand2 [78.25249670594033, -36.32765481662148, -16.003677169569407]
// Brand3 [85.3300784398493, -22.066011137736375, 74.9815823890027]
// Brand4 [78.44200701646093, -65.51838282954553, 35.31924585960553]
let hues = {
  neutral: `rgb(0, 0, 0) |> Lab.fromRGB,
  primary: `rgb(110, 181, 247) |> Lab.fromRGB,
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
    ~fontScale=1.2,
    ~baseFontSize=16,
    ~baseGridUnit=5,
    ~fonts,
    ~hues,
    ~gridWidth=700,
    ~borderRadii,
    (),
  );