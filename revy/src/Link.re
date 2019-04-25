let useLinkStyle = (~color as color_, ()) =>
  Css.[
    display(`inline),
    textDecoration(`underline),
    cursor(`pointer),
    borderStyle(`none),
    color(Revy.Core.Styles.useColor(color_)),
    transition(~duration=200, "color"),
    hover([color(Revy.Core.Styles.useColor(~highlight=-40, color_))]),
    focus([
      outlineStyle(`none),
      boxShadow(
        ~y=px(0),
        ~blur=px(0),
        ~spread=px(1),
        ~inset=true,
        Revy.Core.(Styles.useColor(Color.Primary)),
      ),
    ]),
    active([
      outlineStyle(`none),
      boxShadow(
        ~y=px(0),
        ~blur=px(0),
        ~spread=px(1),
        ~inset=true,
        Revy.Core.(Styles.useColor(Color.Transparent)),
      ),
    ]),
  ];

[@react.component]
let make =
    (
      ~href,
      ~onClick=ignore,
      ~color=Revy.Core.Color.Primary,
      ~size=0,
      ~lineHeight=0,
      ~m=Revy.Core.(Margin(Space.Auto)),
      ~weight=Revy.Core.Type.Normal,
      ~children,
      (),
    ) => {
  let textStyle = Text.useTextStyles(~color, ~size, ~lineHeight, ~weight, ());
  let linkStyle = useLinkStyle(~color, ());
  <a
    href
    onClick
    className={
      [textStyle, linkStyle, Revy.Core.Styles.useMargin(m)]
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
        ~color=Revy.Core.Color.Primary,
        ~size=0,
        ~lineHeight=0,
        ~m=Revy.Core.(Margin(Space.Auto)),
        ~weight=Revy.Core.Type.Normal,
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
        [textStyle, linkStyle, Revy.Core.Styles.useMargin(m)] |> List.concat
      }>
      children->React.string
    </TouchableOpacity>;
  };
};