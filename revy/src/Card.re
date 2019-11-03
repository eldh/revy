open Core;

let useCardStyle = (~padding as p=?, ~margin as m=?, ()) => {
  // let alpha = Styles.getIsLight() ? 0.05 : 0.2;
  [
    Css.[
      backgroundColor(Styles.getColor(`bodyUp1)),
      flexWrap(`wrap),
      flexDirection(`column),
      alignItems(`stretch),
      borderRadius(Css.px(12)),
      // borderWidth(px(1)),
      // borderColor(Styles.getColor(`highlight((8, `body)))),
      // borderStyle(`solid),
      unsafe("willChange", "transition"),
    ],
    // boxShadows([
    //   `shadow("0 0px 4px " ++ string_of_rgba(0, 0, 0, alpha)),
    //   `shadow("0 5px 12px " ++ string_of_rgba(0, 0, 0, alpha)),
    //   `shadow("0 10px 16px " ++ string_of_rgba(0, 0, 0, alpha)),
    // ]),
    Styles.getPadding(p),
    Styles.getMargin(m),
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
      ~margin=?,
      ~domProps=?,
      ~children=?,
      (),
    ) => {
  let style = [useCardStyle(~padding, ~margin?, ()), style_] |> List.concat;

  <View tag style domProps> children </View>;
};