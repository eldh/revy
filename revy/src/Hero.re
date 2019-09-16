[@react.component]
let make = (~title, ~subtitle, ()) => {
  <Box
    width=`full
    height={Css.vh(80.)}
    justify=`center
    >
    <Text.String
      tag="div" size=8 weight=`extraBold tintColor=`body>
      title
    </Text.String>
    <Text.String
      tag="div" size=3 weight=`bold>
      subtitle
    </Text.String>
  </Box>;
};