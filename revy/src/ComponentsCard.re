[@react.component]
let make = (~title, ~children, ()) => {
  <Box m=`marginBottom(`number(10))>
    <Box wrap=`wrap w=`full>
      <Heading level=`h4 > (title |> React.string) </Heading>
      <Box style=Css.[maxWidth(pct(100.))] direction=`row> children </Box>
    </Box>
  </Box>;
};