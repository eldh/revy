open Jest;
open Lab;

test("fromRGB", _ =>
  Expect.(
    expect(fromRGB(`rgb((255, 255, 255))))
    |> toEqual(
         `lab((
           100.00000386666655,
           (-0.000016666666158293708),
           0.000006666666463317483,
           1.,
         )),
       )
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
    getContrastColor(`rgb((94,94,94)) |> fromRGB)
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