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
         )),
       )
  )
);

describe("isContrastOk", () => {
  open Expect;
  test("`rgb(50, 50, 50), `rgb(255, 192, 0)", _ =>
    isContrastOk(`rgb((50, 50, 50)), `rgb((255, 192, 0)))
    |> expect
    |> toBe(true)
  );
  test("`rgb(75, 75, 75), `rgb(255, 192, 0)", _ =>
    isContrastOk(`rgb((75, 75, 75)), `rgb((255, 192, 0)))
    |> expect
    |> toBe(true)
  );
  test("`rgb(0, 192, 255), `rgb(255, 192, 0))", _ =>
    isContrastOk(`rgb((0, 192, 255)), `rgb((255, 192, 0)))
    |> expect
    |> toBe(false)
  );
});

describe("getContrastColor", () =>
  Expect.(
    test("`rgb(110, 181, 247)", _ =>
      getContrastColor(`rgb((110, 181, 247)))
      |> expect
      |> toEqual(`rgb((0, 9, 59)))
    )
  )
);