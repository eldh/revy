open Revy.Core;
open Revy.UI;

[@react.component]
let make = (~toggleTheme=ignore, ()) => {
  <View>
    <>
      <Box
        h={Styles.useSpace(Space.Number(11))}
      />
      <Box
        backgroundColor={
          Color.Highlight(
            20, Color.BodyBackground)
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
            <Text.String size=1 weight=Type.Bold> "Revy" </Text.String>
          </Box>
          <Box direction=`row grow=0.>
            <Link
              m={Revy.Core.Margin(Space.Half)}
              href="https://github.com/eldh/revy"
              color=Revy.Core.Color.Secondary>
              "Github"
            </Link>
            <Link.Button
              m={Revy.Core.Margin(Space.Half)}
              onClick={_ => toggleTheme()}
              color=Revy.Core.Color.Secondary>
              "Toggle dark theme"
            </Link.Button>
          </Box>
        </>
      </Box>
    </>
  </View>;
};