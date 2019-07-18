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
let p3Clamp = clamp(0., 1.0);
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

  let x = Constants.xn *. lab_xyz(x0);
  let y = Constants.yn *. lab_xyz(y0);
  let z = Constants.zn *. lab_xyz(z0);
  (x, y, z);
};

let xyz_rgb = r => {
  255. *. (r <= 0.00304 ? 12.92 *. r : 1.055 *. r ** (1. /. 2.4) -. 0.055);
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
let xyz_p3 = r => {
  r <= 0.00304 ? 12.92 *. r : 1.055 *. r ** (1. /. 2.4) -. 0.055;
};

let xyzToP3 = ((x, y, z)) => {
  (
    xyz_p3(
      2.4041476775378706282
      *. x
      -. 0.99010703944210726052
      *. y
      -. 0.39759019425373693677
      *. z,
    )
    |> p3Clamp,
    xyz_p3(
      (-0.84239097992588684688)
      *. x
      +. 1.7990595398556119185
      *. y
      +. 0.015970230317527190242
      *. z,
    )
    |> p3Clamp,
    xyz_p3(
      0.04838763487334053893
      *. x
      -. 0.097525459078352834297
      *. y
      +. 1.2739363577809163373
      *. z,
    )
    |> p3Clamp,
  );
};

let toP3 = lab => {
  lab |> labToXyz |> xyzToP3;
};

Js.log2("toP3", toP3(`lab((31.0139, 70.7230, (-116.0393)))));
Js.log2("toP3", toP3(`lab((100., (-128.), 128.))));
Js.log2("toRGB", toRGB(`lab((31.0139, 70.7230, (-116.0393)))));

let p3_xyz = r => {
  let r2 = r;
  if (r2 <= 0.04045) {
    r2 /. 12.92;
  } else {
    ((r2 +. 0.055) /. 1.055) ** 2.4;
  };
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

let labxyzToLab = ((x, y, z)) => {
  let x0 = xyz_lab(x /. Constants.xn);
  let y0 = xyz_lab(y /. Constants.yn);
  let z0 = xyz_lab(z /. Constants.zn);
  let l = y0 *. 116. -. 16.;
  let a = (x0 -. y0) *. 500.;
  let b = (y0 -. z0) *. 200.;
  `lab((l, a, b));
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
let p3ToXyz = ((r_, g_, b_)) => {
  let r = rgb_xyz(r_ |> float_of_int);
  let g = rgb_xyz(g_ |> float_of_int);
  let b = rgb_xyz(b_ |> float_of_int);
  let x = xyz_lab((0.5151 *. r +. 0.292 *. g +. 0.1571 *. b) /. Constants.xn);
  let y =
    xyz_lab((0.2412 *. r +. 0.6922 *. g +. 0.0666 *. b) /. Constants.yn);
  let z =
    xyz_lab(((-0.0011) *. r +. 0.0419 *. g +. 0.7841 *. b) /. Constants.zn);
  (x, y, z);
};

let rgbxyzToLab = ((x, y, z)) => {
  let l = 116. *. y -. 16.;
  `lab((l < 0. ? 0. : l, 500. *. (x -. y), 200. *. (y -. z)));
};

/**
 Takes an (r, g, b) color and returns the corresponding (l, a, b) color */
let fromRGB = rgb => {
  switch (rgb) {
  | `rgb(r, g, b) => (r, g, b) |> rgbToXyz |> rgbxyzToLab
  | `rgba(r, g, b, _) => (r, g, b) |> rgbToXyz |> rgbxyzToLab
  | t => (255, 0, 0) |> rgbToXyz |> rgbxyzToLab |> Log.pass(t)
  };
};

let toCss = c => {
  switch (c) {
  | `rgb(_r, _g, _b) as rgb => rgb
  | `rgba(_r, _g, _b, _a) as rgba => rgba
  | `transparent as t => t
  | `lab(_l, _a, _b) as lab => lab |> toRGB
  };
};

let lightness = (v, lab) => {
  switch (lab) {
  | `lab(_l, a, b) => `lab((clamp(0., 100., v), a, b))
  };
};

let lightnessRGB = (v, rgb) => {
  rgb |> fromRGB |> lightness(v) |> toRGB;
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
  |> labxyzToLab;
};

// Js.log2(
//   "mix(0.5, `lab(0.,0.,0.), `lab(30., -40.,30.))",
//   mix(0.5, `rgb((255, 0, 0)) |> fromRGB, `rgb((0, 255, 0)) |> fromRGB)
//   |> toRGB,
// );

let getTuple = rgb => {
  switch (rgb) {
  | `rgb(r, g, b) => (r, g, b)
  };
};

let mixRgb = (f, rgb1, rgb2) => {
  let toFloats = ((r_, g_, b_)) => {
    (r_ |> float_of_int, g_ |> float_of_int, b_ |> float_of_int);
  };
  let (x1, y1, z1) = rgb1 |> getTuple |> toFloats;
  let (x2, y2, z2) = rgb2 |> getTuple |> toFloats;
  `rgb((
    x1 +. f *. (x2 -. x1) |> int_of_float,
    y1 +. f *. (y2 -. y1) |> int_of_float,
    z1 +. f *. (z2 -. z1) |> int_of_float,
  ));
};

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

let getContrastColorLab =
    (~lightColor=`lab((100., 0., 0.)), ~darkColor=`lab((10., 0., 0.)), lab) => {
  let contrastFn = lab |> toRGB |> rgbContrast;
  let useDark =
    darkColor |> toRGB |> contrastFn > (lightColor |> toRGB |> contrastFn);
  useDark ? darkColor : lightColor;
};

let getContrastColorRGB =
    (~lightColor=`rgb((255, 255, 255)), ~darkColor=`rgb((30, 30, 30)), rgb) => {
  let useDark =
    darkColor |> rgbContrast(rgb) > (lightColor |> rgbContrast(rgb));
  useDark ? darkColor : lightColor;
};

let getContrastColor = c => {
  switch (c) {
  | `rgb(_r, _g, _b) as rgb => getContrastColorRGB(rgb)
  | `lab(_l, _a, _b) as lab => getContrastColorLab(lab) |> toRGB
  | `rgba(_,_,_,_) => `rgb((255, 0, 0)) |> Log.pass("rgba")
  | _ => `rgb((255, 0, 0)) |> Log.pass("contrast")
  } |> toCss;
};

let rgbToCssRGB = ((r, g, b)) => Css.rgb(r, g, b);