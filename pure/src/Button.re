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
    Theme.(
      switch (size) {
      | Small => (Theme.Styles.useFontSize(-1), Space.Half, Space.Single)
      | Medium => (Theme.Styles.useFontSize(0), Space.Single, Space.Double)
      | Large => (Theme.Styles.useFontSize(1), Space.Double, Space.Triple)
      }
    );
  let sharedStyles =
    Css.[
      padding2(
        ~v=Theme.Styles.useSpace(paddingV),
        ~h=Theme.Styles.useSpace(paddingH),
      ),
      textDecoration(`none),
      textAlign(`center),
      alignContent(`center),
      flexGrow(0.),
      cursor(`pointer),
      transition(~duration=200, "all"),
      fontSize(btnFontSize),
      lineHeight(Theme.Styles.useLineHeight(~fontSize=btnFontSize, ())),
      fontWeight(`bold),
    ];
  let variantStyles = v => {
    open Css;
    let (textVariant, bgVariant) =
      outline_
        ? switch (v) {
          | Warning => (Theme.Color.Warning, Theme.Color.Transparent)
          | Error => (Theme.Color.Error, Theme.Color.Transparent)
          | Success => (Theme.Color.Success, Theme.Color.Transparent)
          | Primary => (Theme.Color.Primary, Theme.Color.Transparent)
          | Secondary => (Theme.Color.Secondary, Theme.Color.Transparent)
          }
        : (
          switch (v) {
          | Warning => (Theme.Color.WarningText, Theme.Color.Warning)
          | Error => (Theme.Color.ErrorText, Theme.Color.Error)
          | Success => (Theme.Color.SuccessText, Theme.Color.Success)
          | Primary => (Theme.Color.PrimaryText, Theme.Color.Primary)
          | Secondary => (Theme.Color.SecondaryText, Theme.Color.Secondary)
          }
        );
    let styleStyles =
      switch (Theme.Flat) {
      | _ => [
          outline_
            ? boxShadow(
                ~y=px(0),
                ~inset=true,
                ~spread=px(2),
                ~blur=px(0),
                Theme.Styles.useColor(~highlight=50, textVariant),
              )
            : boxShadow(
                ~y=px(0),
                ~inset=true,
                ~spread=px(1),
                ~blur=px(0),
                Theme.Styles.useColor(~highlight=15, bgVariant),
              ),
          // boxShadow(
          //   ~y=px(0),
          //   ~inset=true,
          //   ~spread=px(1),
          //   ~blur=px(0),
          //   outline_
          //     ? Css.transparent : Theme.Styles.useColor(~highlight=10, bgVariant),
          // ),
          // borderColor(Theme.Styles.useColor(~highlight=10, textVariant)),
          borderWidth(px(0)),
          borderStyle(`solid),
        ]
      };
    let outlineHighlightBg =
      Theme.Styles.useIsLight() ? rgba(0, 0, 0) : rgba(255, 255, 255);

    [
      fontFamily(Theme.Styles.useFontFamily(Theme.Type.Body)),
      color(
        Theme.Styles.useColor(~highlight=outline_ ? 50 : 0, textVariant),
      ),
      borderRadius(Css.px(6)),
      textTransform(`uppercase),
      backgroundColor(Theme.Styles.useColor(bgVariant)),
      hover([
        backgroundColor(
          outline_
            ? outlineHighlightBg(0.05)
            : Theme.Styles.useColor(~highlight=-20, bgVariant),
        ),
      ]),
      disabled([
        opacity(0.7),
        hover([backgroundColor(Theme.Styles.useColor(bgVariant))]),
      ]),
      focus([
        outlineStyle(`none),
        backgroundColor(
          outline_
            ? outlineHighlightBg(0.1)
            : Theme.Styles.useColor(~highlight=30, bgVariant),
        ),
      ]),
      active([
        backgroundColor(Theme.Styles.useColor(~highlight=20, bgVariant)),
      ]),
      ...styleStyles,
    ];
  };
  [Theme.Styles.useMargin(m), sharedStyles, variantStyles(variant)]
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
      ~m=Theme.(Margin(Space.NoSpace)),
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
        ~m=Theme.(Margin(Space.NoSpace)),
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