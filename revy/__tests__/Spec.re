open Jest;
open Lab;

test("fromRGB", _ =>
  Expect.(
    expect(fromRGB((255, 255, 255)))
    |> toEqual((
         100.00000386666655,
         (-0.000016666666158293708),
         0.000006666666463317483,
       ))
  )
);

describe("isContrastOk", () => {
  open Expect;
  test("(50, 50, 50), (255, 192, 0)", _ =>
    isContrastOk((50, 50, 50), (255, 192, 0)) |> expect |> toBe(true)
  );
  test("(75, 75, 75), (255, 192, 0)", _ =>
    isContrastOk((75, 75, 75), (255, 192, 0)) |> expect |> toBe(true)
  );
  test("(0, 192, 255), (255, 192, 0))", _ =>
    isContrastOk((0, 192, 255), (255, 192, 0)) |> expect |> toBe(false)
  );
});