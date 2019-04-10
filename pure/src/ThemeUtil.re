let clamp = (minVal, maxVal, v) =>
  if (v < minVal) {
    minVal;
  } else if (v > maxVal) {
    maxVal;
  } else {
    v;
  };

let rgbClamp = clamp(0, 255);
let hslClamp = clamp(0, 100);
module Color = {
  let lighten = (factor, color: Css.color) =>
    switch (color) {
    | `hsl(h, s, l) => `hsl((h, s, hslClamp(l + factor)))
    | `hsla(h, s, l, a) => `hsla((h, s, hslClamp(l + factor), a))
    | `rgb(r, g, b) =>
      `rgb((
        rgbClamp(r + factor),
        rgbClamp(g + factor),
        rgbClamp(b + factor),
      ))
    | `rgba(r, g, b, a) =>
      `rgba((
        rgbClamp(r + factor),
        rgbClamp(g + factor),
        rgbClamp(b + factor),
        a,
      ))
    | _ => color // TODO: Error / handle
    };

  let darken = (factor, rgb) => lighten(factor * (-1), rgb);

  let highlight = (factor, hsl: Css.color) =>
    switch (hsl) {
    | `hsl(_h, _s, l) => l > 50 ? darken(factor, hsl) : lighten(factor, hsl)
    | `hsla(_h, _s, l, _a) =>
      l > 50 ? darken(factor, hsl) : lighten(factor, hsl)
    | `rgb(r, g, b) =>
      Lab.(fromRGB((r, g, b, 1.)) |> highlight(factor) |> toCssRGB)
    | `rgba(r, g, b, a) =>
      Lab.(fromRGB((r, g, b, a)) |> highlight(factor) |> toCssRGB)
    | _ => lighten(factor, hsl)
    };
  let isLight = (hsl: Css.color) =>
    switch (hsl) {
    | `hsl(_h, _s, l) => l > 50
    | `hsla(_h, _s, l, _a) => l > 50
    | `rgb(r, g, b) =>
      Lab.fromRGB((r, g, b, 1.)) |> (((l, _a, _b, _al)) => l > 50.)
    | `rgba(r, g, b, a) =>
      Lab.fromRGB((r, g, b, a)) |> (((l, _a, _b, _al)) => l > 50.)
    | _ => true
    };

  let alpha = (v, c) => {
    Css.(
      switch (c) {
      | `hsl(h, s, l) => hsla(h, s, l, v)
      | `hsla(h, s, l, _a) => hsla(h, s, l, v)
      | `rgba(r, g, b, _a) => rgba(r, g, b, v)
      | `rgb(r, g, b) => rgba(r, g, b, v)
      | _ => c
      }
    );
  };
};
module Style = {
  let shadows = vals => {
    let v =
      List.map(
        v =>
          switch (v) {
          | `shadow(s) => s
          | _ => ""
          },
        vals,
      )
      |> String.concat(",");
    Css.unsafe("box-shadow", v);
  };
};

module Font = {
  let div = (a, b) => {
    let af = float_of_int(a);
    let bf = float_of_int(b);
    (af /. bf +. 0.5)->int_of_float;
  };
  let (/) = div;

  let fontSize = (~baseFontSize=14, ~factor=1.25, n) => {
    factor *. baseFontSize->float_of_int ** n->float_of_int;
  };
};