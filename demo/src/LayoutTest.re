open Revy;
open Revy.Core;

[@react.component]
let make = (~toggleTheme=ignore, ()) => {
  <Box m={MarginBottom(Space.Number(10))}>
    <Box wrap=`wrap w=Layout.Full>
      <Heading level=Heading.H4> "Layout" </Heading>
      <Box
        style=Css.[maxWidth(pct(100.)), width(pct(100.))] direction=`row>
        <Box w=Layout.Full direction=`row>
          <>
            <Box
              p={Padding(Space.Single)}
              w=Layout.Full
              h={Css.em(10.)}
              backgroundColor=Color.Primary>
              <Text.String weight=Type.Bold color=Color.PrimaryText>
                "Full"
              </Text.String>
            </Box>
            <Box
              p={Padding(Space.Single)}
              w=Layout.Half
              h={Css.em(10.)}
              backgroundColor=Color.Success>
              <Text.String weight=Type.Bold color=Color.SuccessText>
                "Half"
              </Text.String>
            </Box>
            <Box
              p={Padding(Space.Single)}
              w={Layout.Responsive(Full, Full, Half)}
              h={Css.em(10.)}
              backgroundColor=Color.Warning>
              <Text.String weight=Type.Bold color=Color.WarningText>
                "Responsive(Full, Full, Half)"
              </Text.String>
            </Box>
            <Box
              p={Padding(Space.Single)}
              w=Layout.Third
              h={Css.em(10.)}
              backgroundColor=Color.Error>
              <Text.String weight=Type.Bold color=Color.ErrorText>
                "Third"
              </Text.String>
            </Box>
            <Box
              p={Padding(Space.Single)}
              w=Layout.Third
              h={Css.em(10.)}
              backgroundColor=Color.Primary>
              <Text.String weight=Type.Bold color=Color.PrimaryText>
                "Third"
              </Text.String>
            </Box>
            <Box
              p={Padding(Space.Single)}
              w=Layout.Third
              h={Css.em(10.)}
              backgroundColor=Color.Success>
              <Text.String weight=Type.Bold color=Color.SuccessText>
                "Third"
              </Text.String>
            </Box>
          </>
        </Box>
      </Box>
    </Box>
  </Box>;
};