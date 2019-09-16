open Core;

let useCardStyle = (~padding as p, ~margin as m, ()) => {
  [
    Css.[
      backgroundColor(Styles.useColor(`highlight((5, `body)))),
      flexWrap(`wrap),
      borderRadius(Css.px(6)),
      borderWidth(px(1)),
      borderColor(Styles.useColor(`highlight((10, `body)))),
      borderStyle(`solid),
      boxShadow(
        ~y=px(4),
        ~blur=px(10),
        rgba(0, 0, 0, Styles.useIsLight() ? 0.15 : 0.45),
      ),
    ],
    Styles.usePadding(p),
    Styles.useMargin(m),
  ]
  |> List.concat;
};

[@react.component]
let make =
    (
      ~tag="div",
      ~a11yTitle as _a11yTitle=?,
      ~style as style_=[],
      ~grow=1.,
      ~padding=`padding(`single),
      ~margin=`margin(`noSpace),
      ~domProps=?,
      ~children=?,
      (),
    ) => {
  let style = [useCardStyle(~padding, ~margin, ()), style_] |> List.concat;

  <View tag style domProps> children </View>;
};