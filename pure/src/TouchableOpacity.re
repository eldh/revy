[@bs.config {jsx: 3}];

[@react.component]
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
      ~onPress=?,
      ~domProps=Js.Obj.empty(),
      ~children=?,
      (),
    ) => {
  
  let style =
    [
      Box.useBoxStyle(
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
  <View tag style domProps onPress> children </View>;
};