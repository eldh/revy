exception InvalidValue(string);

let useTextStyles =
    (
      ~size,
      ~color as color_,
      ~lineHeight as lineHeight_,
      ~weight as weight_,
      (),
    ) => {
  let sizeVal = Theme.Styles.useFontSize(size);
  Css.[
    color(Theme.Styles.useColor(color_)),
    fontSize(sizeVal),
    overflow(`hidden),
    fontFamily(Theme.Styles.useFontFamily(Theme.Type.Body)),
    lineHeight(
      Theme.Styles.useLineHeight(
        ~fontSize=sizeVal,
        ~extraHeight=lineHeight_,
        (),
      ),
    ),
    fontWeight(Theme.Styles.useFontWeight(weight_)),
  ];
};

[@react.component]
let make =
    (
      ~weight=Theme.Type.Normal,
      ~size=0,
      ~tag="span",
      ~style=?,
      ~lineHeight=0,
      ~color=Theme.Color.BodyText,
      ~children,
      (),
    ) => {
  let styles = useTextStyles(~size, ~lineHeight, ~weight, ~color, ());
  EscapeHatch.use(
    tag,
    {
      "class": {
        (
          switch (style) {
          | Some(p) => [styles, p] |> List.concat
          | None => styles
          }
        )
        |> Css.style;
      },
      "children": children,
    },
  );
};

module String = {
  [@react.component]
  let make =
      (
        ~weight=Theme.Type.Normal,
        ~tag="span",
        ~size=0,
        ~style=?,
        ~lineHeight=0,
        ~color=Theme.Color.BodyText,
        ~children,
        (),
      ) => {
    let styles = useTextStyles(~size, ~lineHeight, ~weight, ~color, ());
    EscapeHatch.use(
      tag,
      {
        "className": {
          (
            switch (style) {
            | Some(p) => [styles, p] |> List.concat
            | None => styles
            }
          )
          |> Css.style;
        },
        "children": children |> React.string,
      },
    );
  };
};