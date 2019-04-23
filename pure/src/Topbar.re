open Theme;
[@react.component]
let make = (~toggleTheme=ignore, ()) => {
  <View>
    <>
      <Box
        h={Styles.useSpace(Space.Number(11))}
      />
      <Box
        backgroundColor={
          Color.EscapeHatch(
            Styles.useColor(~highlight=20, Color.BodyBackground),
          )
        }
        p={Padding(Space.Single)}
        w={Layout.Css(Css.vw(100.))}
        direction=`row
        align=`center
        alignContent=`center
        style=Css.[
          position(`fixed),
          top(px(0)),
          left(px(0)),
          boxShadow(~y=px(0), ~spread=px(1), Css.rgba(0, 0, 0, 0.2)),
          unsafe("willChange", "transition"),
          zIndex(1),
        ]>
        <>
          <Box grow=1. direction=`row>
            <Text.String size=1 weight=Type.Bold> "Pure" </Text.String>
          </Box>
          <Box direction=`row grow=0.>
            <Link
              m={Theme.Margin(Space.Half)}
              href="https://github.com/eldh/pure"
              color=Theme.Color.Secondary>
              "Github"
            </Link>
            <Link.Button
              m={Theme.Margin(Space.Half)}
              onClick={_ => toggleTheme()}
              color=Theme.Color.Secondary>
              "Toggle dark theme"
            </Link.Button>
          </Box>
        </>
      </Box>
    </>
  </View>;
};