[@react.component]
let make = (~title, ~children, ()) => {
  <Card m=Theme.Space.Single p=Theme.Space.Double>
    <Box wrap=`wrap w=Theme.Layout.Full>
      <Text.String> title </Text.String>
      <Box style=Css.[maxWidth(pct(100.))] direction=`row> children </Box>
    </Box>
  </Card>;
};