let useLinkStyle = (~color as color_, ()) =>
  Css.[
    display(`inline),
    textDecoration(`underline),
    cursor(`pointer),
    borderStyle(`none),
    color(Theme.Styles.useColor(color_)),
    transition(~duration=200, "color"),
    hover([color(Theme.Styles.useColor(~highlight=-40, color_))]),
    focus([
      outlineStyle(`none),
      boxShadow(
        ~y=px(0),
        ~blur=px(0),
        ~spread=px(1),
        ~inset=true,
        Theme.(Styles.useColor(Color.Primary)),
      ),
    ]),
    active([
      outlineStyle(`none),
      boxShadow(
        ~y=px(0),
        ~blur=px(0),
        ~spread=px(1),
        ~inset=true,
        Theme.(Styles.useColor(Color.Transparent)),
      ),
    ]),
  ];

[@react.component]
let make =
    (
      ~href,
      ~onClick=ignore,
      ~color=Theme.Color.Primary,
      ~size=0,
      ~lineHeight=0,
      ~m=Theme.(Margin(Space.Auto)),
      ~weight=Theme.Type.Normal,
      ~children,
      (),
    ) => {
  let textStyle = Text.useTextStyles(~color, ~size, ~lineHeight, ~weight, ());
  let linkStyle = useLinkStyle(~color, ());
  <a
    href
    onClick
    className={
      [textStyle, linkStyle, Theme.Styles.useMargin(m)]
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
        ~color=Theme.Color.Primary,
        ~size=0,
        ~lineHeight=0,
        ~m=Theme.(Margin(Space.Auto)),
        ~weight=Theme.Type.Normal,
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
        [textStyle, linkStyle, Theme.Styles.useMargin(m)] |> List.concat
      }>
      children->React.string
    </TouchableOpacity>;
  };
};