open Revy;
open Revy.Core;

[@react.component]
let make = (~toggleTheme=ignore, ()) => {
  <Box
    tag="main"
    backgroundColor=Revy.Core.Color.BodyBackground
    p={Revy.Core.Padding(Space.Double)}
    w=Layout.Full
    align=`stretch
    m={Revy.Core.Margin(Space.Auto)}>
    <>
      <Hero
        title="Revy"
        subtitle="A higher order design system for ReasonReact."
      />
      <Box m={MarginBottom(Space.Quint)} w=Layout.Full>
        <Heading> {"Revy.Core" |> React.string} </Heading>
        <Text.Paragraph>
          "Consistency, colors, typography, motion... A lot of things are hard to manage in a design system. Revy aims to make these things easier."
        </Text.Paragraph>
        <Text.Paragraph>
          {j|You create a theme by providing some input to `Revy.Core.make()`. Then you access everything included in the theme – colors, fonts, space variables etc. – via a set of variants and functions supplied by Revy. Revy.Core provides functions for color manipulation, layout, spacing, typography and more and makes it easy to build consistent, accessible and beautiful user interfaces.|j}
        </Text.Paragraph>
        <Text.Paragraph>
          "It's easy to create multiple themes, if you want to provide different branding styles (or a dark mode like this page). You can even use different themes at the same time, which could be useful for sidebars or other pop-in content."
        </Text.Paragraph>
        <Heading level=Heading.H3> {"Example" |> React.string} </Heading>
        <Text.Paragraph>
          "This is just a trivial example of how to create a theme and add it to your app. More examples are coming soon..."
        </Text.Paragraph>
        <Text.Code>
          {|let theme = Revy.Core.make();

[@react.component]
let make = () => {
  <Revy.Core.Context.Provider value=theme>
    <Text.String
      color=Revy.Core.Colors.QuietText
      size=2
    >
        "My first app"
    </Text.String>
  </Revy.Core.Context.Provider>
};|}
        </Text.Code>
      </Box>
      <Heading> {"Revy.UI" |> React.string} </Heading>
      <Box m={MarginBottom(Space.Quint)}>
        <Text.Paragraph>
          "Revy makes it easy to build your own components, but it also comes with a set of components of its own. You can use them as a starting point for your design system, an inspiration or a cautionary example."
        </Text.Paragraph>
      </Box>
      <TextInputTest />
      <ButtonTest />
      <TypeTest />
      <LayoutTest />
    </>
  </Box>;
};