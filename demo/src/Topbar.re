open Core;
open UI;

[@react.component]
let make = (~toggleTheme=ignore, ()) => {
  <View>
    <>
      <Box height={Styles.getSpace(`number(11))} />
      <Box
        backgroundColor={`highlight((8, `body))}
        padding={`padding(`single)}
        width={`unsafeCustomValue(Css.vw(100.))}
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
              margin={`margin(`half)}
              href="https://github.com/eldh/revy"
              tintColor=`body>
              "Github"
            </Link>
            <Link.Button
              margin={`margin(`half)} onClick={_ => toggleTheme()} tintColor=`body>
              "Toggle dark theme"
            </Link.Button>
          </Box>
        </>
      </Box>
    </>
  </View>;
};