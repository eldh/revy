open Revy.UI;
open Revy.Core;

module ColorBox = {
  [@react.component]
  let make = (~color, ~title, ()) => {

    <Box m=Space.(Margin4(NoSpace, NoSpace, Double, Double)) grow=0.>
      <Text.String size=(-1) color=Color.QuietText> title </Text.String>
      {[|(-5), (-4), (-3), (-2), (-1), 0, 1, 2, 3, 4, 5|]
       |> Array.map(n =>
            <Box
              h={Css.px(19)}
              w={Layout.EscapeHatch(Css.px(80))}
              key={n |> string_of_int}
              m=Space.(MarginBottom(EscapeHatch(Css.px(1))))
              backgroundColor={Color.Highlight(n * 8, color)}
            />
          )
       |> React.array}
    </Box>;
  };
};

[@react.component]
let make = () => {
  <ComponentsCard title="Colors">
    <Box direction=`row align=`flexEnd wrap=`wrap w=Layout.Full>
      <ColorBox color=Color.Primary title="Primary" />
      <ColorBox color=Color.Secondary title="Secondary" />
      <ColorBox color=Color.Success title="Success" />
      <ColorBox color=Color.Error title="Error" />
      <ColorBox color=Color.Warning title="Warning" />
    </Box>
    <Box direction=`row align=`flexEnd wrap=`wrap w=Layout.Full>
      <ColorBox color=Color.Brand1 title="Brand1" />
      <ColorBox color=Color.Brand2 title="Brand2" />
      <ColorBox color=Color.Brand3 title="Brand3" />
      <ColorBox color=Color.Brand4 title="Brand4" />
    </Box>
  </ComponentsCard>;
};