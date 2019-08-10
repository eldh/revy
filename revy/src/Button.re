open Core;

type variant =
  | Error
  | Warning
  | Success
  | Primary
  | Secondary;

type size =
  | Small
  | Medium
  | Large;

let useButtonStyles =
    (~variant, ~outline as outline_, ~m, ~size, ~disabled as _disabled_, ()) => {
  // TODO fix
  let (btnFontSize, paddingV, paddingH) =
    switch (size) {
    | Small => (Styles.useFontSize(-1), `half, `single)
    | Medium => (Styles.useFontSize(0), `single, `double)
    | Large => (Styles.useFontSize(1), `double, `triple)
    };
  let sharedStyles =
    Css.[
      padding2(~v=Styles.useSpace(paddingV), ~h=Styles.useSpace(paddingH)),
      textDecoration(`none),
      textAlign(`center),
      alignContent(`center),
      flexGrow(0.),
      cursor(`pointer),
      transition(~duration=200, "all"),
      fontSize(btnFontSize),
      lineHeight(Styles.useLineHeight(~fontSize=btnFontSize, ())),
      fontWeight(`bold),
    ];
  let variantStyles = v => {
    open Css;
    let isLight = Styles.useIsLight();

    let bgVariant =
      switch (v) {
      | Warning => `warning
      | Error => `error
      | Success => `success
      | Primary => `primary
      | Secondary => `highlight(50, `neutral)
      };
    let styleStyles = [
      outline_
        ? boxShadow(
            ~y=px(0),
            ~inset=true,
            ~spread=px(2),
            ~blur=px(0),
            Styles.useTextColor(~tint=bgVariant, ~highlight=-30, ()),
          )
        : boxShadow(
            ~y=px(0),
            ~inset=true,
            ~spread=px(1),
            ~blur=px(0),
            Styles.useColor(~highlight=5, bgVariant),
          ),
      borderWidth(px(0)),
      borderStyle(`solid),
    ];
    let outlineHighlightBg = isLight ? rgba(0, 0, 0) : rgba(255, 255, 255);

    [
      fontFamily(Styles.useFontFamily(`body)),
      color(
        outline_
          ? Styles.useTextColor(~tint=bgVariant, ~highlight=-30, ())
          : Styles.useTextColor(~background=bgVariant, ~highlight=10, ()),
      ),
      borderRadius(Styles.useBorderRadius(`medium)),
      textTransform(`uppercase),
      backgroundColor(Styles.useColor(outline_ ? `transparent : bgVariant)),
      hover([
        backgroundColor(
          outline_
            ? outlineHighlightBg(0.05)
            : Styles.useColor(~highlight=isLight ? (-8) : 10, bgVariant),
        ),
      ]),
      disabled([
        opacity(0.7),
        hover([backgroundColor(Styles.useColor(bgVariant))]),
      ]),
      focus([
        outlineStyle(`none),
        backgroundColor(
          outline_
            ? outlineHighlightBg(0.1)
            : Styles.useColor(~highlight=10, bgVariant),
        ),
      ]),
      active([
        backgroundColor(
          outline_
            ? outlineHighlightBg(0.15)
            : Styles.useColor(~highlight=15, bgVariant),
        ),
      ]),
      ...styleStyles,
    ];
  };
  [Styles.useMargin(m), sharedStyles, variantStyles(variant)] |> List.concat;
};

[@react.component]
let make =
    (
      ~onClick,
      ~variant=Secondary,
      ~size=Medium,
      ~disabled=false,
      ~outline=false,
      ~onlyFocusOnTab=true,
      ~m=`margin(`noSpace),
      ~children,
      (),
    ) => {
  <TouchableOpacity
    tag="button"
    onlyFocusOnTab
    style={useButtonStyles(~variant, ~outline, ~m, ~size, ~disabled, ())}
    onPress=onClick
    domProps={"disabled": disabled}>
    children
  </TouchableOpacity>;
};
module Link = {
  [@react.component]
  let make =
      (
        ~onClick,
        ~variant=Primary,
        ~href,
        ~disabled=false,
        ~outline=false,
        ~size=Medium,
        ~m=`margin(`noSpace),
        ~onlyFocusOnTab=true,
        ~children,
        (),
      ) => {
    <a
      href
      className={
        useButtonStyles(~variant, ~outline, ~m, ~size, ~disabled, ())
        ->Css.style
      }
      onClick={e => {
        if (onlyFocusOnTab) {
          let target = e |> ReactEvent.Mouse.currentTarget;
          target |> TouchableOpacity.blur;
        };
        onClick(e);
      }}>
      children
    </a>;
  };
};