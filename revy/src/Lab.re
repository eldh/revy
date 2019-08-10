exception InvalidValue(string);

/*
 * L* [0..100]
 * a [-100..100]
 * b [-100..100]
 */

type t = [ | `lab(float, float, float, float)];

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
  let (l, a, b, alpha) =
    switch (lab) {
    | `lab(l, a, b, alpha) => (l, a, b, alpha)
    };
  let y0 = (l +. 16.) /. 116.;
  let x0 = y0 +. a /. 500.;
  let z0 = y0 -. b /. 200.;

  let x = Constants.xn *. lab_xyz(x0);
  let y = Constants.yn *. lab_xyz(y0);
  let z = Constants.zn *. lab_xyz(z0);
  (x, y, z, alpha);
};

let xyz_rgb = r => {
  255. *. (r <= 0.00304 ? 12.92 *. r : 1.055 *. r ** (1. /. 2.4) -. 0.055);
};

let xyzToRgb = ((x, y, z, alpha)) => {
  `rgba((
    xyz_rgb(3.2404542 *. x -. 1.5371385 *. y -. 0.4985314 *. z)
    |> toInt
    |> rgbClamp,
    xyz_rgb((-0.9692660) *. x +. 1.8760108 *. y +. 0.0415560 *. z)
    |> toInt
    |> rgbClamp,
    xyz_rgb(0.0556434 *. x -. 0.2040259 *. y +. 1.0572252 *. z)
    |> toInt
    |> rgbClamp,
    alpha,
  ));
};
let toRGB = lab => {
  lab |> labToXyz |> xyzToRgb;
};
let xyz_p3 = r => {
  r <= 0.00304 ? 12.92 *. r : 1.055 *. r ** (1. /. 2.4) -. 0.055;
};

let xyzToP3 = ((x, y, z, alpha)) => {
  `p3(
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
    alpha,
  );
};

let toP3 = lab => {
  lab |> labToXyz |> xyzToP3;
};

// Js.log2("toP3", toP3(`lab((31.0139, 70.7230, (-116.0393), 1.))));
// Js.log2("toP3", toP3(`lab((100., (-128.), 128., 1.))));
// Js.log2("toRGB", toRGB(`lab((31.0139, 70.7230, (-116.0393), 1.))));

let p3_xyz = r => {
  let lab2 = r;
  if (lab2 <= 0.04045) {
    lab2 /. 12.92;
  } else {
    ((lab2 +. 0.055) /. 1.055) ** 2.4;
  };
};

let rgb_xyz = r => {
  let lab2 = r /. 255.;
  if (lab2 <= 0.04045) {
    lab2 /. 12.92;
  } else {
    ((lab2 +. 0.055) /. 1.055) ** 2.4;
  };
};

let xyz_lab = t =>
  if (t > Constants.t3) {
    t ** (1. /. 3.);
  } else {
    t /. Constants.t2 +. Constants.t0;
  };

let labxyzToLab = ((x, y, z, alpha)) => {
  let x0 = xyz_lab(x /. Constants.xn);
  let y0 = xyz_lab(y /. Constants.yn);
  let z0 = xyz_lab(z /. Constants.zn);
  let l = y0 *. 116. -. 16.;
  let a = (x0 -. y0) *. 500.;
  let b = (y0 -. z0) *. 200.;
  `lab((l, a, b, alpha));
};

let rgbToXyz = ((r_, g_, b_, alpha: float)) => {
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
  (x, y, z, alpha);
};
let p3ToXyz = ((r_, g_, b_, alpha)) => {
  let r = rgb_xyz(r_ |> float_of_int);
  let g = rgb_xyz(g_ |> float_of_int);
  let b = rgb_xyz(b_ |> float_of_int);
  let x = xyz_lab((0.5151 *. r +. 0.292 *. g +. 0.1571 *. b) /. Constants.xn);
  let y =
    xyz_lab((0.2412 *. r +. 0.6922 *. g +. 0.0666 *. b) /. Constants.yn);
  let z =
    xyz_lab(((-0.0011) *. r +. 0.0419 *. g +. 0.7841 *. b) /. Constants.zn);
  (x, y, z, alpha);
};

let rgbxyzToLab = ((x, y, z, alpha: float)) => {
  let l = 116. *. y -. 16.;
  `lab((l < 0. ? 0. : l, 500. *. (x -. y), 200. *. (y -. z), alpha));
};

/**
 Takes an (r, g, b, alpha?) color and returns the corresponding (l, a, b, alpha) color */
let fromRGB =
  fun
  | `rgb(r, g, b) => (r, g, b, 1.) |> rgbToXyz |> rgbxyzToLab
  | `rgba(r, g, b, a) => (r, g, b, a) |> rgbToXyz |> rgbxyzToLab;
let toLab =
  fun
  | `lab(_, _, _, _) as lab => lab
  | `rgb(_, _, _) as rgb => rgb |> fromRGB
  | `rgba(_, _, _, _) as rgba => rgba |> fromRGB
  | `transparent => `lab((0., 0., 0., 0.));

let toCss =
  fun
  | `lab(_l, _a, _b, alpha) as lab =>
    switch (alpha) {
    | 0. => `transparent
    | _ => toRGB(lab)
    };

let lightness = v => {
  fun
  | `lab(_l, a, b, alpha) => `lab((clamp(0., 100., v), a, b, alpha));
};

let lighten = factor => {
  fun
  | `lab(l, a, b, alpha) =>
    `lab((clamp(0., 100., l +. (factor |> float_of_int)), a, b, alpha));
};

let darken = (factor, c) => {
  c |> lighten(factor * (-1));
};

let highlight = factor => {
  fun
  | `lab(l, _a, _b, _alpha) as c =>
    lighten((l > 50. ? (-1) : 1) * factor, c);
};

let mix = (f, lab1, lab2) => {
  let (x1, y1, z1, a1) = lab1 |> labToXyz;
  let (x2, y2, z2, a2) = lab2 |> labToXyz;
  (
    x1 +. f *. (x2 -. x1),
    y1 +. f *. (y2 -. y1),
    z1 +. f *. (z2 -. z1),
    (a1 +. a2) /. 2.,
  )
  |> labxyzToLab;
};

let luminance_x = x => {
  let x1 = (x |> float_of_int) /. 255.;
  x1 <= 0.03928 ? x1 /. 12.92 : ((x1 +. 0.055) /. 1.055) ** 2.4;
};

let luminance =
  fun
  | `lab(l, _a, _b, _alpha) => l;

let contrast = (lab1, lab2) => {
  let lum1 = lab1 |> luminance;
  let lum2 = lab2 |> luminance;

  21. *. 0.01 *. abs_float(lum1 -. lum2);
};

let getContrastLimit =
  fun
  | (AA, Large) => 3.
  | (AA, Normal) => 4.5
  | (AAA, Large) => 4.5
  | (AAA, Normal) => 7.;

let isContrastOk = (~level=AA, ~size=Normal, lab1, lab2) => {
  contrast(lab1, lab2) > getContrastLimit((level, size));
};

let getContrastColor =
    (
      ~lightColor=`lab((100., 0., 0., 1.)),
      ~darkColor=`lab((10., 0., 0., 1.)),
      ~tint=?,
      lab,
    ) => {
  let contrastFn = contrast(lab);

  let baseColor =
    darkColor |> contrastFn > (lightColor |> contrastFn)
      ? darkColor : lightColor;
  switch (tint) {
  | None => baseColor
  | Some(`lab(_l, a, b, alpha)) =>
    `lab((luminance(baseColor), a, b, alpha))
  };
};