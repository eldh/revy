[@bs.config {jsx: 3}];

let useBoxStyle =
    (
      ~align as alignProp,
      ~alignSelf as alignSelfProp,
      ~alignContent as alignContentProp,
      ~backgroundColor as backgroundColorProp,
      ~color as colorProp,
      ~grow as growProp,
      ~wrap as wrapProp,
      ~shrink as shrinkProp,
      ~justify as justifyProp,
      ~direction as directionProp,
      ~p,
      ~m,
      ~h as heightProp,
      ~w as widthProp,
      ~overflow as overflowProp,
      ~borderRadius as borderRadiusProp,
      (),
    ) => {
  let theme = React.useContext(ThemeContext.context);
  let marginStyles = Theme.Styles.margin(theme, m);
  let paddingStyles = Theme.Styles.padding(theme, p);
  let widthStyles = Theme.Styles.width(theme, widthProp);

  [
    Css.[
      alignSelf(alignSelfProp),
      alignItems(alignProp),
      alignContent(alignContentProp),
      backgroundColor(theme.color(backgroundColorProp)),
      color(theme.color(colorProp)),
      height(heightProp),
      overflow(overflowProp),
      borderRadius(borderRadiusProp),
      flexShrink(shrinkProp),
      flexDirection(directionProp),
      flexGrow(growProp),
      flexWrap(wrapProp),
      justifyContent(justifyProp),
    ],
    marginStyles,
    paddingStyles,
    widthStyles,
  ]
  ->List.concat;
};

[@react.component __MODULE__]
let make =
    (
      ~tag="div",
      ~a11yTitle as _a11yTitle=?,
      ~style as styleProp=[],
      ~align=`flexStart,
      ~alignSelf=`flexStart,
      ~alignContent=`flexStart,
      ~backgroundColor=Theme.Color.Transparent,
      ~color=Theme.Color.PrimaryText,
      ~grow=1.,
      ~wrap=`wrap,
      ~shrink=0,
      ~justify=`flexStart,
      ~direction=`column,
      ~p=Theme.padding(NoSpace),
      ~m=Theme.margin(NoSpace),
      ~h=`auto,
      ~w=Theme.Layout.Auto,
      ~overflow=`auto,
      ~borderRadius=Css.px(0),
      ~domProps=Js.Obj.empty(),
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
      styleProp,
    ]
    ->List.concat;

  <View tag style domProps> children </View>;
};