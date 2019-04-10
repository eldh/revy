exception InvalidValue(string);
// let Constants = require('./lab-constants');
// let {unpack} = require('../../utils');
// let {pow} = Math;

/*
 * L* [0..100]
 * a [-100..100]
 * b [-100..100]
 */

let clamp = (minVal, maxVal, v) =>
  if (v < minVal) {
    minVal;
  } else if (v > maxVal) {
    maxVal;
  } else {
    v;
  };

let toInt = f => (f +. 0.5)->int_of_float;

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

let labToXyz = ((l, a, b, alpha)) => {
  let y0 = (l +. 16.) /. 116.;
  let x0 = y0 +. a /. 500.;
  let z0 = y0 -. b /. 200.;

  let y = Constants.yn *. lab_xyz(y0);
  let x = Constants.xn *. lab_xyz(x0);
  let z = Constants.zn *. lab_xyz(z0);
  (x, y, z, alpha);
};

let xyzToRgb = ((x, y, z, alpha)) => {
  (
    xyz_rgb(3.2404542 *. x -. 1.5371385 *. y -. 0.4985314 *. z)->toInt,
    xyz_rgb((-0.9692660) *. x +. 1.8760108 *. y +. 0.0415560 *. z)->toInt,
    xyz_rgb(0.0556434 *. x -. 0.2040259 *. y +. 1.0572252 *. z)->toInt,
    alpha,
  );
};

let toRGB = lab => {
  lab |> labToXyz |> xyzToRgb;
};

let toCssRGB = t => {
  let (r, g, b, a) = toRGB(t);
  Css.rgba(r, g, b, a);
};

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

let rgbToXyz = ((r_, g_, b_, alpha)) => {
  let r = rgb_xyz(r_->float_of_int);
  let g = rgb_xyz(g_->float_of_int);
  let b = rgb_xyz(b_->float_of_int);

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
  (x, y, z, alpha);
};

let xyzToLab = ((x, y, z, alpha)) => {
  let l = 116. *. y -. 16.;
  (l < 0. ? 0. : l, 500. *. (x -. y), 200. *. (y -. z), alpha);
};

let fromRGB = rgb => {
  rgb |> rgbToXyz |> xyzToLab;
};

let fromCssRGB = rgb => {
  switch (rgb) {
  | `rgb(r, g, b) => fromRGB((r, g, b, 1.))
  | `rgba(r, g, b, a) => fromRGB((r, g, b, a))
  // | _ => raise(InvalidValue("Not an rgb value"))
  };
};

let lighten = (factor, (l, a, b, alpha)) => {
  (clamp(0., 100., l +. factor->float_of_int), a, b, alpha);
};

let highlight = (factor, (l, a, b, alpha)) => {
  lighten((l > 50. ? (-1) : 1) * factor, (l, a, b, alpha));
};

let mix = (f, lab1, lab2) => {
  let (x1, y1, z1, alpha1) = lab1 |> labToXyz;
  let (x2, y2, z2, alpha2) = lab2 |> labToXyz;
  (
    x1 +. f *. (x2 -. x1),
    y1 +. f *. (y2 -. y1),
    z1 +. f *. (z2 -. z1),
    (alpha1 +. alpha2) /. 2.,
  )
  |> xyzToRgb
  |> fromRGB;
};

let mixRgb = (f, rgb1, rgb2) =>
  mix(f, fromRGB(rgb1), fromRGB(rgb2)) |> toRGB;

Js.log2(
  "mixRgb(0.5, (0,0,0,1.), (255,255,255,1.)",
  mixRgb(0.5, (0, 0, 0, 1.), (255, 255, 255, 1.)),
);