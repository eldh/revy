[@bs.config {jsx: 3}];

let useBoxStyle =
    (
      ~align as align_,
      ~alignSelf as alignSelf_,
      ~alignContent as alignContent_,
      ~backgroundColor as backgroundColor_,
      ~tintColor as tint,
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
  let widthStyles = Core.Styles.useWidth(width_);

  [
    Css.[
      alignSelf(alignSelf_),
      alignItems(align_),
      backgroundColor(Core.Styles.useColor(backgroundColor_)),
      alignContent(alignContent_),
      color(Core.Styles.useTextColor(~tint, ())),
      height(height_),
      overflow(overflow_),
      borderRadius(borderRadius_),
      flexShrink(shrink_),
      flexDirection(direction_),
      flexGrow(grow_),
      flexWrap(wrap_),
      justifyContent(justify_),
    ],
    Core.Styles.useMargin(m),
    Core.Styles.usePadding(p),
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
      ~backgroundColor=`transparent,
      ~grow=1.,
      ~wrap=`wrap,
      ~shrink=0.,
      ~justify=`flexStart,
      ~direction=`column,
      ~p=`padding(`noSpace),
      ~m=`margin(`noSpace),
      ~h=`auto,
      ~w=`auto,
      ~overflow=`auto,
      ~borderRadius=Css.px(0),
      ~tintColor=?,
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
        ~tintColor,
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

  <Core.BackgroundColorContext.Provider value=backgroundColor>
    <View tag style domProps> children </View>
  </Core.BackgroundColorContext.Provider>;
};