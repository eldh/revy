exception InvalidValue(string);
/* let Constants = require('./lab-constants'); */
/* let {unpack} = require('../../utils'); */
/* let {pow} = Math; */

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

let rgbClamp = clamp(0, 255);
let toInt = f => f +. 0.5 |> int_of_float;

module Constants = {
  /* Corresponds roughly to RGB brighter/darker */
  let kn = 18;
  /* D65 standard referent */
  let xn = 0.950470;
  let yn = 1.;
  let zn = 1.088830;
  let t0 = 0.137931034; /* 4 / 29 */
  let t1 = 0.206896552; /* 6 / 29 */
  let t2 = 0.12841855; /* 3 * t1 * t1 */
  let t3 = 0.008856452; /* t1 * t1 * t1 */
};

let xyz_rgb = r => {
  255. *. (r <= 0.00304 ? 12.92 *. r : 1.055 *. r ** (1. /. 2.4) -. 0.055);
};

let lab_xyz = t => {
  t > Constants.t1 ? t *. t *. t : Constants.t2 *. (t -. Constants.t0);
};

let labToXyz = ((l, a, b)) => {
  let y0 = (l +. 16.) /. 116.;
  let x0 = y0 +. a /. 500.;
  let z0 = y0 -. b /. 200.;

  /* y = LAB_CONSTANTS.Yn * lab_xyz(y); */
  /* x = LAB_CONSTANTS.Xn * lab_xyz(x); */
  /* z = LAB_CONSTANTS.Zn * lab_xyz(z); */

  let x = Constants.xn *. lab_xyz(x0);
  let y = Constants.yn *. lab_xyz(y0);
  let z = Constants.zn *. lab_xyz(z0);
  (x, y, z);
};

let xyzToRgb = ((x, y, z)) => {
  (
    xyz_rgb(3.2404542 *. x -. 1.5371385 *. y -. 0.4985314 *. z) |> toInt |> rgbClamp,
    xyz_rgb((-0.9692660) *. x +. 1.8760108 *. y +. 0.0415560 *. z) |> toInt |> rgbClamp,
    xyz_rgb(0.0556434 *. x -. 0.2040259 *. y +. 1.0572252 *. z) |> toInt |> rgbClamp,
  );
};

let toRGB = lab => {
  lab |> labToXyz |> xyzToRgb;
};

/* let toCssRGB = t => { */
/*   let (r, g, b) = toRGB(t); */
/*   Css.rgb(r, g, b); */
/* }; */

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
  (l < 0. ? 0. : l, 500. *. (x -. y), 200. *. (y -. z));
};

/**
 Takes an (r, g, b) color and returns the corresponding (l, a, b) color */
let fromRGB = rgb => {
print_endline("Add Your Test Cases Here");

  rgb |> rgbToXyz |> xyzToLab;
};

/**
 Takes a Css.rgb value and returns the corresponding (l, a, b) color */
let fromCssRGB = rgb => {
  switch (rgb) {
  | `rgb(r, g, b) => fromRGB((r, g, b))
  | `rgba(r, g, b, _a) => fromRGB((r, g, b))
  /* | _ => raise(InvalidValue("Not an rgb value")) */
  };
};

let lighten = (factor, (l, a, b)) => {
  (clamp(0., 100., l +. (factor |> float_of_int)), a, b);
};

let highlight = (factor, (l, a, b)) => {
  lighten((l > 50. ? (-1) : 1) * factor, (l, a, b));
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

let luminance = ((r, g, b)) => {
  let rl = r |> luminance_x;
  let gl = g |> luminance_x;
  let bl = b |> luminance_x;
  0.2126 *. rl +. 0.7152 *. gl +. 0.0722 *. bl;
};

let contrast = (l1, l2) =>
  l1 > l2 ? (l1 +. 0.05) /. (l2 +. 0.05) : (l2 +. 0.05) /. (l1 +. 0.05);
/* let contrastLab = ((l1, _, _), (l2, _, _)) => l1 > l2 ? (l1 +. 5.) /.  *(l2 +. 5.) : (l2 +. 5.) /. (l1 +. 5.); */

let rgbContrast = (r1, r2) => contrast(r1 |> luminance, r2 |> luminance);
/* let rgbContrastLab = (r1, r2) => contrastLab(r1 |> fromRGB, r2 |>  fromRGB); */
type a11yLevel =
  | AA
  | AAA;

type a11yTextSize =
  | Normal
  | Large;

let isContrastOk = (~level=AA, ~size=Normal, r1, r2) => {
  let limit =
    switch (level, size) {
    | (AA, Large) => 3.
    | (AA, Normal) => 4.5
    | (AAA, Large) => 4.5
    | (AAA, Normal) => 7.
    };
  rgbContrast(r1, r2) > limit;
};

let getContrastColor = rgb => {
  /* Js.log2("luminance(rgb)", luminance(rgb)); */
  let labC = rgb |> fromRGB;
  let (_l, a, b) = labC;
  /* let isDark = rgb |> luminance < 0.5; */
  let darkLabC = (0., a, b);
  let lightLabC = (100., a, b);
  /* Js.log2("labC", labC); */
  /* Js.log2("darkLabC", darkLabC |> toRGB |> rgbContrast(rgb)); */
  /* Js.log2("lightLabC", lightLabC |> toRGB |> rgbContrast(rgb)); */
};
/* Js.log2("getContrastColor(())", getContrastColor((110, 181, 247))); */

/* Js.log2( */
/*   "rgbContrast((110, 181, 247), (0,0, 0))", */
/*   rgbContrast((110, 181, 247), (255, 255, 255)), */
/* ); */
/* Js.log2( */
/*   "isContrastOk((50, 50, 50), (255, 192, 0))", */
/*   isContrastOk((50, 50, 50), (255, 192, 0)), */
/* ); */
/* Js.log2( */
/*   "isContrastOk((75, 75, 75), (255, 192, 0))", */
/*   isContrastOk((75, 75, 75), (255, 192, 0)), */
/* ); */
/* Js.log2( */
/*   "isContrastOk((0, 192, 255), (255, 192, 0))", */
/*   isContrastOk((0, 192, 255), (255, 192, 0)), */
/* ); */