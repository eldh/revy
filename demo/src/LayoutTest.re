open Theme;

[@react.component]
let make = (~toggleTheme=ignore, ()) => {
  <Card m={Theme.Margin(Space.Single)} p={Theme.Padding(Space.Triple)}>
    <Box wrap=`wrap w=Theme.Layout.Full>
      <Text.String weight=Type.Bold> "Layout" </Text.String>
      <Box
        style=Css.[maxWidth(pct(100.)), width(pct(100.))] direction=`row>
        <Box w=Theme.Layout.Full direction=`row>
          <>
            <Box
              p={Padding(Space.Single)}
              w=Theme.Layout.Full
              h={Css.em(10.)}
              backgroundColor=Theme.Color.Primary>
              <Text.String weight=Type.Bold color=Theme.Color.PrimaryText>
                "Full"
              </Text.String>
            </Box>
            <Box
              p={Padding(Space.Single)}
              w=Theme.Layout.Half
              h={Css.em(10.)}
              backgroundColor=Theme.Color.Success>
              <Text.String weight=Type.Bold color=Theme.Color.SuccessText>
                "Half"
              </Text.String>
            </Box>
            <Box
              p={Padding(Space.Single)}
              w={Theme.Layout.Responsive(Full, Full, Half)}
              h={Css.em(10.)}
              backgroundColor=Theme.Color.Warning>
              <Text.String weight=Type.Bold color=Theme.Color.WarningText>
                "Responsive(Full, Full, Half)"
              </Text.String>
            </Box>
            <Box
              p={Padding(Space.Single)}
              w=Theme.Layout.Third
              h={Css.em(10.)}
              backgroundColor=Theme.Color.Error>
              <Text.String weight=Type.Bold color=Theme.Color.ErrorText>
                "Third"
              </Text.String>
            </Box>
            <Box
              p={Padding(Space.Single)}
              w=Theme.Layout.Third
              h={Css.em(10.)}
              backgroundColor=Theme.Color.Primary>
              <Text.String weight=Type.Bold color=Theme.Color.PrimaryText>
                "Third"
              </Text.String>
            </Box>
            <Box
              p={Padding(Space.Single)}
              w=Theme.Layout.Third
              h={Css.em(10.)}
              backgroundColor=Theme.Color.Success>
              <Text.String weight=Type.Bold color=Theme.Color.SuccessText>
                "Third"
              </Text.String>
            </Box>
          </>
        </Box>
      </Box>
    </Box>
  </Card>;
};