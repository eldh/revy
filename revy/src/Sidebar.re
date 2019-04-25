module Link = {
  [@react.component]
  let make =
      (
        ~target="_self",
        ~href,
        ~color=Revy.Core.Color.Primary,
        ~size=0,
        ~lineHeight=0,
        ~weight=Revy.Core.Type.Normal,
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
        fontWeight(Revy.Core.Styles.useFontWeight(Revy.Core.Type.Bold)),
        padding(Revy.Core.Styles.useSpace(Revy.Core.Space.Single)),
        borderBottom(
          px(1),
          `solid,
          Revy.Core.Styles.useColor(~highlight=40, Revy.Core.Color.BodyBackground),
        ),
        hover([
          Css.color(
            Revy.Core.Styles.useColor(~highlight=20, Revy.Core.Color.Primary),
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
        backgroundColor=Revy.Core.(
          Color.EscapeHatch(
            Styles.useColor(~highlight=10, Color.BodyBackground),
          )
        )
        w={Revy.Core.Layout.Css(Css.px(200))}
        h={Css.vh(100.)}
        style=Css.[position(`fixed), top(px(0)), left(px(0))]>
        <>
          <Text.String size=1> "Revy" </Text.String>
          <Link href="#"> "Revy" </Link>
          <Link href="#"> "Revy" </Link>
          <Link href="#"> "Revy" </Link>
          <Link href="#"> "Revy" </Link>
          <Link href="#"> "Revy" </Link>
        </>
      </Box>
    </>
  </View>;
};