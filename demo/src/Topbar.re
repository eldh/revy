open Revy.Core;
open Revy.UI;

[@react.component]
let make = (~toggleTheme=ignore, ()) => {
  <View>
    <>
      <Box
        h={Styles.useSpace(`number(11))}
      />
      <Box
        backgroundColor={
          `highlight(
            8, `bodyBackground)
        }
        p={`padding(`single)}
        w={`escapeHatch(Css.vw(100.))}
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
            <Text.String size=1 weight=`bold> "Revy" </Text.String>
          </Box>
          <Box direction=`row grow=0.>
            <Link
              m={`margin(`half)}
              href="https://github.com/eldh/revy"
              color=`bodyText>
              "Github"
            </Link>
            <Link.Button
              m={`margin(`half)}
              onClick={_ => toggleTheme()}
              color=`bodyText>
              "Toggle dark theme"
            </Link.Button>
          </Box>
        </>
      </Box>
    </>
  </View>;
};