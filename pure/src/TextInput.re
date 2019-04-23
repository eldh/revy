// let highlightShadow =
//   ThemeUtil.Style.shadows(
//     Css.[
//       boxShadow(~y=px(-1), ~blur=px(0), ~inset=true, hsla(0, 0, 100, 0.2)),
//       boxShadow(~y=px(1), ~blur=px(0), ~inset=true, hsla(0, 0, 0, 0.2)),
//     ],
//   );

let useInputStyles = (~m, ()) => {
  Theme.(
    [
      Css.[
        Css.padding2(
          ~v=Styles.useSpace(~borderAdjust=0, Space.Single),
          ~h=Styles.useSpace(~borderAdjust=0, Space.Single),
        ),
        textDecoration(`none),
        cursor(`pointer),
        lineHeight(
          Styles.useLineHeight(~fontSize=Styles.useFontSize(0), ()),
        ),
        fontSize(Styles.useFontSize(0)),
        fontFamily(Styles.useFontFamily(Theme.Type.Body)),
        borderWidth(px(0)),
        borderColor(Styles.useColor(Color.Transparent)),
        borderRadius(Css.px(6)),
        borderStyle(`solid),
        backgroundColor(
          Styles.useIsLight()
            ? Css.rgba(0, 0, 0, 0.05) : Css.rgba(255, 255, 255, 0.05),
        ),
        color(Styles.useColor(Color.BodyText)),
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
            Styles.useColor(Color.Primary),
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
        ~m=Theme.(Margin(Space.NoSpace)),
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
          ~color=Theme.Color.QuietText,
          ~lineHeight=1,
          ~weight=Theme.Type.Normal,
          (),
        )
        |> Css.style
      }>
      children
    </label>;
  };
};