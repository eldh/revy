open Theme;
open Theme.Color;

[@react.component]
let make = () => {
  let (count, setCount) = React.useState(() => 0);
  <Box
    tag="main"
    backgroundColor=BodyBackground
    p={padding(Space.Double)}
    w=Theme.Layout.Full
    m=Auto>
    <>
      <Text> count->R.i </Text>
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
        onClick={foo => {
          Js.log2("foo2", foo);
          setCount(c => c + 1);
        }}>
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
        variant=Button.Secondary
        outline=true
        onClick={foo => Js.log2("foo1", foo)}>
        "Click me"->R.s
      </Button>
      <Button
        m={Theme.margin(Half)}
        variant=Button.Primary
        outline=true
        onClick={foo => Js.log2("foo2", foo)}>
        "Click me"->R.s
      </Button>
      <Button
        variant=Button.Warning
        outline=true
        m={Theme.margin(Half)}
        onClick={foo => Js.log2("foo3", foo)}>
        "Click me"->R.s
      </Button>
      <Button
        variant=Button.Error
        outline=true
        m={Theme.margin(Half)}
        onClick={foo => Js.log2("foo3", foo)}>
        "Click me"->R.s
      </Button>
      <Button
        size=Button.Large
        variant=Button.Success
        outline=true
        m={Theme.margin(Half)}
        onClick={foo => Js.log2("foo3", foo)}>
        "Click me"->R.s
      </Button>
      <Box w=Theme.Layout.Full>
        <>
          <Box>
            <Text.String size=5 weight=Type.ExtraBold> "Text good good 3" </Text.String>
          </Box>
          <Box> <Text.String size=4 weight=Type.Bold> "Text good 3" </Text.String> </Box>
          <Box> <Text.String size=3 weight=Type.Light> "Text good 3" </Text.String> </Box>
          <Box>
            <Text.String size=2 weight=Type.ExtraLight> "Text good 2" </Text.String>
          </Box>
          <Box> <Text.String size=1> "Text good 1" </Text.String> </Box>
          <Box> <Text.String size=(-1)> "More good text -1" </Text.String> </Box>
          <Box> <Text.String size=(-2)> "More good text -2" </Text.String> </Box>
        </>
      </Box>
      <Box w=Theme.Layout.Full direction=`row p={padding(Space.Single)}>
        <>
          <Box w=Theme.Layout.Full h={Css.em(10.)} backgroundColor=Primary />
          <Box
            w=Theme.Layout.Half
            h={Css.em(10.)}
            backgroundColor={EscapeHatch(Css.hsl(40, 80, 50))}
          />
          <Box
            w={Theme.Layout.Responsive(Full, Half, Quarter)}
            h={Css.em(10.)}
            backgroundColor=Warning
          />
          <Box w=Theme.Layout.Third h={Css.em(10.)} backgroundColor=Error />
          <Box w=Theme.Layout.Third h={Css.em(10.)} backgroundColor=Warning />
          <Box w=Theme.Layout.Third h={Css.em(10.)} backgroundColor=Success />
        </>
      </Box>
    </>
  </Box>;
};