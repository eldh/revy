open Jest;
open Lab;
open Expect;

test("fromRGB", _ =>
  expect(fromRGB(`rgba((255, 255, 255, 1.))))
  |> toEqual(`lab((100., 0., 0., 1.)))
);
test("fromRGB dark bg to p3", _ =>
  expect(fromRGB(`rgba((20, 20, 20, 1.))) |> toP3
  )
  |> toEqual(`p3((0.078, 0.078, 0.078, 1.)))
);
test("toRGB", _ =>
  expect(toRGB(`lab((100., 0., 0., 1.))))
  |> toEqual(`rgba((255, 255, 255, 1.)))
);

test("toP3", _ =>
  expect(toP3(`lab((100., 0., 0., 1.)))) |> toEqual(`p3((1., 1., 1., 1.)))
);
test("p3", _ =>
  expect(toP3(`lab((100., 0., 0., 1.))) |> fromP3)
  |> toEqual(`lab((100., (-0.0037), (-0.014), 1.)))
);
test("fromP3", _ =>
  expect(fromP3(`p3((1., 1., 1., 1.))))
  |> toEqual(`lab((100., (-0.0037), (-0.014), 1.)))
);
test("fromP3 green", _ =>
  expect(fromP3(`p3((0., 1., 0., 1.))))
  |> toEqual(`lab((86.61, (-106.5597), 102.9, 1.)))
);
test("fromP3 red", _ =>
  expect(fromP3(`p3((1., 0., 0., 1.))))
  |> toEqual(`lab((56.2, 94.47, 98.88, 1.)))
);

test("toP3", _ =>
  expect(toP3(`lab((100., 0., 0., 1.)))) |> toEqual(`p3((1., 1., 1., 1.)))
);

test("labToXYZ", _ =>
  expect(labToXyz((100., 0., 0.))) |> toEqual((0.96422, 1., 0.82521))
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