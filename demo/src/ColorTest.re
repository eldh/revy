open Revy.UI;

module ColorBox = {
  [@react.component]
  let make = (~color, ~title, ()) => {

    <Box m=(`margin4(`noSpace, `noSpace, `double, `double)) grow=0.>
      <Text.String size=(-1) color=`quietText> title </Text.String>
      {[|(-5), (-4), (-3), (-2), (-1), 0, 1, 2, 3, 4, 5|]
       |> Array.map(n =>
            <Box
              h={Css.px(19)}
              w={`escapeHatch(Css.px(80))}
              key={n |> string_of_int}
              m=(`marginBottom(`escapeHatch(Css.px(1))))
              backgroundColor={`highlight(n * 8, color)}
            />
          )
       |> React.array}
    </Box>;
  };
};

[@react.component]
let make = () => {
  <ComponentsCard title="Colors">
    <Box direction=`row align=`flexEnd wrap=`wrap w=`full>
      <ColorBox color=`primary title="Primary" />
      <ColorBox color=`secondary title="Secondary" />
      <ColorBox color=`success title="Success" />
      <ColorBox color=`error title="Error" />
      <ColorBox color=`warning title="Warning" />
    </Box>
    <Box direction=`row align=`flexEnd wrap=`wrap w=`full>
      <ColorBox color=`brand1 title="Brand1" />
      <ColorBox color=`brand2 title="Brand2" />
      <ColorBox color=`brand3 title="Brand3" />
      <ColorBox color=`brand4 title="Brand4" />
    </Box>
  </ComponentsCard>;
};