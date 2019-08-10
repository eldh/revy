open Core;
let useLinkStyle = () =>
  Css.[
    display(`inline),
    textDecoration(`underline),
    cursor(`pointer),
    borderStyle(`none),
    color(Styles.useTextColor()),
    transition(~duration=200, "color"),
    hover([color(Styles.useTextColor(~highlight=-40, ()))]),
    focus([
      outlineStyle(`none),
      boxShadow(
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
        Styles.useColor(`transparent),
      ),
    ]),
  ];

[@react.component]
let make =
    (
      ~href,
      ~onClick=ignore,
      ~size=0,
      ~lineHeight=0,
      ~m=`margin(`auto),
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
      [textStyle, linkStyle, Styles.useMargin(m)] |> List.concat |> Css.style
    }>
    children->React.string
  </a>;
};

module Button = {
  [@react.component]
  let make =
      (
        ~onClick=ignore,
        ~size=0,
        ~lineHeight=0,
        ~m=`margin(`auto),
        ~weight=`normal,
        ~tintColor=?,
        ~children,
        (),
      ) => {
    let textStyle =
      Text.useTextStyles(~tintColor?, ~size, ~lineHeight, ~weight, ());
    let linkStyle = useLinkStyle();
    <TouchableOpacity
      tag="button"
      grow=0.
      onPress=onClick
      style={[textStyle, linkStyle, Styles.useMargin(m)] |> List.concat}>
      children->React.string
    </TouchableOpacity>;
  };
};