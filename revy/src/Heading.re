type level =
  | H1
  | H2
  | H3
  | H4
  | H5;

[@react.component]
let make =
    (
      ~level=H1,
      ~style=?,
      ~m=Revy.Core.(Margin2(Space.NoSpace, Space.NoSpace)),
      ~children,
      (),
    ) => {
  let (size, weight, color, tag) =
    switch (level) {
    | H1 => (5, Revy.Core.Type.Bold, Revy.Core.Color.BodyText, "h1")
    | H2 => (4, Revy.Core.Type.Bold, Revy.Core.Color.BodyText, "h2")
    | H3 => (3, Revy.Core.Type.Bold, Revy.Core.Color.BodyText, "h3")
    | H4 => (2, Revy.Core.Type.Bold, Revy.Core.Color.BodyText, "h4")
    | H5 => (1, Revy.Core.Type.Bold, Revy.Core.Color.BodyText, "h5")
    };

  <Text.Block ?style size weight color tag m> children </Text.Block>;
};