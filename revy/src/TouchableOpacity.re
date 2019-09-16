[@bs.send] external blur: Js.t({..}) => unit = "blur";

/**
 This is the first line. _Italicized_ word.

 * This is a bullet point.
 * This is the second point. */

/**
 This is the first line. _Italicized_ word.

 * This is a bullet point.
 * This is the second point. */
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
      ~onlyFocusOnTab=true,
      ~padding=`padding(`noSpace),
      ~margin=`margin(`noSpace),
      ~height=`auto,
      ~width=`auto,
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
        ~grow,
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
    </View>
  </Core.BackgroundColorContext.Provider>;
};