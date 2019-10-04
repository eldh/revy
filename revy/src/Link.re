open Core;
let useLinkStyle = () => {
  Css.[
    display(`inline),
    textDecoration(`underline),
    cursor(`pointer),
    borderStyle(`none),
    color(Styles.useTextColor()),
    transition(~duration=200, "color"),
    hover([color(Styles.useTextColor(~highlight=-40, ()))]),
    focus([outlineStyle(`none)]),
    selector(
      ":focus:not(:active)",
      [
        textShadow(~blur=px(3), Styles.useColor(~alpha=0.4, `primary)),
        ...Animations.focus,
      ],
    ),
    active([opacity(0.5)]),
  ];
};
[@react.component]
let make =
    (
      ~href,
      ~onClick=ignore,
      ~size=0,
      ~lineHeight=0,
      ~margin=?,
      ~weight=`normal,
      ~tintColor=?,
      ~children,
      (),
    ) => {
  let textStyle =
    Text.useTextStyles(~tintColor?, ~size, ~lineHeight, ~weight, ());
  let linkStyle = useLinkStyle();
  <a
    href
    onClick
    className={
      [textStyle, linkStyle, Styles.useMargin(margin)]
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
        ~onClick,
        ~size=0,
        ~lineHeight=0,
        ~margin=?,
        ~weight=`normal,
        ~tintColor=?,
        ~children,
        (),
      ) => {
    let textStyle =
      Text.useTextStyles(~tintColor?, ~size, ~lineHeight, ~weight, ());
    let linkStyle = useLinkStyle(());
    <TouchableOpacity
      tag="button"
      grow=0.
      onPress=onClick
      style={[textStyle, linkStyle, Styles.useMargin(margin)] |> List.concat}>
      children->React.string
    </TouchableOpacity>;
  };
};