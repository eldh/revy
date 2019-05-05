open TestFramework;

Couloir.Lab.fromRGB((255, 255, 255));

describe("my first test suite", ({test}) =>
  test("1 + 1 should equal 2", ({expect}) =>
    expect.int(1 + 1).toBe(2)
  )
);

print_endline("Add Your Test Cases Somewhere");