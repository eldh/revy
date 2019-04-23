// type cssFontFamily = array(string);
exception InvalidValue(string);

type cssFontSize = [
  | `calc([ | `add | `sub], Css.length, Css.length)
  | `ch(float)
  | `cm(float)
  | `em(float)
  | `ex(float)
  | `inherit_
  | `initial
  | `mm(float)
  | `percent(float)
  | `pt(int)
  | `px(int)
  | `pxFloat(float)
  | `rem(float)
  | `unset
  | `vh(float)
  | `vmax(float)
  | `vmin(float)
  | `vw(float)
  | `zero
];

type cssLineHeight = [
  | `abs(float)
  | `calc([ | `add | `sub], Css.length, Css.length)
  | `ch(float)
  | `cm(float)
  | `em(float)
  | `ex(float)
  | `inherit_
  | `initial
  | `mm(float)
  | `normal
  | `percent(float)
  | `pt(int)
  | `px(int)
  | `pxFloat(float)
  | `rem(float)
  | `unset
  | `vh(float)
  | `vmax(float)
  | `vmin(float)
  | `vw(float)
  | `zero
];

type cssWidth = [
  | `auto
  | `calc([ | `add | `sub], Css.length, Css.length)
  | `ch(float)
  | `cm(float)
  | `em(float)
  | `ex(float)
  | `mm(float)
  | `percent(float)
  | `pt(int)
  | `px(int)
  | `pxFloat(float)
  | `rem(float)
  | `vh(float)
  | `vmax(float)
  | `vmin(float)
  | `vw(float)
  | `zero
];
type cssFontWeight = [
  | `black
  | `bold
  | `bolder
  | `extraBold
  | `extraLight
  | `inherit_
  | `initial
  | `light
  | `lighter
  | `medium
  | `normal
  | `num(int)
  | `semiBold
  | `thin
  | `unset
];

type uiStyle =
  | Layers
  | Flat
  | Raised;

type length =
  | Zero
  | Unit(int)
  | BorderWidth
  | BorderRadius;

module Layout = {
  type t =
    | Percent(float)
    | Eighth
    | Sixth
    | Quarter
    | Third
    | Half
    | Full
    | Css(cssWidth)
    | Auto
    | Responsive(t, t, t);
};

module Space = {
  type t =
    | Auto
    | NoSpace
    | Half
    | Single
    | Double
    | Triple
    | Quad
    | Quint
    | Number(int)
    | Responsive(t, t, t);
};

module Type = {
  type font =
    | Body
    | Title
    | Mono
    | Alt;

  type fontWeight =
    | ExtraLight
    | Light
    | Normal
    | Bold
    | ExtraBold;
};

module Color = {
  type t =
    | Primary
    | Secondary
    | Success
    | Warning
    | Error
    | BodyBackground
    | PrimaryText
    | SecondaryText
    | WarningText
    | ErrorText
    | SuccessText
    | BodyText
    | QuietText
    | Transparent
    | EscapeHatch(Css.color);
};

type margin =
  | Auto
  | Margin(Space.t)
  | MarginTop(Space.t)
  | MarginBottom(Space.t)
  | MarginLeft(Space.t)
  | MarginRight(Space.t)
  | Margin2(Space.t, Space.t)
  | Margin4(Space.t, Space.t, Space.t, Space.t)
  | ResponsiveMargin(margin, margin, margin);

type padding =
  | Padding(Space.t)
  | PaddingTop(Space.t)
  | PaddingBottom(Space.t)
  | PaddingLeft(Space.t)
  | PaddingRight(Space.t)
  | Padding2(Space.t, Space.t)
  | Padding4(Space.t, Space.t, Space.t, Space.t)
  | ResponsivePadding(padding, padding, padding);

/**
  Base type for themes
 */

type fonts = {
  body: list(string),
  title: list(string),
  mono: list(string),
  alt: list(string),
};

type colors = {
  primary: Css.color,
  primaryText: Css.color,
  secondary: Css.color,
  secondaryText: Css.color,
  success: Css.color,
  successText: Css.color,
  warning: Css.color,
  warningText: Css.color,
  error: Css.color,
  errorText: Css.color,
  bodyBackground: Css.color,
  bodyText: Css.color,
  quietText: Css.color,
};

type t = {
  colors,
  fonts,
  fontScale: float,
  baseFontSize: int,
  baseGridUnit: int,
  width: int,
};

let responsive = (_theme, (s, m, l)) => {
  Css.[media("(min-width: 30em)", m), media("(min-width: 50em)", l), ...s];
};
module Private = {
  let isLight = theme => ThemeUtil.Color.isLight(theme.colors.bodyBackground);

  let color = (~theme, ~alpha=1., ~highlight=0, v) => {
    open Color;
    let highlightFn =
      (theme |> isLight ? ThemeUtil.Color.darken : ThemeUtil.Color.lighten)(
        highlight,
      );
    (
      switch (v) {
      | Primary => theme.colors.primary
      | Secondary => theme.colors.secondary
      | Success => theme.colors.success
      | Warning => theme.colors.warning
      | Error => theme.colors.error
      | BodyBackground => theme.colors.bodyBackground
      | PrimaryText => theme.colors.primaryText
      | SecondaryText => theme.colors.secondaryText
      | WarningText => theme.colors.warningText
      | ErrorText => theme.colors.errorText
      | SuccessText => theme.colors.successText
      | BodyText => theme.colors.bodyText
      | QuietText => theme.colors.quietText
      | Transparent => `transparent
      | EscapeHatch(c) => c
      }
    )
    |> highlightFn
    |> (
      switch (alpha) {
      | 1. => (a => a)
      | a => ThemeUtil.Color.alpha(a)
      }
    );
  };

  let fontFamily = (~theme, v) =>
    Type.(
      switch (v) {
      | Title => theme.fonts.title
      | Mono => theme.fonts.mono
      | Body => theme.fonts.body
      | Alt => theme.fonts.alt
      }
    )
    |> String.concat(", ");

  let fontSize = (~theme, n) => {
    (theme.fontScale ** n->float_of_int *. theme.baseFontSize->float_of_int)
    ->int_of_float
    ->Css.px;
  };

  let fontWeight = (~theme as _, v) => {
    Type.(
      switch (v) {
      | ExtraLight => `extraLight
      | Light => `light
      | Bold => `bold
      | Normal => `normal
      | ExtraBold => `extraBold
      }
    );
  };

  let space = (~theme, ~borderAdjust=0, v) => {
    open Css;
    let length = v => px(theme.baseGridUnit * v - borderAdjust);
    switch (v) {
    | Space.Auto => Obj.magic(Css.auto)
    | NoSpace => Css.px(0)
    | Half => 1 |> length
    | Single => 2 |> length
    | Double => 3 |> length
    | Triple => 6 |> length
    | Quad => 8 |> length
    | Quint => 10 |> length
    | Number(i) => i |> length
    | Responsive(_, _, _) => 6 |> length // TODO Fix
    };
  };

  let rec findMinStep = (test, i) => {
    test(i) ? i : findMinStep(test, i + 1);
  };

  let getPx = v =>
    switch (v) {
    | `px(i) => i
    | _ => raise(InvalidValue("Not a pixel value"))
    };

  let lineHeight = (~theme, ~fontSize=Css.px(0), ~extraHeight=0, _) => {
    let length = v => Css.px(theme.baseGridUnit * v);
    let va =
      findMinStep(
        i =>
          (i * theme.baseGridUnit)->float_of_int
          > fontSize->getPx->float_of_int
          *. 1.25,
        0,
      );
    va + extraHeight |> length;
  };
};
let make =
    (
      ~fontScale=1.25,
      ~baseFontSize=16,
      ~baseGridUnit=4,
      ~fonts={
               body: ["-apple-system", "BlinkMacSystemFont", "sans-serif"],
               title: ["-apple-system", "BlinkMacSystemFont", "sans-serif"],
               mono: ["monospace"],
               alt: ["-apple-system", "BlinkMacSystemFont", "sans-serif"],
             },
      ~colors=Css.{
                primary:
                  Lab.(fromRGB((36, 133, 222)) |> lighten(25) |> toCssRGB),
                primaryText: rgb(0, 0, 0),
                secondary:
                  Lab.(fromRGB((20, 10, 0)) |> lighten(25) |> toCssRGB),
                secondaryText: rgb(255, 255, 255),
                warning:
                  Lab.(fromRGB((214, 149, 5)) |> lighten(25) |> toCssRGB),
                warningText: rgb(0, 0, 0),
                success:
                  Lab.(fromRGB((44, 173, 2)) |> lighten(25) |> toCssRGB),
                successText: rgb(0, 0, 0),
                error:
                  Lab.(fromRGB((211, 26, 26)) |> lighten(25) |> toCssRGB),
                errorText: rgb(0, 0, 0),
                bodyBackground: rgb(255, 255, 255),
                bodyText: rgb(40, 40, 40),
                quietText: rgb(130, 130, 130),
              },
      ~gridWidth as width=960,
      (),
    ) => {
  {colors, fonts, fontScale, baseFontSize, baseGridUnit, width};
};

module DefaultTheme = {
  let theme = make();
};

module Context = {
  let context = React.createContext(make());
  let provider = React.Context.provider(context);

  module Provider = {
    [@react.component]
    let make = (~value, ~children) => {
      EscapeHatch.use(
        Obj.magic(provider),
        {"value": value, "children": children},
      );
    };
  };
};
module Styles = {
  let marginSpace = (theme, v) => Obj.magic(Private.space(~theme, v));
  let rec marginStyles_ = (theme, p) => {
    let marginSpace = v => Obj.magic(Private.space(~theme, v));
    switch (p) {
    | Auto => [Css.margin(`auto)]
    | Margin(i) => [Css.margin(marginSpace(i))]
    | MarginTop(i) => [Css.marginTop(marginSpace(i))]
    | MarginBottom(i) => [Css.marginBottom(marginSpace(i))]
    | MarginLeft(i) => [Css.marginLeft(marginSpace(i))]
    | MarginRight(i) => [Css.marginRight(marginSpace(i))]
    | Margin2(x, y) => [Css.margin2(~v=marginSpace(y), ~h=marginSpace(x))]
    | Margin4(l, t, r, b) => [
        Css.margin4(
          ~top=marginSpace(t),
          ~bottom=marginSpace(b),
          ~right=marginSpace(r),
          ~left=marginSpace(l),
        ),
      ]
    | ResponsiveMargin(s, m, l) =>
      responsive(
        theme,
        (
          marginStyles_(theme, s),
          marginStyles_(theme, m),
          marginStyles_(theme, l),
        ),
      )
    };
  };
  let rec paddingStyles_ = (theme, p) => {
    switch (p) {
    | Padding(i) => [Css.padding(Private.space(~theme, i))]
    | PaddingTop(i) => [Css.paddingTop(Private.space(~theme, i))]
    | PaddingBottom(i) => [Css.paddingBottom(Private.space(~theme, i))]
    | PaddingLeft(i) => [Css.paddingLeft(Private.space(~theme, i))]
    | PaddingRight(i) => [Css.paddingRight(Private.space(~theme, i))]
    | Padding2(x, y) => [
        Css.padding2(
          ~v=Private.space(~theme, y),
          ~h=Private.space(~theme, x),
        ),
      ]
    | Padding4(l, t, r, b) => [
        Css.padding4(
          ~top=Private.space(~theme, t),
          ~bottom=Private.space(~theme, b),
          ~right=Private.space(~theme, r),
          ~left=Private.space(~theme, l),
        ),
      ]
    | ResponsivePadding(s, m, l) =>
      responsive(
        theme,
        (
          paddingStyles_(theme, s),
          paddingStyles_(theme, m),
          paddingStyles_(theme, l),
        ),
      )
    };
  };

  let rec widthStyles_ = (theme, m) => {
    let w = theme.width;
    switch (m) {
    | Layout.Percent(v) => Css.[width(pct(v))]
    | Eighth => Css.[width(pct(100. /. 8.))]
    | Sixth => Css.[width(pct(100. /. 6.))]
    | Quarter => Css.[width(pct(100. /. 4.))]
    | Third => Css.[width(pct(100. /. 3.))]
    | Half => Css.[width(pct(100. /. 2.))]
    | Full => Css.[maxWidth(px(w)), width(pct(100.))]
    | Auto => Css.[width(`auto)]
    | Css(i) => Css.[width(i)]
    | Responsive(s, m, l) =>
      responsive(
        theme,
        (
          widthStyles_(theme, s),
          widthStyles_(theme, m),
          widthStyles_(theme, l),
        ),
      )
    };
  };

  let useMargin = m => {
    let theme = React.useContext(Context.context);
    marginStyles_(theme, m);
  };

  let usePadding = p => {
    let theme = React.useContext(Context.context);
    paddingStyles_(theme, p);
  };

  /** Width styles yo */
  let useWidth = w => widthStyles_(React.useContext(Context.context), w);

  let useColor = (~highlight=0, ~alpha=1., c) => {
    Private.color(
      ~theme=React.useContext(Context.context),
      ~highlight,
      ~alpha,
      c,
    );
  };

  let useSpace = (~borderAdjust=0, s) => {
    Private.space(
      ~theme=React.useContext(Context.context),
      ~borderAdjust,
      s,
    );
  };

  let useFontFamily = f => {
    Private.fontFamily(~theme=React.useContext(Context.context), f);
  };

  let useFontSize = f => {
    Private.fontSize(~theme=React.useContext(Context.context), f);
  };

  let useFontWeight = f => {
    Private.fontWeight(~theme=React.useContext(Context.context), f);
  };

  let useLineHeight = (~fontSize=Css.px(0), ~extraHeight=0, f) => {
    Private.lineHeight(
      ~theme=React.useContext(Context.context),
      ~fontSize,
      ~extraHeight,
      f,
    );
  };

  let useIsLight = () => {
    Private.isLight(React.useContext(Context.context));
  };
};