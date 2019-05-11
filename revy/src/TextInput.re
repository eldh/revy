let useInputStyles = (~m, ()) => {
  Revy.Core.(
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
        backgroundColor(
          Styles.useIsLight()
            ? Css.rgba(0, 0, 0, 0.05) : Css.rgba(255, 255, 255, 0.05),
        ),
        color(Styles.useColor(`bodyText)),
        boxShadow(
          ~y=px(0),
          ~blur=px(0),
          ~spread=px(1),
          ~inset=true,
          Styles.useIsLight()
            ? Css.rgba(0, 0, 0, 0.07) : Css.rgba(255, 255, 255, 0.07),
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
          ~color=`quietText,
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