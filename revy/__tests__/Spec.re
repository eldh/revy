open Jest;
open Lab;

test("fromRGB", _ =>
  Expect.(
    expect(fromRGB(`rgb((255, 255, 255))))
    |> toEqual(
         `lab((
           100.,
           (-0.036993142251),
           0.015189611659,
           1.,
         )),
       )
  )
);

test("toP3", _ =>
  Expect.(
    expect(toP3(`lab((100., 0., 0., 1.))))
    |> toEqual(`p3((1., 1., 1., 1.)))
  )
);
let p_ = 100000000.;
let ( ** ) = (a, b) => a *. p_ *. (b *. p_) /. (p_ *. p_);
let (/) = (a, b) => a *. p_ /. (b *. p_);

// Js.log2("0.0000000002 * 0.0000003", 1.0002 *. 0.03);
// Js.log2("0.0000000002 * 0.0000003", 1.0002 ** 0.03);
// Js.log2("0.0000000002 * 0.0000003", 0.3 / 0.2);
// Js.log2("0.0000000002 * 0.0000003", 0.3 /. 0.2);

test("labToXYZ", _ =>
  Expect.(
    expect(labToXyz(`lab((100., 0., 0., 1.))))
    |> toEqual((0.964214, 1., 0.825188, 1.))
  )
);

test("xyzToP3", _ =>
  Expect.(
    expect(xyzToP3((0.964214, 1., 0.825188, 1.)))
    |> toEqual(`p3((1., 1., 1., 1.)))
  )
);

describe("isContrastOk", () => {
  open Expect;
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
  open Expect;
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