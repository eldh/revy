exception InvalidValue(string);
// let Constants = require('./lab-constants');
// let {unpack} = require('../../utils');
// let {pow} = Math;

/*
 * L* [0..100]
 * a [-100..100]
 * b [-100..100]
 */

type a11yLevel =
  | AA
  | AAA;

type a11yTextSize =
  | Normal
  | Large;

let clamp = (minVal, maxVal, v) =>
  if (v < minVal) {
    minVal;
  } else if (v > maxVal) {
    maxVal;
  } else {
    v;
  };

let rgbClamp = clamp(0, 255);
let toInt = f => f +. 0.5 |> int_of_float;

module Constants = {
  // Corresponds roughly to RGB brighter/darker
  let kn = 18;
  // D65 standard referent
  let xn = 0.950470;
  let yn = 1.;
  let zn = 1.088830;
  let t0 = 0.137931034; // 4 / 29
  let t1 = 0.206896552; // 6 / 29
  let t2 = 0.12841855; // 3 * t1 * t1
  let t3 = 0.008856452; // t1 * t1 * t1
};

let xyz_rgb = r => {
  255. *. (r <= 0.00304 ? 12.92 *. r : 1.055 *. r ** (1. /. 2.4) -. 0.055);
};

let lab_xyz = t => {
  t > Constants.t1 ? t *. t *. t : Constants.t2 *. (t -. Constants.t0);
};

let labToXyz = lab => {
  let (l, a, b) =
    switch (lab) {
    | `lab(l, a, b) => (l, a, b)
    };
  let y0 = (l +. 16.) /. 116.;
  let x0 = y0 +. a /. 500.;
  let z0 = y0 -. b /. 200.;

  // y = LAB_CONSTANTS.Yn * lab_xyz(y);
  // x = LAB_CONSTANTS.Xn * lab_xyz(x);
  // z = LAB_CONSTANTS.Zn * lab_xyz(z);

  let x = Constants.xn *. lab_xyz(x0);
  let y = Constants.yn *. lab_xyz(y0);
  let z = Constants.zn *. lab_xyz(z0);
  (x, y, z);
};

let xyzToRgb = ((x, y, z)) => {
  `rgb((
    xyz_rgb(3.2404542 *. x -. 1.5371385 *. y -. 0.4985314 *. z)
    |> toInt
    |> rgbClamp,
    xyz_rgb((-0.9692660) *. x +. 1.8760108 *. y +. 0.0415560 *. z)
    |> toInt
    |> rgbClamp,
    xyz_rgb(0.0556434 *. x -. 0.2040259 *. y +. 1.0572252 *. z)
    |> toInt
    |> rgbClamp,
  ));
};

let toRGB = lab => {
  lab |> labToXyz |> xyzToRgb;
};

let toCssRGB = toRGB;

let rgb_xyz = r => {
  let r2 = r /. 255.;
  if (r2 <= 0.04045) {
    r2 /. 12.92;
  } else {
    ((r2 +. 0.055) /. 1.055) ** 2.4;
  };
};

let xyz_lab = t =>
  if (t > Constants.t3) {
    t ** (1. /. 3.);
  } else {
    t /. Constants.t2 +. Constants.t0;
  };

let rgbToXyz = ((r_, g_, b_)) => {
  let r = rgb_xyz(r_ |> float_of_int);
  let g = rgb_xyz(g_ |> float_of_int);
  let b = rgb_xyz(b_ |> float_of_int);

  let x =
    xyz_lab(
      (0.4124564 *. r +. 0.3575761 *. g +. 0.1804375 *. b) /. Constants.xn,
    );
  let y =
    xyz_lab(
      (0.2126729 *. r +. 0.7151522 *. g +. 0.0721750 *. b) /. Constants.yn,
    );
  let z =
    xyz_lab(
      (0.0193339 *. r +. 0.1191920 *. g +. 0.9503041 *. b) /. Constants.zn,
    );
  (x, y, z);
};

let xyzToLab = ((x, y, z)) => {
  let l = 116. *. y -. 16.;
  `lab((l < 0. ? 0. : l, 500. *. (x -. y), 200. *. (y -. z)));
};

/**
 Takes an (r, g, b) color and returns the corresponding (l, a, b) color */
let fromRGB = rgb => {
  switch (rgb) {
  | `rgb(r, g, b) => (r, g, b) |> rgbToXyz |> xyzToLab
  | `rgba(r, g, b, _) => (r, g, b) |> rgbToXyz |> xyzToLab
  | _ => (255, 0, 0) |> rgbToXyz |> xyzToLab
  };
};

let lightness = (v, lab) => {
  switch (lab) {
  | `lab(_l, a, b) => `lab((clamp(0., 100., v), a, b))
  };
};

let lighten = (factor, lab) => {
  switch (lab) {
  | `lab(l, a, b) =>
    `lab((clamp(0., 100., l +. (factor |> float_of_int)), a, b))
  };
};

let lightenRGB = (factor, c) => {
  c |> fromRGB |> lighten(factor) |> toRGB;
};

let darkenLab = (factor, c) => {
  c |> lighten(factor * (-1));
};

let darkenRGB = (factor, c) => {
  c |> fromRGB |> darkenLab(factor) |> toRGB;
};

let highlightLab = (factor, lab) => {
  switch (lab) {
  | `lab(l, _a, _b) => lighten((l > 50. ? (-1) : 1) * factor, lab)
  };
};

let highlightRGB = (factor, rgb) => {
  rgb |> fromRGB |> highlightLab(factor) |> toRGB;
};

let highlight = (factor, c) => {
  switch (c) {
  | `rgb(_, _, _) as rgb => rgb |> highlightRGB(factor)
  | `lab(_l, _a, _b) as lab => lab |> highlightLab(factor)
  };
};

let mix = (f, lab1, lab2) => {
  let (x1, y1, z1) = lab1 |> labToXyz;
  let (x2, y2, z2) = lab2 |> labToXyz;
  (x1 +. f *. (x2 -. x1), y1 +. f *. (y2 -. y1), z1 +. f *. (z2 -. z1))
  |> xyzToRgb
  |> fromRGB;
};

let mixRgb = (f, rgb1, rgb2) =>
  mix(f, fromRGB(rgb1), fromRGB(rgb2)) |> toRGB;

let luminance_x = x => {
  let x1 = (x |> float_of_int) /. 255.;
  x1 <= 0.03928 ? x1 /. 12.92 : ((x1 +. 0.055) /. 1.055) ** 2.4;
};

let luminanceRGB = rgb => {
  switch (rgb) {
  | `rgb(r, g, b) =>
    let rl = r |> luminance_x;
    let gl = g |> luminance_x;
    let bl = b |> luminance_x;
    0.2126 *. rl +. 0.7152 *. gl +. 0.0722 *. bl;
  };
};

let luminance = c => {
  (
    switch (c) {
    | `rgb(_, _, _) as rgb => rgb
    | `lab(_, _, _) as lab => lab |> toRGB
    }
  )
  |> luminanceRGB;
};

let contrast = (luminance1, luminance2) => {
  luminance1 > luminance2
    ? (luminance1 +. 0.05) /. (luminance2 +. 0.05)
    : (luminance2 +. 0.05) /. (luminance1 +. 0.05);
};

let rgbContrast = (r1, r2) =>
  contrast(r1 |> luminanceRGB, r2 |> luminanceRGB);

let getContrastLimit = (level, size) =>
  switch (level, size) {
  | (AA, Large) => 3.
  | (AA, Normal) => 4.5
  | (AAA, Large) => 4.5
  | (AAA, Normal) => 7.
  };

let isContrastOk = (~level=AA, ~size=Normal, r1, r2) => {
  rgbContrast(r1, r2) > getContrastLimit(level, size);
};

let getContrastColorLab = lab => {
  switch (lab) {
  | `lab(_, a, b) as c =>
    let rgb = c |> toRGB;
    let darkLab = `lab((0., a, b));
    let lightLab = `lab((100., a, b));

    darkLab
    |> toRGB
    |> rgbContrast(rgb) > (lightLab |> toRGB |> rgbContrast(rgb))
      ? darkLab : lightLab;
  };
};

let getContrastColorRGB = rgb => {
  rgb |> fromRGB |> getContrastColorLab |> toRGB;
};

let getContrastColor = c => {
  switch (c) {
  | `rgb(r, g, b) => getContrastColorRGB(`rgb((r, g, b)))
  | `lab(l, a, b) => getContrastColorLab(`lab((l, a, b))) |> toRGB
  };
};

let rgbToCssRGB = ((r, g, b)) => Css.rgb(r, g, b);