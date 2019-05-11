open Revy.Core;
let useLinkStyle = (~color as color_, ()) =>
  Css.[
    display(`inline),
    textDecoration(`underline),
    cursor(`pointer),
    borderStyle(`none),
    color(Styles.useColor(color_)),
    transition(~duration=200, "color"),
    hover([color(Styles.useColor(~highlight=-40, color_))]),
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
    active([
      outlineStyle(`none),
      boxShadow(
        ~y=px(0),
        ~blur=px(0),
        ~spread=px(1),
        ~inset=true,
        (Styles.useColor(`transparent)),
      ),
    ]),
  ];

[@react.component]
let make =
    (
      ~href,
      ~onClick=ignore,
      ~color=`primary,
      ~size=0,
      ~lineHeight=0,
      ~m=`margin(`auto),
      ~weight=`normal,
      ~children,
      (),
    ) => {
  let textStyle = Text.useTextStyles(~color, ~size, ~lineHeight, ~weight, ());
  let linkStyle = useLinkStyle(~color, ());
  <a
    href
    onClick
    className={
      [textStyle, linkStyle, Styles.useMargin(m)]
      |> List.concat
      |> Css.style
    }>
    children->React.string
  </a>;
};

module Button = {
  [@react.component]
  let make =
      (
        ~onClick=ignore,
        ~color=`primary,
        ~size=0,
        ~lineHeight=0,
        ~m=(`margin(`auto)),
        ~weight=`normal,
        ~children,
        (),
      ) => {
    let textStyle =
      Text.useTextStyles(~color, ~size, ~lineHeight, ~weight, ());
    let linkStyle = useLinkStyle(~color, ());
    <TouchableOpacity
      tag="button"
      grow=0.
      onPress=onClick
      style={
        [textStyle, linkStyle, Styles.useMargin(m)] |> List.concat
      }>
      children->React.string
    </TouchableOpacity>;
  };
};