[@react.component]
let make = (~title, ~subtitle, ()) => {
  <Box
    w=Revy.Core.Layout.Full
    h={Css.vh(80.)}
    justify=`center
    >
    <Text.String
      tag="div" size=8 weight=Revy.Core.Type.ExtraBold color=Revy.Core.Color.BodyText>
      title
    </Text.String>
    <Text.String
      tag="div" size=3 weight=Revy.Core.Type.Bold color=Revy.Core.Color.QuietText>
      subtitle
    </Text.String>
  </Box>;
};