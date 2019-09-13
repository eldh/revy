open Jest;
open Lab;
open Expect;

test("fromRGB", _ =>
  expect(fromRGB(`rgb((255, 255, 255))))
  |> toEqual(`lab((100., (-0.036993142251), 0.015189611659, 1.)))
);
test("rgbToXYZ", _ =>
  expect(rgbToXyz((255, 255, 255, 1.))) |> toEqual((0.9643, 1., 0.8251, 1.))
);
describe("Rgb2", () => {
  test("Rgb2.rgbToLab", _ =>
    expect(Rgb2.rgbToLab(`rgb((255, 255, 255, 1.))))
    |> toEqual(`lab((100., 0., 0., 1.)))
  );
  test("Rgb2.labToRgb", _ =>
    expect(Rgb2.labToRgb(`lab((100., 0., 0., 1.))))
    |> toEqual(`rgb((255, 255, 255, 1.)))
  );
  test("Rgb2.labToP3", _ =>
    expect(Rgb2.labToP3(`lab((100., 0., 0., 1.))))
    |> toEqual(`p3((1., 1., 1., 1.)))
  );
  test("p3", _ =>
    expect(Rgb2.labToP3(`lab((100., 0., 0., 1.))) |> Rgb2.p3ToLab)
    |> toEqual(`lab((100., (-0.0037), (-0.014), 1.)))
  );
  test("Rgb2.p3ToLab", _ =>
    expect(Rgb2.p3ToLab(`p3((1., 1., 1., 1.))))
    |> toEqual(`lab((100., (-0.0037), (-0.014), 1.)))
  );
  test("Rgb2.p3ToLab green", _ =>
    expect(Rgb2.p3ToLab(`p3((0., 1., 0., 1.))))
    |> toEqual(`lab((86.61, (-106.5597), 102.9, 1.)))
  );
  test("Rgb2.p3ToLab red", _ =>
    expect(Rgb2.p3ToLab(`p3((1., 0., 0., 1.))))
    |> toEqual(`lab((56.2, 94.47, 98.88, 1.)))
  );
});

test("toP3", _ =>
  expect(toP3(`lab((100., 0., 0., 1.)))) |> toEqual(`p3((1., 1., 1., 1.)))
);

test("labToXYZ", _ =>
  expect(labToXyz(`lab((100., 0., 0., 1.))))
  |> toEqual((0.964214, 1., 0.825188, 1.))
);

test("xyzToP3", _ =>
  expect(xyzToP3((0.964214, 1., 0.825188, 1.)))
  |> toEqual(`p3((1., 1., 1., 1.)))
);

describe("isContrastOk", () => {
  test("`rgb(50, 50, 50), `rgb(255, 192, 0)", _ =>
    isContrastOk(
      `rgb((50, 50, 50)) |> fromRGB,
      `rgb((255, 192, 0)) |> fromRGB,
    )
    |> expect
    |> toBe(true)
  );
  test("`rgb(75, 75, 75), `rgb(255, 192, 0)", _ =>
    isContrastOk(
      `rgb((75, 75, 75)) |> fromRGB,
      `rgb((255, 192, 0)) |> fromRGB,
    )
    |> expect
    |> toBe(true)
  );
  test("`rgb(0, 192, 255), `rgb(255, 192, 0))", _ =>
    isContrastOk(
      `rgb((0, 192, 255)) |> fromRGB,
      `rgb((255, 192, 0)) |> fromRGB,
    )
    |> expect
    |> toBe(false)
  );
});

describe("getContrastColor", () => {
  test("`rgb(94,94,94)", _ =>
    getContrastColor(`rgb((94, 94, 94)) |> fromRGB)
    |> expect
    |> toEqual(`lab((100., 0., 0., 1.)))
  );
  test("`rgb(110, 181, 247)", _ =>
    getContrastColor(`rgb((110, 181, 247)) |> fromRGB)
    |> expect
    |> toEqual(`lab((10., 0., 0., 1.)))
  );
  test("`rgb(110, 181, 247)", _ =>
    getContrastColor(`rgb((255, 80, 61)) |> fromRGB)
    |> expect
    |> toEqual(`lab((10., 0., 0., 1.)))
  );
});