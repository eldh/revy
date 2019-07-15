
[@react.component]
let make = () => {
  <ComponentsCard title="Typography">
    <Box w=`full>
      <>
        <Box>
          <Text.String size=5 weight=`extraBold>
            "Extra bold and very big"
          </Text.String>
        </Box>
        <Box>
          <Text.String size=4 weight=`bold>
            "Bold and big"
          </Text.String>
        </Box>
        <Box>
          <Text.String size=3 weight=`light>
            "Light and tall, like a basketball player"
          </Text.String>
        </Box>
        <Box>
          <Text.String size=2 weight=`extraLight>
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
          <Text.String size=(-2) >
            "So tiny and quiet you almost don't notice it"
          </Text.String>
        </Box>
      </>
    </Box>
  </ComponentsCard>;
};