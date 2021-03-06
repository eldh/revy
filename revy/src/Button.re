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
    (
      ~variant,
      ~outline as outline_,
      ~margin as margin_=?,
      ~size,
      ~disabled as _disabled_,
      (),
    ) => {
  // TODO fix
  let (btnFontSize, paddingV, paddingH) =
    switch (size) {
    | Small => (Styles.getFontSize(-1), `half, `single)
    | Medium => (Styles.getFontSize(0), `single, `double)
    | Large => (Styles.getFontSize(1), `double, `triple)
    };
  let sharedStyles =
    Css.[
      padding2(~v=Styles.getSpace(paddingV), ~h=Styles.getSpace(paddingH)),
      textAlign(`center),
      alignContent(`center),
      position(`relative),
      flexGrow(0.),
      overflow(`visible),
      cursor(`pointer),
      transition(~duration=200, "all"),
      fontSize(btnFontSize),
      lineHeight(Styles.getLineHeight(~fontSize=btnFontSize, ())),
      fontWeight(`bold),
    ];
  let variantStyles = v => {
    open Css;
    let isLight = Styles.getIsLight();

    let bgVariant =
      switch (v) {
      | Warning => `warning
      | Error => `error
      | Success => `success
      | Primary => `primary
      | Secondary => `highlight((3, `body))
      };
    let styleStyles = [
      outline_
        ? boxShadow(
            ~y=px(0),
            ~inset=true,
            ~spread=px(2),
            ~blur=px(0),
            Styles.getTextColor(~tint=bgVariant, ~highlight=-30, ()),
          )
        : boxShadow(
            ~y=px(0),
            ~inset=true,
            ~spread=px(1),
            ~blur=px(0),
            Styles.getColor(~highlight=5, bgVariant),
          ),
      borderWidth(px(0)),
      borderStyle(`solid),
    ];
    let outlineHighlightBg = isLight ? rgba(0, 0, 0) : rgba(255, 255, 255);

    [
      fontFamily(Styles.getFontFamily(`body)),
      color(
        outline_
          ? Styles.getTextColor(~tint=bgVariant, ~highlight=-30, ())
          : Styles.getTextColor(~background=bgVariant, ~highlight=10, ()),
      ),
      borderRadius(Styles.getBorderRadius(`medium)),
      textTransform(`uppercase),
      backgroundColor(Styles.getColor(outline_ ? `transparent : bgVariant)),
      hover([
        backgroundColor(
          outline_
            ? outlineHighlightBg(0.05)
            : Styles.getColor(~highlight=isLight ? (8) : 10, bgVariant),
        ),
      ]),
      disabled([
        opacity(0.7),
        hover([backgroundColor(Styles.getColor(bgVariant))]),
      ]),
      focus([outlineStyle(`none)]),
      selector(":focus:not(:active)", Animations.focus),
      active([
        backgroundColor(
          outline_
            ? outlineHighlightBg(0.15)
            : Styles.getColor(~highlight=5, bgVariant),
        ),
      ]),
      ...styleStyles,
    ];
  };
  [Styles.getMargin(margin_), sharedStyles, variantStyles(variant)]
  |> List.concat;
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
      ~margin as m=`margin(`noSpace),
      ~children,
      (),
    ) => {
  <TouchableOpacity
    tag="button"
    onlyFocusOnTab
    style={useButtonStyles(
      ~variant,
      ~outline,
      ~margin=m,
      ~size,
      ~disabled,
      (),
    )}
    basis=`auto
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
        ~margin as m=`margin(`noSpace),
        ~onlyFocusOnTab=true,
        ~children,
        (),
      ) => {
    <a
      href
      className={
        useButtonStyles(~variant, ~outline, ~margin=m, ~size, ~disabled, ())
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
module Round = {
  [@react.component]
  let make =
      (
        ~onClick,
        ~variant=Secondary,
        ~size=Medium,
        ~disabled=false,
        ~outline=false,
        ~style=[],
        ~onlyFocusOnTab=true,
        ~margin=?,
        ~children,
        (),
      ) => {
    let w =
      switch (size) {
      | Small => `triple
      | Medium => `quad
      | Large => `number(6)
      };
    let btnStyle =
      useButtonStyles(~variant, ~outline, ~margin?, ~size, ~disabled, ());
    <TouchableOpacity
      tag="button"
      onlyFocusOnTab
      justify=`center
      align=`center
      alignContent=`center
      style={
        [
          btnStyle,
          Css.[
            width(Styles.getSpace(w)),
            height(Styles.getSpace(w)),
            padding(px(0)),
            borderRadius(pct(50.)),
          ],
          style,
        ]
        |> List.concat
      }
      basis=`auto
      onPress=onClick
      domProps={"disabled": disabled}>
      children
    </TouchableOpacity>;
  };
};