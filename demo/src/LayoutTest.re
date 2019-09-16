[@react.component]
let make = (~toggleTheme=ignore, ()) => {
  <Box margin={`marginBottom(`number(10))}>
    <Box wrap=`wrap width=`full>
      <Heading level=`h4> "Layout" </Heading>
      <Box
        style=Css.[maxWidth(pct(100.)), width(pct(100.))] direction=`row>
        <Box width=`full direction=`row>
          <>
            <Box
              padding={`padding(`single)}
              width=`full
              height={`em(10.)}
              backgroundColor=`primary>
              <Text.String weight=`bold> "`full" </Text.String>
            </Box>
            <Box
              padding={`padding(`single)}
              width=`half
              height={`em(10.)}
              backgroundColor=`success>
              <Text.String weight=`bold> "`half" </Text.String>
            </Box>
            <Box
              padding={`padding(`single)}
              width={`responsive((`full, `full, `half))}
              height={`em(10.)}
              backgroundColor=`warning>
              <Text.String weight=`bold>
                "`responsive(`full, `full, `half)"
              </Text.String>
            </Box>
            <Box
              padding={`padding(`single)}
              width=`third
              height={`em(10.)}
              backgroundColor=`error>
              <Text.String weight=`bold> "`third" </Text.String>
            </Box>
            <Box
              padding={`padding(`single)}
              width=`third
              height={`em(10.)}
              backgroundColor=`brand1>
              <Text.String weight=`bold> "`third" </Text.String>
            </Box>
            <Box
              padding={`padding(`single)}
              width=`third
              height={`em(10.)}
              backgroundColor=`brand2>
              <Text.String weight=`bold> "`third" </Text.String>
            </Box>
          </>
        </Box>
      </Box>
    </Box>
  </Box>;
};