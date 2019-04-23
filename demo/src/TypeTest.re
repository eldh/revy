open Theme;

[@react.component]
let make = () => {
  <ComponentsCard title="Typography">
    <Box w=Layout.Full>
      <>
        <Box>
          <Text.String size=5 weight=Type.ExtraBold>
            "Extra bold and very big"
          </Text.String>
        </Box>
        <Box>
          <Text.String size=4 weight=Type.Bold>
            "Bold and big"
          </Text.String>
        </Box>
        <Box>
          <Text.String size=3 weight=Type.Light>
            "Light and tall, like a basketball player"
          </Text.String>
        </Box>
        <Box>
          <Text.String size=2 weight=Type.ExtraLight>
            "Supermodel style"
          </Text.String>
        </Box>
        <Box>
          <Text.String size=1>
            "Perfectly average"
          </Text.String>
        </Box>
        <Box>
          <Text.String size=0>
            "This is nothing at all"
          </Text.String>
        </Box>
        <Box>
          <Text.String size=(-1)>
            "A bit smaller"
          </Text.String>
        </Box>
        <Box>
          <Text.String size=(-2) color=Color.QuietText>
            "So tiny and quiet you almost don't notice it"
          </Text.String>
        </Box>
      </>
    </Box>
  </ComponentsCard>;
};