module Link = {
  [@react.component]
  let make =
      (
        ~target="_self",
        ~href,
        ~color=Theme.Color.Primary,
        ~size=0,
        ~lineHeight=0,
        ~weight=Theme.Type.Normal,
        ~children,
        (),
      ) => {
    let textStyle =
      Text.useTextStyles(~color, ~size, ~lineHeight, ~weight, ());
    let linkStyle =
      Css.[
        width(pct(100.)),
        display(`block),
        textDecoration(`none),
        fontWeight(Theme.Styles.useFontWeight(Theme.Type.Bold)),
        padding(Theme.Styles.useSpace(Theme.Space.Single)),
        borderBottom(
          px(1),
          `solid,
          Theme.Styles.useColor(~highlight=40, Theme.Color.BodyBackground),
        ),
        hover([
          Css.color(
            Theme.Styles.useColor(~highlight=20, Theme.Color.Primary),
          ),
        ]),
      ];
    <Box
      tag="a"
      grow=0.
      domProps={"href": href, "target": target}
      style={[textStyle, linkStyle]|>List.concat}>
      children->React.string
    </Box>;
  };
};

[@react.component]
let make = () => {
  <View>
    <>
      <View style=Css.[width(px(200))] />
      <Box
        grow=0.
        backgroundColor=Theme.(
          Color.EscapeHatch(
            Styles.useColor(~highlight=10, Color.BodyBackground),
          )
        )
        w={Theme.Layout.Css(Css.px(200))}
        h={Css.vh(100.)}
        style=Css.[position(`fixed), top(px(0)), left(px(0))]>
        <>
          <Text.String size=1> "Pure" </Text.String>
          <Link href="#"> "Pure" </Link>
          <Link href="#"> "Pure" </Link>
          <Link href="#"> "Pure" </Link>
          <Link href="#"> "Pure" </Link>
          <Link href="#"> "Pure" </Link>
        </>
      </Box>
    </>
  </View>;
};