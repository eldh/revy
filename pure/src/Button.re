[@bs.config {jsx: 3}];

[@bs.send] external blur: Js.t({..}) => unit = "blur";
let highlightBoxShadow =
  Css.unsafe(
    "box-shadow",
    "0 1px 0 hsla(0,0%,100%, 0.2) inset, 0 -1px 0 hsla(0,0%,0%, 0.2) inset",
  );

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
  let theme = React.useContext(ThemeContext.context);
  // TODO fix
  let (btnFontSize, paddingV, paddingH) =
    Theme.(
      switch (size) {
      | Small => (theme.fontSize(-1), Space.Half, Space.Single)
      | Medium => (theme.fontSize(0), Space.Single, Space.Double)
      | Large => (theme.fontSize(1), Space.Double, Space.Triple)
      }
    );
  let sharedStyles =
    Css.[
      padding2(~v=theme.space(paddingV), ~h=theme.space(paddingH)),
      textDecoration(`none),
      cursor(`pointer),
      transition(~duration=200, "all"),
      fontSize(btnFontSize),
      lineHeight(theme.lineHeight(~fontSize=btnFontSize, ())),
      fontWeight(`bold),
    ];
  let variantStyles = v => {
    open Css;
    let (textVariant, bgVariant) =
      outline_
        ? switch (v) {
          | Warning => (Theme.Color.Warning, Theme.Color.BodyBackground)
          | Error => (Theme.Color.Error, Theme.Color.BodyBackground)
          | Success => (Theme.Color.Success, Theme.Color.BodyBackground)
          | Primary => (Theme.Color.Primary, Theme.Color.BodyBackground)
          | Secondary => (Theme.Color.Secondary, Theme.Color.BodyBackground)
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
          boxShadow(
            ~y=px(0),
            ~inset=true,
            ~spread=px(1),
            ~blur=px(0),
            outline_
              ? Css.transparent : theme.color(~highlight=10, bgVariant),
          ),
          borderColor(theme.color(~highlight=10, textVariant)),
          borderWidth(px(outline_ ? 2 : 0)),
          borderStyle(`solid),
        ]
      // | Raised => [borderWidth(px(0)), highlightBoxShadow]
      // | Layers => [
      //     boxShadow(~y=px(4), ~blur=px(5), hsla(0, 0, 0, 0.15)),
      //     borderWidth(px(0)),
      //   ]
      };

    [
      fontFamily(theme.fontFamily(Theme.Type.Body)),
      color(theme.color(textVariant)),
      borderRadius(theme.space(Theme.Space.Single)),
      textTransform(`uppercase),
      backgroundColor(theme.color(bgVariant)),
      hover([
        backgroundColor(
          theme.color(~highlight=outline_ ? 15 : (-20), bgVariant),
        ),
      ]),
      disabled([
        opacity(0.7),
        hover([backgroundColor(theme.color(bgVariant))])]),
      focus([
        outlineStyle(`none),
        backgroundColor(theme.color(~highlight=30, bgVariant)),
      ]),
      active([backgroundColor(theme.color(~highlight=20, bgVariant))]),
      ...styleStyles,
    ];
  };
  [Theme.Styles.margin(theme, m), sharedStyles, variantStyles(variant)]
  ->List.concat;
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
      ~m=Theme.margin(NoSpace),
      ~children,
      (),
    ) => {
  <TouchableOpacity
    tag="button"
    style={useButtonStyles(~variant, ~outline, ~m, ~size, ~disabled, ())}
    onPress={e => {
      if (onlyFocusOnTab) {
        let target = e->ReactEvent.Mouse.currentTarget;
        blur(target);
      };
      onClick();
    }}
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
        ~m=Theme.margin(NoSpace),
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
          let target = e->ReactEvent.Mouse.currentTarget;
          blur(target);
        };
        onClick();
      }}>
      children
    </a>;
  };
};