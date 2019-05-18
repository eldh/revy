open Revy.UI;
let getRgb = c =>
  switch (c) {
  | `rgb(_, _, _) as rgb => rgb
  | _ => `rgb((255, 0, 0))
  };
module Swatch = {
  [@react.component]
  let make = (~color, ()) => {
    let lum =
      Revy.Lab.luminanceRGB(Revy.Core.Styles.useColor(color) |> getRgb)
      *. 1000.
      |> int_of_float;
    <Box
      w={`escapeHatch(Css.px(80))}
      justify=`center
      // m={`marginBottom(`escapeHatch(Css.px()))}
      p={`paddingLeft(`escapeHatch(Css.em(0.5)))}
      backgroundColor=color>
      <Text.String
        size=(-1)
        lineHeight=2
        color={lum > 180 ? `escapeHatch(Css.black) : `escapeHatch(Css.white)}>
        {lum |> string_of_int}
      </Text.String>
    </Box>;
  };
};

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
            <Swatch color={`escapeHatch(c)} key={n |> string_of_int} />;
          })
       |> React.array}
    </Box>;
  };
};
module GradientBox = {
  [@react.component]
  let make = (~toColor, ~fromColor, ()) => {
    <Box m={`margin4((`noSpace, `noSpace, `double, `double))} grow=0.>
      <Text.String size=(-1) color=`quietText> "Lab" </Text.String>
      {[|0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10|]
       |> Array.map(n => {
            let c =
              Revy.Lab.mix(
                (n |> float_of_int) /. 10.,
                Revy.Core.Styles.useColor(fromColor) |> Revy.Lab.fromRGB,
                Revy.Core.Styles.useColor(toColor) |> Revy.Lab.fromRGB,
              )
              |> Revy.Lab.toRGB;
            <Swatch color={`escapeHatch(c)} key={n |> string_of_int} />;
          })
       |> React.array}
    </Box>;
  };
};

module RgbGradientBox = {
  [@react.component]
  let make = (~toColor, ~fromColor, ()) => {
    <Box m={`margin4((`noSpace, `noSpace, `double, `double))} grow=0.>
      <Text.String size=(-1) color=`quietText> "Rgb" </Text.String>
      {[|0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10|]
       |> Array.map(n => {
            let c =
              Revy.Lab.(
                mixRgb(
                  (n |> float_of_int) /. 10.,
                  Revy.Core.Styles.useColor(fromColor) |> getRgb,
                  Revy.Core.Styles.useColor(toColor) |> getRgb,
                )
              );
            <Swatch color={`escapeHatch(c)} key={n |> string_of_int} />;
          })
       |> React.array}
    </Box>;
  };
};

[@react.component]
let make = () => {
  Revy.Lab.(
    <ComponentsCard title="Colors">
      <Box direction=`row align=`flexEnd wrap=`wrap w=`full>
        <GradientBox fromColor=`primary toColor=`brand1 />
        <RgbGradientBox fromColor=`primary toColor=`brand1 />
        <GradientBox fromColor=`primary toColor=`error />
        <RgbGradientBox fromColor=`primary toColor=`error />
        <GradientBox fromColor=`success toColor=`warning />
        <RgbGradientBox fromColor=`success toColor=`warning />
        <GradientBox fromColor=`primary toColor=`warning />
        <RgbGradientBox fromColor=`primary toColor=`warning />
      </Box>
      <Box direction=`row align=`flexEnd wrap=`wrap w=`full>
        <GradientBox fromColor=`brand1 toColor=`primary />
        <RgbGradientBox fromColor=`brand1 toColor=`primary />
        <GradientBox fromColor=`brand2 toColor=`brand1 />
        <RgbGradientBox fromColor=`brand2 toColor=`brand1 />
        <GradientBox fromColor=`brand1 toColor=`success />
        <RgbGradientBox fromColor=`brand1 toColor=`success />
        <GradientBox fromColor=`brand2 toColor=`warning />
        <RgbGradientBox fromColor=`brand2 toColor=`warning />
      </Box>
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
    </ComponentsCard>
  );
};