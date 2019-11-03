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

let multiplyMatrix =
    (((x1, x2, x3), (y1, y2, y3), (z1, z2, z3)), (a, b, c)) => {
  (
    x1 *. a +. x2 *. b +. x3 *. c,
    y1 *. a +. y2 *. b +. y3 *. c,
    z1 *. a +. z2 *. b +. z3 *. c,
  );
};

let mapTriple = (fn, (a, b, c)) => (fn(a), fn(b), fn(c));
let intOfFloat = f => f +. 0.5 |> int_of_float;

let rgbClamp = clamp(0, 255);
let p3Clamp = a => clamp(0., 1.0, a) |> toPrecision(4);
let toInt = f => f +. 0.5 |> int_of_float;

let rgbGamma = r => {
  r <= 0.0031308 ? 12.92 *. r : 1.055 *. r ** (1. /. 2.4) -. 0.055;
};
let srgbGamma = r => 255. *. rgbGamma(r);

let rgbLinear = r => {
  let lab2 = r;
  if (lab2 <= 0.04045) {
    lab2 /. 12.92;
  } else {
    ((lab2 +. 0.055) /. 1.055) ** 2.4;
  };
};

let srgbLinear = r => rgbLinear(r /. 255.);

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

let e = 216. /. 24389.; // 6^3/29^3
let k = 24389. /. 27.; // 29^3/3^3
let d50White = (0.96422, 1., 0.82521); // D50 reference white
let xyzToLab = ((x1, y1, z1)) => {
  // Assuming XYZ is relative to D50, convert to CIE Lab
  // from CIE standard, which now defines these as a rational fraction
  let (wX, wY, wZ) = d50White;

  // compute xyz, which is XYZ scaled relative to reference white
  // let xyz = XYZ.map((value, i) => value /. white[i]);
  let xyz = (x1 /. wX, y1 /. wY, z1 /. wZ);

  // now compute f
  let (f0, f1, f2) =
    mapTriple(v => v > e ? v ** (1. /. 3.) : (k *. v +. 16.) /. 116., xyz);

  (
    116. *. f1 -. 16., // L
    500. *. (f0 -. f1), // a
    200. *. (f1 -. f2) // b
  );
};

let labToXyz = ((l, a, b)) => {
  // Convert Lab to D50-adapted XYZ
  // http://www.brucelindbloom.com/index.html?Eqn_RGB_XYZ_Matrix.html

  // compute f, starting with the luminance-related term
  let f1 = (l +. 16.) /. 116.;
  let f0 = a /. 500. +. f1;
  let f2 = f1 -. b /. 200.;

  // compute xyz
  let x = f0 ** 3. > e ? f0 ** 3. : (116. *. f0 -. 16.) /. k;
  let y = l > k *. e ? ((l +. 16.) /. 116.) ** 3. : l /. k;
  let z = f2 ** 3. > e ? f2 ** 3. : (116. *. f2 -. 16.) /. k;
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
    (2.493496911941425, (-0.9313836179191239), (-0.40271078445071684)),
    ((-0.8294889695615747), 1.7626640603183463, 0.023624685841943577),
    (0.03584583024378447, (-0.07617238926804182), 0.9568845240076872),
  ));

let rec fromRGB =
  fun
  | `rgb(r, g, b) => `rgba((r, g, b, 1.)) |> fromRGB
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

let toRGB =
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

let fromP3 =
  fun
  | `p3(r, g, b, alpha) => {
      (r, g, b)
      |> mapTriple(rgbLinear)
      |> linearP3ToXyz
      |> d65ToD50
      |> xyzToLab
      |> mapTriple(toFixed(4))
      |> (((l, a, b)) => `lab((l, a, b, alpha)));
    };

let toP3 =
  fun
  | `lab(l, a, b, alpha) => {
      (l, a, b)
      |> labToXyz
      |> d50ToD65
      |> xyzToP3
      |> mapTriple(rgbGamma)
      |> mapTriple(p3Clamp)
      |> mapTriple(toFixed(3))
      |> (((r, g, b)) => `p3((r, g, b, alpha)));
    };

let toLab =
  fun
  | `lab(_, _, _, _) as lab => lab
  | `rgb(_, _, _) as rgb => fromRGB(rgb)
  | `rgba(_, _, _, _) as rgba => fromRGB(rgba)
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

let getTuple =
  fun
  | `lab(l, a, b, al) => (l, a, b, al);

let mix = (f, lab1, lab2) => {
  let (l1, a1, b1, alpha1) = lab1 |> getTuple;
  let (l2, a2, b2, alpha2) = lab2 |> getTuple;
  let (x1, y1, z1) = (l1, a1, b1) |> labToXyz;
  let (x2, y2, z2) = (l2, a2, b2) |> labToXyz;
  (x1 +. f *. (x2 -. x1), y1 +. f *. (y2 -. y1), z1 +. f *. (z2 -. z1))
  |> xyzToLab
  |> (((l, a, b)) => `lab((l, a, b, (alpha1 +. alpha2) /. 2.)));
};

let luminance_x = x => {
  let x1 = (x |> float_of_int) /. 255.;
  x1 <= 0.03928 ? x1 /. 12.92 : ((x1 +. 0.055) /. 1.055) ** 2.4;
};

let luminance =
  fun
  | `lab(l: float, _a, _b, _alpha) => l;

let highlight = (~baseColor, factor) => {
  let baseL = luminance(baseColor);
  fun
  | `lab(l, _a, _b, _alpha) as c =>
    lighten(
      (baseL > 50. ? l +. (factor |> float_of_int) > 100. ? (-1) : 1 : 1)
      * factor,
      c,
    );
};

let contrast = (lab1, lab2) => {
  let lum1 = lab1 |> luminance;
  let lum2 = lab2 |> luminance;
  21. *. (0.01 *. abs_float(lum1 -. lum2));
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