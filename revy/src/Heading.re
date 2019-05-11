[@react.component]
let make =
    (~level=`h1, ~style=?, ~m=`margin2((`noSpace, `noSpace)), ~children, ()) => {
  let (size, weight, color, tag) =
    switch (level) {
    | `h1 => (5, `bold, `bodyText, "h1")
    | `h2 => (4, `bold, `bodyText, "h2")
    | `h3 => (3, `bold, `bodyText, "h3")
    | `h4 => (2, `bold, `bodyText, "h4")
    | `h5 => (1, `bold, `bodyText, "h5")
    };

  <Text.Block ?style size weight color tag m> children </Text.Block>;
};