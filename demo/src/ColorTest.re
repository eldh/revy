open Revy.UI;

module ColorBox = {
  [@react.component]
  let make = (~color, ~title, ()) => {

    <Box m={`margin4((`noSpace, `noSpace, `double, `double))} grow=0.>
      <Text.String size=(-1) color=`quietText> title </Text.String>
      {[|0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10|]
       |> Array.map(n => {
            let c =
              Revy.Lab.lightnessRGB(
                n * 10 |> float_of_int,
                Revy.Core.Styles.useColor(color),
              );
            <Box
              h={Css.px(19)}
              w={`escapeHatch(Css.px(80))}
              key={n |> string_of_int}
              m={`marginBottom(`escapeHatch(Css.px(1)))}
              backgroundColor={`escapeHatch(c)}
            />;
          })
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
      <ColorBox color=`brand1 title="Brand1" />
      <ColorBox color=`brand2 title="Brand2" />
    </Box>
    <Box direction=`row align=`flexEnd wrap=`wrap w=`full>
      <ColorBox color=`success title="Success" />
      <ColorBox color=`error title="Error" />
      <ColorBox color=`warning title="Warning" />
    </Box>
  </ComponentsCard>;
};