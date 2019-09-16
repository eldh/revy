[@react.component]
let make = () => {
  <ComponentsCard title="Typography">
    <Box width=`full>
      <>
        <Text.Paragraph>
          "Revy UI comes with a few Text components for common use cases, like paragraphs, headings, code blocks etc. The `Text` module also exposes a `useTextStyles` hook for use in custom components. It ensures sizes, colors are correct. You normally don't even need to specify a text color - Revy automatically picks an accessible text color for the current background."
        </Text.Paragraph>
        <Text.Paragraph margin={`margin(`noSpace)} size=5 weight=`extraBold>
          "Extra bold and very big"
        </Text.Paragraph>
        <Text.Paragraph margin={`margin(`noSpace)} size=4 weight=`bold>
          "Bold and big"
        </Text.Paragraph>
        <Text.Paragraph quiet=true margin={`margin(`noSpace)} size=3 weight=`light>
          "Light and tall, like a basketball player"
        </Text.Paragraph>
        <Text.Paragraph margin={`margin(`noSpace)} size=2 weight=`extraLight>
          "Supermodel style"
        </Text.Paragraph>
        <Text.Paragraph margin={`margin(`noSpace)} size=1>
          "Perfectly average"
        </Text.Paragraph>
        <Text.Block backgroundColor=`highlight(10, `primary) padding=`padding2(`single, `half) margin={`margin(`noSpace)} weight=`bold>
          "Hey look I have a different background"
        </Text.Block>
        <Text.Paragraph margin={`margin(`noSpace)} size=0>
          "This is nothing at all"
        </Text.Paragraph>
        <Text.Paragraph margin={`margin(`noSpace)} size=(-1)>
          "A bit smaller"
        </Text.Paragraph>
        <Text.Paragraph quiet=true margin={`margin(`noSpace)} size=(-2)>
          "So tiny and quiet you almost don't notice it"
        </Text.Paragraph>
      </>
    </Box>
  </ComponentsCard>;
};