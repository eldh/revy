[@bs.config {jsx: 3}];

let useCardStyle = (~p, ~m, ()) => {
  Css.[
    backgroundColor(
      Theme.Styles.useColor(~highlight=15, Theme.Color.BodyBackground),
    ),
    flexWrap(`wrap),
    borderRadius(Css.px(6)),
    borderWidth(px(1)),
    borderColor(
      Theme.Styles.useColor(~highlight=25, Theme.Color.BodyBackground),
    ),
    borderStyle(`solid),
    boxShadow(
      ~y=px(4),
      ~blur=px(10),
      hsla(0, 0, 0, Theme.Styles.useIsLight() ? 0.15 : 0.45),
    ),
    Theme.Styles.useMargin(m),
    Theme.Styles.usePadding(p),
  ];
};

[@react.component]
let make =
    (
      ~tag="div",
      ~a11yTitle as _a11yTitle=?,
      ~style as style_=[],
      ~color=Theme.Color.PrimaryText,
      ~grow=1.,
      ~p=(Theme.Space.Single),
      ~m=(Theme.Space.NoSpace),
      ~domProps=?,
      ~children=?,
      (),
    ) => {
  let style = [useCardStyle(~p, ~m, ()), style_]|>List.concat;

  <View tag style domProps> children </View>;
};