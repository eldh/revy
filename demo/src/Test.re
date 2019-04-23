open Theme;

[@react.component]
let make = (~toggleTheme=ignore, ()) => {
  <Box
    tag="main"
    backgroundColor=Theme.Color.BodyBackground
    p={Theme.Padding(Space.Double)}
    w=Layout.Full
    align=`stretch
    m={Theme.Margin(Space.Auto)}
    >
    <>
      // <Button
      //   m={Theme.Margin(Space.Half)}
      //   onClick={_ => toggleTheme()}
      //   size=Button.Small
      //   variant=Button.Secondary>
      //   "Toggle theme" |> R.s
      // </Button>
      <Hero
        title="Pure"
        subtitle="A higher order design system for ReasonReact."
      />
      <Box m={MarginBottom(Space.Quint)} w=Layout.Full>
        <Heading> {"Pure.Core" |> React.string} </Heading>
        <Text.Paragraph>
          "Consistency, colors, typography, motion... A lot of things are hard to manage in a design system. Pure aims to make these things easier."
        </Text.Paragraph>
        <Text.Paragraph>
          "You create a theme by providing some input to `Theme.make()`. Then you access them via a set of pre-defined variants and functions supplied by Pure. Pure.Core provides functions for color manipulation, layout, spacing, typography and more."
        </Text.Paragraph>
        <Text.Paragraph>
          "It's easy to create multiple themes, if you want to provide different branding styles (or a dark mode like this page). You can even use different themes at the same time, which could be useful for sidebars or other pop-in content."
        </Text.Paragraph>
        <Heading level=Heading.H3> {"Example" |> React.string} </Heading>
        <Text.Paragraph>
          "This is just a trivial example of how to create a theme and add it to your app. More examples are coming soon..."
        </Text.Paragraph>
        <Text.Code>
          {|let theme = Theme.make();

[@react.component]
let make = () => {
  <Theme.Context.Provider value=theme>
    <Text.String
      color=Theme.Colors.QuietText
      size=2
    >
        "My first app"
    </Text.String>
  </Theme.Context.Provider>
};|}
        </Text.Code>
      </Box>
      <Heading> {"Pure.UI" |> React.string} </Heading>
      <Box m={MarginBottom(Space.Quint)}>
        <Text.Paragraph>
          "Pure makes it easy to build your own components, but it also comes with a set of components of its own. You can use them as a starting point for your design system, an inspiration or a cautionary example."
        </Text.Paragraph>
      </Box>
      <TextInputTest />
      <ButtonTest />
      <TypeTest />
      <LayoutTest />
    </>
  </Box>;
};