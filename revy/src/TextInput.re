let useInputStyles = (~margin as m, ()) => {
  Core.(
    [
      Css.[
        Css.padding2(
          ~v=Styles.useSpace(~borderAdjust=0, `single),
          ~h=Styles.useSpace(~borderAdjust=0, `single),
        ),
        textDecoration(`none),
        lineHeight(
          Styles.useLineHeight(~fontSize=Styles.useFontSize(0), ()),
        ),
        fontSize(Styles.useFontSize(0)),
        fontFamily(Styles.useFontFamily(`body)),
        boxSizing(`borderBox),
        borderWidth(px(0)),
        borderColor(Styles.useColor(`transparent)),
        borderRadius(Css.px(6)),
        borderStyle(`solid),
        backgroundColor(Styles.useColor(~alpha=0.07, `bodyText)),
        color(Styles.useTextColor()),
        boxShadow(
          ~y=px(0),
          ~blur=px(0),
          ~spread=px(1),
          ~inset=true,
          Styles.useColor(~alpha=0.07, `bodyText),
        ),
        focus([
          outlineStyle(`none),
          boxShadow(
            ~y=px(0),
            ~blur=px(0),
            ~spread=px(1),
            ~inset=true,
            Styles.useColor(`primary),
          ),
        ]),
        disabled([opacity(0.7)]),
      ],
      Styles.useMargin(m),
    ]
    |> List.concat
  );
};
module Input = {
  [@react.component]
  let make =
      (
        ~onClick as _=?,
        ~onChange,
        ~label,
        ~value,
        ~id="",
        ~type_="text",
        ~disabled=false,
        ~style=?,
        ~onFocus=ignore,
        ~onBlur=ignore,
        ~placeholder="",
        ~margin as m=`margin(`noSpace),
        (),
      ) => {
    <input
      value
      id
      placeholder
      disabled
      onChange
      onFocus
      onBlur
      label
      className={
        (
          switch (style) {
          | None => useInputStyles(~margin=m, ())
          | Some(l) => [useInputStyles(~margin=m, ()), l] |> List.concat
          }
        )
        |> Css.style
      }
      type_
    />;
  };
};

module Label = {
  [@react.component]
  let make = (~children, ~htmlFor=?, ()) => {
    <label
      ?htmlFor
      className={
        Text.useTextStyles(
          ~size=-1,
          ~quiet=true,
          ~lineHeight=1,
          ~weight=`normal,
          (),
        )
        |> Css.style
      }>
      children
    </label>;
  };
};