open Revy.UI;
open Revy.Core;

module ColorBox = {
  [@react.component]
  let make = (~color, ()) => {
    <Box m=Space.(Margin4(NoSpace, NoSpace, Double, Double))>
      {[|(-6), (-5), (-4), (-3), (-2), (-1), 0, 1, 2, 3, 4, 5, 6|]
       |> Array.map(n =>
            <Box
              h={Css.px(19)}
              w={Layout.EscapeHatch(Css.px(100))}
              key={n |> string_of_int}
              m=Space.(MarginBottom(EscapeHatch(Css.px(1))))
              backgroundColor={Color.Highlight(n * 20, color)}
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
      <ColorBox color=Color.Primary />
      <ColorBox color=Color.Secondary />
      <ColorBox color=Color.Success />
      <ColorBox color=Color.Error />
      <ColorBox color=Color.Warning />
    </Box>
  </ComponentsCard>;
};