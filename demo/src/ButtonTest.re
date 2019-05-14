open Revy.UI;

[@react.component]
let make = () => {
  <ComponentsCard title="Buttons">
    <Box direction=`row align=`flexEnd>
      <Button
        m={`margin(`half)}
        onClick={foo => Js.log2("Secondary", foo)}
        size=Button.Large
        variant=Button.Secondary>
        "Click me"->R.s
      </Button>
      <Button
        m={`margin(`half)}
        onClick={foo => Js.log2("Primary", foo)}
        variant=Button.Primary>
        "Click me"->R.s
      </Button>
      <Button
        m={`margin(`half)}
        onClick={foo => Js.log2("Error", foo)}
        variant=Button.Error>
        "Click me"->R.s
      </Button>
      <Button
        m={`margin(`half)}
        onClick={foo => Js.log2("Warning", foo)}
        variant=Button.Warning>
        "Click me"->R.s
      </Button>
      <Button
        m={`margin(`half)}
        onClick={foo => Js.log2("Success", foo)}
        size=Button.Small
        variant=Button.Success>
        "Click me"->R.s
      </Button>
    </Box>
    <Box direction=`row align=`flexStart>
      <Button
        m={`margin(`half)}
        onClick={foo => Js.log2("Secondary outline", foo)}
        outline=true
        size=Button.Large
        variant=Button.Secondary>
        "Click me"->R.s
      </Button>
      <Button
        m={`margin(`half)}
        onClick={foo => Js.log2("Primary outline", foo)}
        outline=true
        variant=Button.Primary>
        "Click me"->R.s
      </Button>
      <Button
        m={`margin(`half)}
        onClick={foo => Js.log2("Error outline", foo)}
        outline=true
        variant=Button.Error>
        "Click me"->R.s
      </Button>
      <Button
        m={`margin(`half)}
        onClick={foo => Js.log2("Warning outline", foo)}
        outline=true
        variant=Button.Warning>
        "Click me"->R.s
      </Button>
      <Button
        m={`margin(`half)}
        onClick={foo => Js.log2("Success outline", foo)}
        outline=true
        size=Button.Small
        variant=Button.Success>
        "Click me"->R.s
      </Button>
    </Box>
  </ComponentsCard>;
};