[@react.component]
let make = (~title, ~children, ()) => {
  <Card m=Revy.Core.(MarginBottom(Space.Quad)) p=Revy.Core.(Padding(Space.Triple))>
    <Box wrap=`wrap w=Revy.Core.Layout.Full>
      <Text.String weight=Revy.Core.Type.Bold> title </Text.String>
      <Box style=Css.[maxWidth(pct(100.))] direction=`row> children </Box>
    </Box>
  </Card>;
};