open Theme;

[@react.component]
let make = (~toggleTheme=ignore, ()) => {
  <Box
    tag="main"
    backgroundColor=Theme.Color.BodyBackground
    p=Space.Double
    w=Theme.Layout.Full
    align=`stretch
    m=Space.Auto>
    <>
      <Button
        m=Theme.Space.Half
        onClick={_ => toggleTheme()}
        size=Button.Small
        variant=Button.Secondary>
        "Toggle theme"->R.s
      </Button>
      <TextInputTest />
      <ComponentsCard title="Buttons">
        <Button
          m=Theme.Space.Half
          onClick={foo => Js.log2("Secondary", foo)}
          size=Button.Small
          variant=Button.Secondary>
          "Click me"->R.s
        </Button>
        <Button
          m=Theme.Space.Half
          onClick={foo => Js.log2("Primary", foo)}
          variant=Button.Primary>
          "Click me"->R.s
        </Button>
        <Button
          m=Theme.Space.Half
          onClick={foo => Js.log2("Error", foo)}
          variant=Button.Error>
          "Click me"->R.s
        </Button>
        <Button
          m=Theme.Space.Half
          onClick={foo => Js.log2("Warning", foo)}
          variant=Button.Warning>
          "Click me"->R.s
        </Button>
        <Button
          m=Theme.Space.Half
          onClick={foo => Js.log2("Success", foo)}
          size=Button.Large
          variant=Button.Success>
          "Click me"->R.s
        </Button>
        <Button
          m=Theme.Space.Half
          onClick={foo => Js.log2("Secondary outline", foo)}
          outline=true
          size=Button.Small
          variant=Button.Secondary>
          "Click me"->R.s
        </Button>
        <Button
          m=Theme.Space.Half
          onClick={foo => Js.log2("Primary outline", foo)}
          outline=true
          variant=Button.Primary>
          "Click me"->R.s
        </Button>
        <Button
          m=Theme.Space.Half
          onClick={foo => Js.log2("Error outline", foo)}
          outline=true
          variant=Button.Error>
          "Click me"->R.s
        </Button>
        <Button
          m=Theme.Space.Half
          onClick={foo => Js.log2("Warning outline", foo)}
          outline=true
          variant=Button.Warning>
          "Click me"->R.s
        </Button>
        <Button
          m=Theme.Space.Half
          onClick={foo => Js.log2("Success outline", foo)}
          outline=true
          size=Button.Large
          variant=Button.Success>
          "Click me"->R.s
        </Button>
      </ComponentsCard>
      <ComponentsCard title="Typography">
        <Box w=Theme.Layout.Full>
          <>
            <Box>
              <Text.String size=5 weight=Type.ExtraBold>
                "The quick fox jumped over the lazy dog 5"
              </Text.String>
            </Box>
            <Box>
              <Text.String size=4 weight=Type.Bold>
                "The quick fox jumped over the lazy dog 4"
              </Text.String>
            </Box>
            <Box>
              <Text.String size=3 weight=Type.Light>
                "The quick fox jumped over the lazy dog 3"
              </Text.String>
            </Box>
            <Box>
              <Text.String size=2 weight=Type.ExtraLight>
                "The quick fox jumped over the lazy dog 2"
              </Text.String>
            </Box>
            <Box>
              <Text.String size=1>
                "The quick fox jumped over the lazy dog 1"
              </Text.String>
            </Box>
            <Box>
              <Text.String size=(-1)>
                "The quick fox jumped over the lazy dog -1"
              </Text.String>
            </Box>
            <Box>
              <Text.String size=(-2)>
                "The quick fox jumped over the lazy dog -2"
              </Text.String>
            </Box>
          </>
        </Box>
      </ComponentsCard>
      <Card m=Theme.Space.Single p=Theme.Space.Double>
        <Box wrap=`wrap w=Theme.Layout.Full>
          <Text.String> "Layout" </Text.String>
          <Box  style=Css.[maxWidth(pct(100.)), width(pct(100.))] direction=`row>
            <Box w=Theme.Layout.Full direction=`row p=Space.Single>
              <>
                <Box
                  w=Theme.Layout.Full
                  h={Css.em(10.)}
                  backgroundColor=Theme.Color.Primary
                />
                <Box
                  w=Theme.Layout.Half
                  h={Css.em(10.)}
                  backgroundColor={
                    Theme.Color.EscapeHatch(Css.hsl(40, 80, 50))
                  }
                />
                <Box
                  w={Theme.Layout.Responsive(Full, Full, Half)}
                  h={Css.em(10.)}
                  backgroundColor=Theme.Color.Warning
                />
                <Box
                  w=Theme.Layout.Third
                  h={Css.em(10.)}
                  backgroundColor=Theme.Color.Error
                />
                <Box
                  w=Theme.Layout.Third
                  h={Css.em(10.)}
                  backgroundColor=Theme.Color.Warning
                />
                <Box
                  w=Theme.Layout.Third
                  h={Css.em(10.)}
                  backgroundColor=Theme.Color.Success
                />
              </>
            </Box>
          </Box>
        </Box>
      </Card>
    </>
  </Box>;
};