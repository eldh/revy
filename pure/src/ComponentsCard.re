[@react.component]
let make = (~title, ~children, ()) => {
  <Card m=Theme.(MarginBottom(Space.Quad)) p=Theme.(Padding(Space.Triple))>
    <Box wrap=`wrap w=Theme.Layout.Full>
      <Text.String weight=Theme.Type.Bold> title </Text.String>
      <Box style=Css.[maxWidth(pct(100.))] direction=`row> children </Box>
    </Box>
  </Card>;
};