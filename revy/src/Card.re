[@bs.config {jsx: 3}];

let useCardStyle = (~p, ~m, ()) => {
  [
    Css.[
      backgroundColor(
        Core.(Styles.useColor(`highlight(5, `body))),
      ),
      flexWrap(`wrap),
      borderRadius(Css.px(6)),
      borderWidth(px(1)),
      borderColor(
        Core.(Styles.useColor(`highlight(10, `body))),
      ),
      borderStyle(`solid),
      boxShadow(
        ~y=px(4),
        ~blur=px(10),
        rgba(0, 0, 0, Core.Styles.useIsLight() ? 0.15 : 0.45),
      ),
    ],
    Core.Styles.usePadding(p),
    Core.Styles.useMargin(m),
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
      ~p=`padding(`single),
      ~m=`margin(`noSpace),
      ~domProps=?,
      ~children=?,
      (),
    ) => {
  let style = [useCardStyle(~p, ~m, ()), style_] |> List.concat;

  <View tag style domProps> children </View>;
};