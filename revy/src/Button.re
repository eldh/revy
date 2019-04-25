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
    Revy.Core.(
      switch (size) {
      | Small => (Revy.Core.Styles.useFontSize(-1), Space.Half, Space.Single)
      | Medium => (Revy.Core.Styles.useFontSize(0), Space.Single, Space.Double)
      | Large => (Revy.Core.Styles.useFontSize(1), Space.Double, Space.Triple)
      }
    );
  let sharedStyles =
    Css.[
      padding2(
        ~v=Revy.Core.Styles.useSpace(paddingV),
        ~h=Revy.Core.Styles.useSpace(paddingH),
      ),
      textDecoration(`none),
      textAlign(`center),
      alignContent(`center),
      flexGrow(0.),
      cursor(`pointer),
      transition(~duration=200, "all"),
      fontSize(btnFontSize),
      lineHeight(Revy.Core.Styles.useLineHeight(~fontSize=btnFontSize, ())),
      fontWeight(`bold),
    ];
  let variantStyles = v => {
    open Css;
    let (textVariant, bgVariant) =
      outline_
        ? switch (v) {
          | Warning => (Revy.Core.Color.Warning, Revy.Core.Color.Transparent)
          | Error => (Revy.Core.Color.Error, Revy.Core.Color.Transparent)
          | Success => (Revy.Core.Color.Success, Revy.Core.Color.Transparent)
          | Primary => (Revy.Core.Color.Primary, Revy.Core.Color.Transparent)
          | Secondary => (Revy.Core.Color.Secondary, Revy.Core.Color.Transparent)
          }
        : (
          switch (v) {
          | Warning => (Revy.Core.Color.WarningText, Revy.Core.Color.Warning)
          | Error => (Revy.Core.Color.ErrorText, Revy.Core.Color.Error)
          | Success => (Revy.Core.Color.SuccessText, Revy.Core.Color.Success)
          | Primary => (Revy.Core.Color.PrimaryText, Revy.Core.Color.Primary)
          | Secondary => (Revy.Core.Color.SecondaryText, Revy.Core.Color.Secondary)
          }
        );
    let styleStyles =
      switch (Revy.Core.Flat) {
      | _ => [
          outline_
            ? boxShadow(
                ~y=px(0),
                ~inset=true,
                ~spread=px(2),
                ~blur=px(0),
                Revy.Core.Styles.useColor(~highlight=50, textVariant),
              )
            : boxShadow(
                ~y=px(0),
                ~inset=true,
                ~spread=px(1),
                ~blur=px(0),
                Revy.Core.Styles.useColor(~highlight=15, bgVariant),
              ),
          // boxShadow(
          //   ~y=px(0),
          //   ~inset=true,
          //   ~spread=px(1),
          //   ~blur=px(0),
          //   outline_
          //     ? Css.transparent : Revy.Core.Styles.useColor(~highlight=10, bgVariant),
          // ),
          // borderColor(Revy.Core.Styles.useColor(~highlight=10, textVariant)),
          borderWidth(px(0)),
          borderStyle(`solid),
        ]
      };
    let outlineHighlightBg =
      Revy.Core.Styles.useIsLight() ? rgba(0, 0, 0) : rgba(255, 255, 255);

    [
      fontFamily(Revy.Core.Styles.useFontFamily(Revy.Core.Type.Body)),
      color(
        Revy.Core.Styles.useColor(~highlight=outline_ ? 50 : 0, textVariant),
      ),
      borderRadius(Css.px(6)),
      textTransform(`uppercase),
      backgroundColor(Revy.Core.Styles.useColor(bgVariant)),
      hover([
        backgroundColor(
          outline_
            ? outlineHighlightBg(0.05)
            : Revy.Core.Styles.useColor(~highlight=-20, bgVariant),
        ),
      ]),
      disabled([
        opacity(0.7),
        hover([backgroundColor(Revy.Core.Styles.useColor(bgVariant))]),
      ]),
      focus([
        outlineStyle(`none),
        backgroundColor(
          outline_
            ? outlineHighlightBg(0.1)
            : Revy.Core.Styles.useColor(~highlight=30, bgVariant),
        ),
      ]),
      active([
        backgroundColor(Revy.Core.Styles.useColor(~highlight=20, bgVariant)),
      ]),
      ...styleStyles,
    ];
  };
  [Revy.Core.Styles.useMargin(m), sharedStyles, variantStyles(variant)]
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
      ~m=Revy.Core.(Margin(Space.NoSpace)),
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
        ~m=Revy.Core.(Margin(Space.NoSpace)),
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