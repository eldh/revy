[@react.component]
let make = (~toggleTheme=ignore, ()) => {
  <Box m={`marginBottom(`number(10))}>
    <Box wrap=`wrap w=`full>
      <Heading level=`h4> "Layout" </Heading>
      <Box
        style=Css.[maxWidth(pct(100.)), width(pct(100.))] direction=`row>
        <Box w=`full direction=`row>
          <>
            <Box
              p={`padding(`single)}
              w=`full
              h={`em(10.)}
              backgroundColor=`primary>
              <Text.String weight=`bold> "`full" </Text.String>
            </Box>
            <Box
              p={`padding(`single)}
              w=`half
              h={`em(10.)}
              backgroundColor=`success>
              <Text.String weight=`bold> "`half" </Text.String>
            </Box>
            <Box
              p={`padding(`single)}
              w={`responsive((`full, `full, `half))}
              h={`em(10.)}
              backgroundColor=`warning>
              <Text.String weight=`bold>
                "`responsive(`full, `full, `half)"
              </Text.String>
            </Box>
            <Box
              p={`padding(`single)}
              w=`third
              h={`em(10.)}
              backgroundColor=`error>
              <Text.String weight=`bold> "`third" </Text.String>
            </Box>
            <Box
              p={`padding(`single)}
              w=`third
              h={`em(10.)}
              backgroundColor=`brand1>
              <Text.String weight=`bold> "`third" </Text.String>
            </Box>
            <Box
              p={`padding(`single)}
              w=`third
              h={`em(10.)}
              backgroundColor=`brand2>
              <Text.String weight=`bold> "`third" </Text.String>
            </Box>
          </>
        </Box>
      </Box>
    </Box>
  </Box>;
};