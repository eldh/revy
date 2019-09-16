[@react.component]
let make =
    (
      ~level=`h1,
      ~style=?,
      ~margin=`margin2((`noSpace, `noSpace)),
      ~children,
      (),
    ) => {
  let (size, weight, tag) =
    switch (level) {
    | `h1 => (5, `bold, "h1")
    | `h2 => (4, `bold, "h2")
    | `h3 => (3, `bold, "h3")
    | `h4 => (2, `bold, "h4")
    | `h5 => (1, `bold, "h5")
    };

  <Text.Block ?style size weight tag margin> children </Text.Block>;
};