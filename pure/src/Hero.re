[@react.component]
let make = (~title, ~subtitle, ()) => {
  <Box
    w=Theme.Layout.Full
    h={Css.vh(80.)}
    justify=`center
    >
    <Text.String
      tag="div" size=8 weight=Theme.Type.ExtraBold color=Theme.Color.BodyText>
      title
    </Text.String>
    <Text.String
      tag="div" size=3 weight=Theme.Type.Bold color=Theme.Color.QuietText>
      subtitle
    </Text.String>
  </Box>;
};