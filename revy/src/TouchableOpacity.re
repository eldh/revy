[@bs.send] external blur: Js.t({..}) => unit = "blur";

/**
 This is the first line. _Italicized_ word.

 * This is a bullet point.
 * This is the second point. */
[@react.component]
/**
 This is the first line. _Italicized_ word.

 * This is a bullet point.
 * This is the second point. */
let make =
    (
      ~tag="div",
      ~a11yTitle as _a11yTitle=?,
      ~style as style_=[],
      ~align=`flexStart,
      ~alignSelf=`auto,
      ~alignContent=`flexStart,
      ~backgroundColor=Core.Color.Transparent,
      ~color=Core.Color.PrimaryText,
      ~grow=1.,
      ~wrap=`wrap,
      ~shrink=0,
      ~justify=`flexStart,
      ~direction=`column,
      ~onlyFocusOnTab=true,
      ~p=Core.(Padding(Space.NoSpace)),
      ~m=Core.(Margin(Space.NoSpace)),
      ~h=`auto,
      ~w=Core.Layout.Auto,
      ~overflow=`auto,
      ~borderRadius=Css.px(0),
      ~onPress=?,
      ~domProps=?,
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
      style_,
    ]
    |> List.concat;
  <View
    tag
    style
    domProps
    onPress={
      switch (onPress) {
      | Some(fn) =>
        Some(
          e => {
            if (onlyFocusOnTab) {
              let target = e->ReactEvent.Mouse.currentTarget;
              blur(target);
            };
            fn(e);
          },
        )
      | None => None
      }
    }>
    children
  </View>;
};