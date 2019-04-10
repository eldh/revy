[@bs.config {jsx: 3}];

module Link = {
  [@react.component __MODULE__]
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
    let theme = React.useContext(ThemeContext.context);
    let textStyle =
      Text.useTextStyles(~color, ~size, ~lineHeight, ~weight, ());
    let linkStyle =
      Css.[
        width(pct(100.)),
        display(`block),
        textDecoration(`none),
        fontWeight(theme.fontWeight(Theme.Type.Bold)),
        padding(theme.space(Theme.Space.Single)),
        borderBottom(px(1), `solid, hsla(0, 0, 100, 0.2)),
        hover([Css.color(theme.color(~highlight=20, Theme.Color.Primary))]),
      ];
    <Box
      tag="a"
      grow=0.
      domProps={"href": href, "target": target}
      style={[textStyle, linkStyle]->List.concat}>
      children->React.string
    </Box>;
  };
};

[@react.component __MODULE__]
let make = () => {
  <View>
    <>
      <View style=Css.[width(px(200))] />
      <Box
        grow=0.
        backgroundColor=Theme.Color.HighlightBackground
        w={Theme.Layout.Px(200)}
        h={Css.vh(100.)}
        style=Css.[position(`fixed), top(px(0)), left(px(0))]>
        <>
          <Text size=1> "Pure" </Text>
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