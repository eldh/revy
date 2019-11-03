open UI;
module Swatch = {
  [@react.component]
  let make = (~color: Lab.t, ()) => {
    let lum = Lab.luminance(color) |> int_of_float;
    <Box
      width={`unsafeCustomValue(Css.px(80))}
      justify=`center
      // margin={`marginBottom(`unsafeCustomValue(Css.px()))}
      padding={`paddingLeft(`unsafeCustomValue(Css.em(0.5)))}
      backgroundColor={`unsafeCustomColor(color)}>
      <Text.String size=(-1) lineHeight=2>
        {lum |> string_of_int}
      </Text.String>
    </Box>;
  };
};

module ColorBox = {
  [@react.component]
  let make = (~color, ~title, ()) => {
    <Box margin={`margin4((`noSpace, `noSpace, `double, `double))} grow=0.>
      <Text.String size=(-1)> title </Text.String>
      {[|0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10|]
       |> Array.map(n => {
            let c =
              Lab.lightness(
                n * 10 |> float_of_int,
                color |> Core.Styles.getLabColor,
              );
            <Swatch color=c key={n |> string_of_int} />;
          })
       |> React.array}
    </Box>;
  };
};
module MixColorBox = {
  let white = `lab((100., 0., 0., 1.));
  let black = `lab((0., 0., 0., 1.));
  [@react.component]
  let make = (~color, ~title) => {
    let middleC = color |> Core.Styles.getLabColor |> Lab.lightness(50.);
    <Box margin={`margin4((`noSpace, `noSpace, `double, `double))} grow=0.>
      <Text.String size=(-1)> title </Text.String>
      {[|0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10|]
       |> Array.map(n => {
            let c =
              n > 5 ?  Lab.mix(
                (n - 6 |> float_of_int) /. 8.,
                middleC,
                white,
              ) : Lab.mix(
                (n |> float_of_int) /. 7.,
                black,
                middleC,
              );

            <Swatch color=c key={n |> string_of_int} />;
          })
       |> React.array}
    </Box>;
  };
};

[@react.component]
let make = () => {
  Lab.(
    <ComponentsCard title="Colors">
      <Box direction=`row align=`flexEnd wrap=`wrap width=`full>
        <ColorBox color=`primary title="Primary" />
        <ColorBox color=`secondary title="Secondary" />
        <ColorBox color=`brand1 title="Brand1" />
        <ColorBox color=`brand2 title="Brand2" />
        <ColorBox color=`success title="Success" />
        <ColorBox color=`error title="Error" />
        <ColorBox color=`warning title="Warning" />
      </Box>
      <Box direction=`row align=`flexEnd wrap=`wrap width=`full>
        <MixColorBox color=`primary title="Primary" />
        <MixColorBox color=`secondary title="Secondary" />
        <MixColorBox color=`brand1 title="Brand1" />
        <MixColorBox color=`brand2 title="Brand2" />
        <MixColorBox color=`success title="Success" />
        <MixColorBox color=`error title="Error" />
        <MixColorBox color=`warning title="Warning" />
      </Box>
    </ComponentsCard>
  );
};