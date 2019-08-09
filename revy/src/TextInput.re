let useInputStyles = (~m, ()) => {
  Core.(
    [
      Css.[
        Css.padding2(
          ~v=Styles.useSpace(~borderAdjust=0, `single),
          ~h=Styles.useSpace(~borderAdjust=0, `single),
        ),
        textDecoration(`none),
        cursor(`pointer),
        lineHeight(
          Styles.useLineHeight(~fontSize=Styles.useFontSize(0), ()),
        ),
        fontSize(Styles.useFontSize(0)),
        fontFamily(Styles.useFontFamily(`body)),
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
        ~id="",
        ~type_="text",
        ~disabled=false,
        ~styles=?,
        ~onFocus=ignore,
        ~onBlur=ignore,
        ~placeholder="",
        ~m=`margin(`noSpace),
        ~value,
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
          switch (styles) {
          | None => useInputStyles(~m, ())
          | Some(l) => [useInputStyles(~m, ()), l] |> List.concat
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
  let make = (~children, ~htmlFor, ()) => {
    <label
      htmlFor
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