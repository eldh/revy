[@bs.config {jsx: 3}];
open Theme;
// open Theme.Layout;
open Theme.Color;

[@react.component __MODULE__]
let make = () =>
  <Box
    tag="main"
    backgroundColor=BodyBackground
    p={padding(Space.Double)}
    w=Theme.Layout.Full
    m=Auto>
    <>
      <TextInputTest />
      <Button
        m={Theme.margin(Half)}
        size=Button.Small
        variant=Button.Secondary
        onClick={foo => Js.log2("foo1", foo)}>
        "Click me"->R.s
      </Button>
      <Button
        m={Theme.margin(Half)}
        variant=Button.Primary
        onClick={foo => Js.log2("foo2", foo)}>
        "Click me"->R.s
      </Button>
      <Button
        variant=Button.Error
        m={Theme.margin(Half)}
        onClick={foo => Js.log2("foo3", foo)}>
        "Click me"->R.s
      </Button>
      <Button
        variant=Button.Warning
        m={Theme.margin(Half)}
        onClick={foo => Js.log2("foo3", foo)}>
        "Click me"->R.s
      </Button>
      <Button
        size=Button.Large
        variant=Button.Success
        m={Theme.margin(Half)}
        onClick={foo => Js.log2("foo3", foo)}>
        "Click me"->R.s
      </Button>
      <Button
        m={Theme.margin(Half)}
        size=Button.Small
        variant=Button.SecondaryInverted
        onClick={foo => Js.log2("foo1", foo)}>
        "Click me"->R.s
      </Button>
      <Button
        m={Theme.margin(Half)}
        variant=Button.PrimaryInverted
        onClick={foo => Js.log2("foo2", foo)}>
        "Click me"->R.s
      </Button>
      <Button
        variant=Button.WarningInverted
        m={Theme.margin(Half)}
        onClick={foo => Js.log2("foo3", foo)}>
        "Click me"->R.s
      </Button>
      <Button
        variant=Button.ErrorInverted
        m={Theme.margin(Half)}
        onClick={foo => Js.log2("foo3", foo)}>
        "Click me"->R.s
      </Button>
      <Button
        size=Button.Large
        variant=Button.SuccessInverted
        m={Theme.margin(Half)}
        onClick={foo => Js.log2("foo3", foo)}>
        "Click me"->R.s
      </Button>
      <Box w=Theme.Layout.Full>
        <>
          <Box>
            <Text size=5 weight=Type.ExtraBold> "Text good good 3" </Text>
          </Box>
          <Box> <Text size=4 weight=Type.Bold> "Text good 3" </Text> </Box>
          <Box> <Text size=3 weight=Type.Light> "Text good 3" </Text> </Box>
          <Box>
            <Text size=2 weight=Type.ExtraLight> "Text good 2" </Text>
          </Box>
          <Box> <Text size=1> "Text good 1" </Text> </Box>
          <Box> <Text size=(-1)> "More good text -1" </Text> </Box>
          <Box> <Text size=(-2)> "More good text -2" </Text> </Box>
        </>
      </Box>
      // <Box direction=`row p={padding(Space.Single)}>
      //   <>
      //     <Box h={Css.em(10.)} backgroundColor=Primary />
      //     <Box
      //       w=Half
      //       h={Css.em(10.)}
      //       backgroundColor={EscapeHatch(Css.hsl(40, 80, 50))}
      //     />
      //     <Box
      //       w={Responsive(Full, Half, Quarter)}
      //       h={Css.em(10.)}
      //       backgroundColor=Warning
      //     />
      //     <Box w=Third h={Css.em(10.)} backgroundColor=Error />
      //     <Box w=Third h={Css.em(10.)} backgroundColor=Warning />
      //     <Box w=Third h={Css.em(10.)} backgroundColor=Success />
      //   </>
      // </Box>
    </>
  </Box>;