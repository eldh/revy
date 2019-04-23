[@bs.config {jsx: 3}];

let useBoxStyle =
    (
      ~align as align_,
      ~alignSelf as alignSelf_,
      ~alignContent as alignContent_,
      ~backgroundColor as backgroundColor_: Theme.Color.t,
      ~color as color_: Theme.Color.t,
      ~grow as grow_,
      ~wrap as wrap_,
      ~shrink as shrink_,
      ~justify as justify_,
      ~direction as direction_,
      ~p,
      ~m,
      ~h as height_,
      ~w as width_,
      ~overflow as overflow_,
      ~borderRadius as borderRadius_,
      (),
    ) => {
  let widthStyles = Theme.Styles.useWidth(width_);

  [
    Css.[
      alignSelf(alignSelf_),
      alignItems(align_),
      backgroundColor(Theme.Styles.useColor(backgroundColor_)),
      alignContent(alignContent_),
      color(Theme.Styles.useColor(color_)),
      height(height_),
      overflow(overflow_),
      borderRadius(borderRadius_),
      flexShrink(shrink_),
      flexDirection(direction_),
      flexGrow(grow_),
      flexWrap(wrap_),
      justifyContent(justify_),
    ],
    Theme.Styles.useMargin(m),
    Theme.Styles.usePadding(p),
    widthStyles,
  ]
  |> List.concat;
};

[@react.component]
let make =
    (
      ~tag="div",
      ~a11yTitle as _a11yTitle=?,
      ~style as style_=[],
      ~align=`flexStart,
      ~alignSelf=`auto,
      ~alignContent=`flexStart,
      ~backgroundColor=Theme.Color.Transparent,
      ~color=Theme.Color.PrimaryText,
      ~grow=1.,
      ~wrap=`wrap,
      ~shrink=0,
      ~justify=`flexStart,
      ~direction=`column,
      ~p=Theme.(Padding(Space.NoSpace)),
      ~m=Theme.(Margin(Space.NoSpace)),
      ~h=`auto,
      ~w=Theme.Layout.Auto,
      ~overflow=`auto,
      ~borderRadius=Css.px(0),
      ~domProps=?,
      ~children=?,
      (),
    ) => {
  let style =
    [
      useBoxStyle(
        ~align,
        ~alignSelf,
        ~alignContent,
        ~backgroundColor,
        ~color,
        ~grow,
        ~wrap,
        ~shrink,
        ~justify,
        ~direction,
        ~p,
        ~m,
        ~h,
        ~w,
        ~overflow,
        ~borderRadius,
        (),
      ),
      style_,
    ]
    |> List.concat;

  <View tag style domProps> children </View>;
};