exception InvalidValue(string);

let useTextStyles =
    (
      ~size,
      ~color as colorProp,
      ~lineHeight as lineHeightProp,
      ~weight as weightProp,
      (),
    ) => {
  let theme = React.useContext(ThemeContext.context);
  let sizeVal = theme.fontSize(size);
  Css.[
    color(theme.color(colorProp)),
    fontSize(sizeVal),
    overflow(`hidden),
    fontFamily(theme.fontFamily(Theme.Type.Body)),
    lineHeight(
      theme.lineHeight(~fontSize=sizeVal, ~extraHeight=lineHeightProp, ()),
    ),
    fontWeight(theme.fontWeight(weightProp)),
  ];
};

[@react.component]
let make =
    (
      ~weight=Theme.Type.Normal,
      ~size=0,
      ~style=?,
      ~lineHeight=0,
      ~color=Theme.Color.BodyText,
      ~children,
      (),
    ) => {
  let styles = useTextStyles(~size, ~lineHeight, ~weight, ~color, ());
  <span
    className={
      (
        switch (style) {
        | Some(p) => [styles, p]->List.concat
        | None => styles
        }
      )
      ->Css.style
    }>
    children
  </span>;
};

module String = {
  [@react.component]
  let make =
      (
        ~weight=Theme.Type.Normal,
        ~size=0,
        ~style=?,
        ~lineHeight=0,
        ~color=Theme.Color.BodyText,
        ~children,
        (),
      ) => {
    let styles = useTextStyles(~size, ~lineHeight, ~weight, ~color, ());
    <span
      className={
        (
          switch (style) {
          | Some(p) => [styles, p]->List.concat
          | None => styles
          }
        )
        ->Css.style
      }>
      children->React.string
    </span>;
  };
};