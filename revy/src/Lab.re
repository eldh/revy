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

let toPrecision: (int, float) => float = [%raw
  (a, b) => "return Number(b.toPrecision(a))"
];

let toFixed = (i0, f) => {
  let i = i0 |> float_of_int;
  if (f < 1.) {
    let multiplier = 10. ** i;
    float_of_int(int_of_float(multiplier *. f +. 0.5)) /. multiplier;
  } else {
    toPrecision(i0, f);
  };
};

let clamp = (minVal, maxVal, v) =>
  if (v < minVal) {
    minVal;
  } else if (v > maxVal) {
    maxVal;
  } else {
    v;
  };

let p_ = 10000000.;
let ( **. ) = ( *. ); //(a, b) => a *. p_ *. (b *. p_) /. (p_ *. p_); // |> toPrecision(12);
let (/) = (/.); // (a, b) => a *. p_ /. (b *. p_); // |> toPrecision(12);

let rgbClamp = clamp(0, 255);
let p3Clamp = a => clamp(0., 1.0, a) |> toPrecision(4);
let toInt = f => f +. 0.5 |> int_of_float;

module Constants = {
  let kn = 18;
  let xn = 0.964214;
  let yn = 1.;
  let zn = 0.825188;
  let t0 = 0.137931034; // 4 / 29
  let t1 = 0.206896552; // 6 / 29
  let t2 = 0.12841855; // 3 * t1 * t1
  let t3 = 0.008856452; // t1 * t1 * t1
};

let lab_xyz = t => {
  t > Constants.t1 ? t **. (t **. t) : Constants.t2 **. (t -. Constants.t0);
};

let labToXyz = lab => {
  let (l, a, b, alpha) =
    switch (lab) {
    | `lab(l, a, b, alpha) => (l, a, b, alpha)
    };
  let y0 = (l +. 16.) / 116.;
  let x0 = y0 +. a / 500.;
  let z0 = y0 -. b / 200.;

  let x = Constants.xn **. lab_xyz(x0);
  let y = Constants.yn **. lab_xyz(y0);
  let z = Constants.zn **. lab_xyz(z0);

  (x, y, z, alpha);
};

let srgbGamma = r => {
  255. **. (r <= 0.0031308 ? 12.92 **. r : 1.055 **. r ** (1. / 2.4) -. 0.055);
};

let xyzToRgb = ((x, y, z, alpha)) => {
  `rgba((
    srgbGamma(3.2404542 **. x -. 1.5371385 **. y -. 0.4985314 **. z)
    |> toInt
    |> rgbClamp,
    srgbGamma((-0.9692660) **. x +. 1.8760108 **. y +. 0.0415560 **. z)
    |> toInt
    |> rgbClamp,
    srgbGamma(0.0556434 **. x -. 0.2040259 **. y +. 1.0572252 **. z)
    |> toInt
    |> rgbClamp,
    alpha,
  ));
};
let toRGB = lab => {
  lab |> labToXyz |> xyzToRgb;
};
let p3Gamma = r => {
  r <= 0.0031308 ? 12.92 **. r : 1.055 **. r ** (1. / 2.4) -. 0.055;
};

let xyzToP3 = ((x, y, z, alpha)) => {
  `p3((
    p3Gamma(
      2.4041476775378706282
      **. x
      -. 0.99010703944210726052
      **. y
      -. 0.39759019425373693677
      **. z,
    )
    |> p3Clamp,
    p3Gamma(
      (-0.84239097992588684688)
      **. x
      +. 1.7990595398556119185
      **. y
      +. 0.015970230317527190242
      **. z,
    )
    |> p3Clamp,
    p3Gamma(
      0.04838763487334053893
      **. x
      -. 0.097525459078352834297
      **. y
      +. 1.2739363577809163373
      **. z,
    )
    |> p3Clamp,
    alpha,
  ));
};

let toP3 = lab => {
  lab |> labToXyz |> xyzToP3;
};

let p3Linear = r => {
  let lab2 = r;
  if (lab2 <= 0.04045) {
    lab2 / 12.92;
  } else {
    ((lab2 +. 0.055) / 1.055) ** 2.4;
  };
};

let srgbLinear = r => {
  let lab2 = r / 255.;
  if (lab2 <= 0.04045) {
    lab2 / 12.92;
  } else {
    ((lab2 +. 0.055) / 1.055) ** 2.4;
  };
};

let xyz_lab = t =>
  if (t > Constants.t3) {
    t ** (1. / 3.);
  } else {
    t / Constants.t2 +. Constants.t0;
  };

let labxyzToLab = ((x, y, z, alpha)) => {
  let x0 = xyz_lab(x / Constants.xn);
  let y0 = xyz_lab(y / Constants.yn);
  let z0 = xyz_lab(z / Constants.zn);
  let l = y0 **. 116. -. 16.;
  let a = (x0 -. y0) **. 500.;
  let b = (y0 -. z0) **. 200.;
  `lab((l, a, b, alpha));
};

let rgbToXyz = ((r_, g_, b_, alpha: float)) => {
  let r = srgbLinear(r_ |> float_of_int);
  let g = srgbLinear(g_ |> float_of_int);
  let b = srgbLinear(b_ |> float_of_int);
  // D65
  //  [0.4124564,  0.3575761,  0.1804375],
  // [0.2126729,  0.7151522,  0.0721750],
  // [0.0193339,  0.1191920,  0.9503041]

  // d65 -> d50
  // 1.0478112  0.0228866 -0.0501270
  //  0.0295424  0.9904844 -0.0170491
  // -0.0092345  0.0150436  0.7521316
  let x =
    xyz_lab(
      (0.4124564 **. r +. 0.3575761 **. g +. 0.1804375 **. b) / Constants.xn,
    );
  let y =
    xyz_lab(
      (0.2126729 **. r +. 0.7151522 **. g +. 0.0721750 **. b) / Constants.yn,
    );
  let z =
    xyz_lab(
      (0.0193339 **. r +. 0.1191920 **. g +. 0.9503041 **. b) / Constants.zn,
    );
  (x, y, z, alpha);
};

let p3ToXyz = ((r_, g_, b_, alpha)) => {
  let r = srgbLinear(r_ |> float_of_int);
  let g = srgbLinear(g_ |> float_of_int);
  let b = srgbLinear(b_ |> float_of_int);
  let x =
    xyz_lab((0.5151 **. r +. 0.292 **. g +. 0.1571 **. b) / Constants.xn);
  let y =
    xyz_lab((0.2412 **. r +. 0.6922 **. g +. 0.0666 **. b) / Constants.yn);
  let z =
    xyz_lab(((-0.0011) **. r +. 0.0419 **. g +. 0.7841 **. b) / Constants.zn);
  (x, y, z, alpha);
};

let rgbxyzToLab = ((x, y, z, alpha: float)) => {
  let l = 116. **. y -. 16.;
  `lab((l < 0. ? 0. : l, 500. **. (x -. y), 200. **. (y -. z), alpha));
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
    x1 +. f **. (x2 -. x1),
    y1 +. f **. (y2 -. y1),
    z1 +. f **. (z2 -. z1),
    (a1 +. a2) / 2.,
  )
  |> labxyzToLab;
};

let luminance_x = x => {
  let x1 = (x |> float_of_int) / 255.;
  x1 <= 0.03928 ? x1 / 12.92 : ((x1 +. 0.055) / 1.055) ** 2.4;
};

let luminance =
  fun
  | `lab(l, _a, _b, _alpha) => l;

let contrast = (lab1, lab2) => {
  let lum1 = lab1 |> luminance;
  let lum2 = lab2 |> luminance;

  21. **. (0.01 **. abs_float(lum1 -. lum2));
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

let multiplyMatrix =
    (((x1, x2, x3), (y1, y2, y3), (z1, z2, z3)), (a, b, c)) => {
  (
    x1 **. a +. x2 **. b +. x3 **. c,
    y1 **. a +. y2 **. b +. y3 **. c,
    z1 **. a +. z2 **. b +. z3 **. c,
  );
};

let mapTriple = (fn, (a, b, c)) => (fn(a), fn(b), fn(c));
let intOfFloat = f => f +. 0.5 |> int_of_float;

module Rgb2 = {
  // Convert from linear sRGB to CIE XYZ
  let linearRgbToXyz =
    multiplyMatrix((
      (0.4124564, 0.3575761, 0.1804375),
      (0.2126729, 0.7151522, 0.0721750),
      (0.0193339, 0.1191920, 0.9503041),
    ));

  let linearP3ToXyz =
    multiplyMatrix((
      (0.4865709486482162, 0.26566769316909306, 0.1982172852343625),
      (0.2289745640697488, 0.6917385218365064, 0.079286914093745),
      (0.0000000000000000, 0.04511338185890264, 1.043944368900976),
    ));

  // Convert from a D65 whitepoint (used by sRGB) to the D50 whitepoint used in Lab, with the Bradford transform [Bradford-CAT]
  let d65ToD50 =
    multiplyMatrix((
      (1.0478112, 0.0228866, (-0.0501270)),
      (0.0295424, 0.9904844, (-0.0170491)),
      ((-0.0092345), 0.0150436, 0.7521316),
    ));

  let e = 216. / 24389.; // 6^3/29^3
  let k = 24389. / 27.; // 29^3/3^3
  let d50White = (0.96422, 1., 0.82521); // D50 reference white
  let xyzToLab = ((x1, y1, z1)) => {
    // Assuming XYZ is relative to D50, convert to CIE Lab
    // from CIE standard, which now defines these as a rational fraction
    let (wX, wY, wZ) = d50White;

    // compute xyz, which is XYZ scaled relative to reference white
    // let xyz = XYZ.map((value, i) => value / white[i]);
    let xyz = (x1 / wX, y1 / wY, z1 / wZ);

    // now compute f
    let (f0, f1, f2) =
      mapTriple(v => v > e ? v ** (1. / 3.) : (k **. v +. 16.) / 116., xyz);

    (
      116. **. f1 -. 16., // L
      500. **. (f0 -. f1), // a
      200. **. (f1 -. f2) // b
    );
  };

  let labToXyz = ((l, a, b)) => {
    // Convert Lab to D50-adapted XYZ
    // http://www.brucelindbloom.com/index.html?Eqn_RGB_XYZ_Matrix.html

    // compute f, starting with the luminance-related term
    let f1 = (l +. 16.) / 116.;
    let f0 = a / 500. +. f1;
    let f2 = f1 -. b / 200.;

    // compute xyz
    let x = f0 ** 3. > e ? f0 ** 3. : (116. **. f0 -. 16.) / k;
    let y = l > k **. e ? ((l +. 16.) / 116.) ** 3. : l / k;
    let z = f2 ** 3. > e ? f2 ** 3. : (116. **. f2 -. 16.) / k;
    let (wX, wY, wZ) = d50White;
    // Compute XYZ by scaling xyz by reference white
    (x *. wX, y *. wY, z *. wZ);
  };

  let d50ToD65 =
    multiplyMatrix((
      (0.9555766, (-0.0230393), 0.0631636),
      ((-0.0282895), 1.0099416, 0.0210077),
      (0.0122982, (-0.0204830), 1.3299098),
    ));

  let xyzToRGB =
    multiplyMatrix((
      (3.2404542, (-1.5371385), (-0.4985314)),
      ((-0.9692660), 1.8760108, 0.0415560),
      (0.0556434, (-0.2040259), 1.0572252),
    ));

  let xyzToP3 =
    multiplyMatrix((
        (
        (2.4041476775378706282, 0.99010703944210726052, 0.39759019425373693677),
        (
          (-0.84239097992588684688),
          1.7990595398556119185,
          0.015970230317527190242,
        ),
        (
          0.04838763487334053893,
          0.097525459078352834297,
          1.2739363577809163373,
        ),
      )
    ));

  let rec rgbToLab =
    fun
    | `rgb(r, g, b) => `rgba(r, g, b, 1.) |> rgbToLab
    | `rgba(r, g, b, alpha) => {
        (r, g, b)
        |> mapTriple(float_of_int)
        |> mapTriple(srgbLinear)
        |> linearRgbToXyz
        |> d65ToD50
        |> xyzToLab
        |> mapTriple(toFixed(4))
        |> (((l, a, b)) => `lab((l, a, b, alpha)));
      };

  let labToRgb =
    fun
    | `lab(l, a, b, alpha) => {
        (l, a, b)
        |> labToXyz
        |> d50ToD65
        |> xyzToRGB
        |> mapTriple(srgbGamma)
        |> mapTriple(intOfFloat)
        |> mapTriple(rgbClamp)
        |> (((r, g, b)) => `rgba((r, g, b, alpha)));
      };

  let p3ToLab =
    fun
    | `p3(r, g, b, alpha) => {
        (r, g, b)
        |> mapTriple(p3Linear)
        |> linearP3ToXyz
        |> d65ToD50
        |> xyzToLab
        |> mapTriple(toFixed(4))
        |> (((l, a, b)) => `lab((l, a, b, alpha)));
      };

  let labToP3 =
    fun
    | `lab(l, a, b, alpha) => {
        (l, a, b)
        |> labToXyz
        |> d50ToD65
        |> xyzToP3
        |> mapTriple(p3Gamma)
        |> mapTriple(p3Clamp)
        |> mapTriple(toFixed(4))
        |> (((r, g, b)) => `p3((r, g, b, alpha)));
      };
};