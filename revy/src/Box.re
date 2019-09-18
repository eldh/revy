[@bs.config {jsx: 3}];

let useBoxStyle =
    (
      ~align as align_,
      ~alignSelf as alignSelf_,
      ~alignContent as alignContent_,
      ~backgroundColor as backgroundColor_,
      ~grow as grow_,
      ~basis as basis_,
      ~wrap as wrap_,
      ~shrink as shrink_,
      ~justify as justify_,
      ~direction as direction_,
      ~padding as padding_,
      ~margin as margin_,
      ~height as height_,
      ~width as width_,
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
      height(height_),
      overflow(overflow_),
      borderRadius(borderRadius_),
      flexShrink(shrink_),
      flexBasis(basis_),
      flexDirection(direction_),
      flexGrow(grow_),
      flexWrap(wrap_),
      justifyContent(justify_),
    ],
    Core.Styles.useMargin(margin_),
    Core.Styles.usePadding(padding_),
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
      ~shrink=1.,
      ~basis=`auto,
      ~justify=`flexStart,
      ~direction=`column,
      ~padding=`padding(`noSpace),
      ~margin=`margin(`noSpace),
      ~height=`auto,
      ~width=`auto,
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
        ~grow,
        ~basis,
        ~wrap,
        ~shrink,
        ~justify,
        ~direction,
        ~padding,
        ~margin,
        ~height,
        ~width,
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