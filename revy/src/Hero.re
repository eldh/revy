[@react.component]
let make = (~title, ~subtitle, ()) => {
  <Box
    w=`full
    h={Css.vh(80.)}
    justify=`center
    >
    <Text.String
      tag="div" size=8 weight=`extraBold color=`bodyText>
      title
    </Text.String>
    <Text.String
      tag="div" size=3 weight=`bold color=`quietText>
      subtitle
    </Text.String>
  </Box>;
};