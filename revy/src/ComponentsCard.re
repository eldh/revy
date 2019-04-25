open Revy.Core;
// module SpacerLine = {
// [@react.component]
// let make = () => {
//   <View style=Css.[
//     Css.borderBottom(px(1), `solid, useColor(~highlight=50, Color.BodyBackground))
//     ] />;
// };

[@react.component]
let make = (~title, ~children, ()) => {
  <Box m=MarginBottom(Space.Number(10))>
    <Box wrap=`wrap w=Layout.Full>
      <Heading level=Heading.H4 > (title |> React.string) </Heading>
      // <SpacerLine />
      <Box style=Css.[maxWidth(pct(100.))] direction=`row> children </Box>
    </Box>
  </Box>;
};