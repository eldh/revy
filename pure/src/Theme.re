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
  | Margin2(Space.t, Space.t)
  | Margin4(Space.t, Space.t, Space.t, Space.t)
  | ResponsiveMargin(margin, margin, margin);

type padding =
  | Padding(Space.t)
  | Padding2(Space.t, Space.t)
  | Padding4(Space.t, Space.t, Space.t, Space.t)
  | ResponsivePadding(padding, padding, padding);

/**
  Base type for themes
 */
type t = {
  color: (~alpha: float=?, ~highlight: int=?, Color.t) => Css.color,
  // length: length => Css.length,
  fontFamily: Type.font => string,
  fontSize: int => cssFontSize,
  fontWeight: Type.fontWeight => cssFontWeight,
  width: int,
  isLight: bool,
  space: (~borderAdjust: int=?, Space.t) => Css.length,
  lineHeight:
    (~fontSize: cssFontSize=?, ~extraHeight: int=?, unit) => cssLineHeight,
};
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

let cssMargin = m => m->Obj.magic->Css.margin;
let cssMarginLeft = m => m->Obj.magic->Css.marginLeft;
let cssMarginRight = m => m->Obj.magic->Css.marginRight;
let cssMarginTop = m => m->Obj.magic->Css.marginTop;
let cssMarginBottom = m => m->Obj.magic->Css.marginBottom;
let cssMargin2 = (~v, ~h) => Css.margin2(~v=Obj.magic(v), ~h=Obj.magic(h));
let cssMargin4 = (~top, ~bottom, ~left, ~right) =>
  Css.margin4(
    ~top=Obj.magic(top),
    ~bottom=Obj.magic(bottom),
    ~left=Obj.magic(left),
    ~right=Obj.magic(right),
  );

let responsive = (_theme, (s, m, l)) => {
  Css.[media("(min-width: 30em)", m), media("(min-width: 50em)", l), ...s];
};

let margin = v => Margin(v);
let margin2 = (~v, ~h) => Margin2(v, h);
let margin4 = (~top, ~bottom, ~left, ~right) =>
  Margin4(top, bottom, left, right);
let padding = v => Padding(v);
let padding2 = (~v, ~h) => Padding2(v, h);
let padding4 = (~top, ~bottom, ~left, ~right) =>
  Padding4(top, bottom, left, right);

let make =
    (
      ~fontScale: float,
      ~fonts as fontsArg: fonts,
      ~colors as colorsArg: colors,
      ~baseFontSize: int,
      ~baseGridUnit: int,
      ~gridWidth=960,
      (),
    ) => {
  open Css;

  let isLight = ThemeUtil.Color.isLight(colorsArg.bodyBackground);

  let color = (~alpha=1., ~highlight=0, v) => {
    open Color;
    let highlightFn =
      (isLight ? ThemeUtil.Color.darken : ThemeUtil.Color.lighten)(highlight);
    (
      switch (v) {
      | Primary => colorsArg.primary
      | Secondary => colorsArg.secondary
      | Success => colorsArg.success
      | Warning => colorsArg.warning
      | Error => colorsArg.error
      | BodyBackground => colorsArg.bodyBackground
      | PrimaryText => colorsArg.primaryText
      | SecondaryText => colorsArg.secondaryText
      | WarningText => colorsArg.warningText
      | ErrorText => colorsArg.errorText
      | SuccessText => colorsArg.successText
      | BodyText => colorsArg.bodyText
      | QuietText => colorsArg.quietText
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

  let fontFamily = v =>
    Type.(
      switch (v) {
      | Title => fontsArg.title
      | Mono => fontsArg.mono
      | Body => fontsArg.body
      | Alt => fontsArg.alt
      }
    )
    |> String.concat(", ");

  let fontSize = n => {
    (fontScale ** n->float_of_int *. baseFontSize->float_of_int)
    ->int_of_float
    ->px;
  };
  let fontWeight = v => {
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

  let space = (~borderAdjust=0, v) => {
    let length = v => px(baseGridUnit * v - borderAdjust);
    switch (v) {
    | Space.Auto => Obj.magic(Css.auto)
    | NoSpace => Css.px(0)
    | Half => 1->length
    | Single => 2->length
    | Double => 3->length
    | Triple => 4->length
    | Responsive(_, _, _) => 6->length // TODO Fix
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

  let lineHeight = (~fontSize=px(0), ~extraHeight=0, _) => {
    let length = v => px(baseGridUnit * v);
    let va =
      findMinStep(
        i =>
          (i * baseGridUnit)->float_of_int > fontSize->getPx->float_of_int
          *. 1.25,
        0,
      );
    (va + extraHeight)->length;
  };

  let width = gridWidth;

  {
    color,
    fontFamily,
    fontSize,
    fontWeight,
    isLight,
    lineHeight,
    space,
    width,
  };
};
module DefaultTheme = {
  let theme =
    make(
      ~fontScale=1.25,
      ~baseFontSize=14,
      ~baseGridUnit=5,
      ~fonts={
        body: ["-apple-system", "BlinkMacSystemFont", "sans-serif"],
        title: ["-apple-system", "BlinkMacSystemFont", "sans-serif"],
        mono: ["monospace"],
        alt: ["-apple-system", "BlinkMacSystemFont", "sans-serif"],
      },
      ~colors=
        Css.{
          primary: Lab.(fromRGB((36, 133, 222)) |> lighten(25) |> toCssRGB),
          primaryText: rgb(0, 0, 0),
          secondary:
            Lab.(fromRGB((20, 10, 0)) |> lighten(25) |> toCssRGB),
          secondaryText: rgb(255, 255, 255),
          warning: Lab.(fromRGB((214, 149, 5)) |> lighten(25) |> toCssRGB),
          warningText: rgb(0, 0, 0),
          success: Lab.(fromRGB((44, 173, 2)) |> lighten(25) |> toCssRGB),
          successText: rgb(0, 0, 0),
          error: Lab.(fromRGB((211, 26, 26)) |> lighten(25) |> toCssRGB),
          errorText: rgb(0, 0, 0),
          bodyBackground: rgb(255, 255, 255),
          bodyText: rgb(40, 40, 40),
          quietText: rgb(70, 70, 70),
        },
      (),
    );
};

module Context = {
  let context = React.createContext(DefaultTheme.theme);
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
  let marginSpace = (theme, v) => Obj.magic(theme.space(v));
  let rec marginStyles_ = (theme, p) => {
    let marginSpace = v => Obj.magic(theme.space(v));
    switch (p) {
    | Auto => [Css.margin(`auto)]
    | Margin(i) => [Css.margin(marginSpace(i))]
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
    | Padding(i) => [Css.padding(theme.space(i))]
    | Padding2(x, y) => [
        Css.padding2(~v=theme.space(y), ~h=theme.space(x)),
      ]
    | Padding4(l, t, r, b) => [
        Css.padding4(
          ~top=theme.space(t),
          ~bottom=theme.space(b),
          ~right=theme.space(r),
          ~left=theme.space(l),
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

  let usePadding = p => {
    let theme = React.useContext(Context.context);
    Css.padding(theme.space(p));
  };

  let useMargin = m => {
    let space = marginSpace(React.useContext(Context.context));
    Css.margin(space(m));
  };
  let usePadding2 = (~v, ~h) => {
    let theme = React.useContext(Context.context);
    Css.padding2(~v=theme.space(v), ~h=theme.space(h));
  };

  let useMargin2 = (~v, ~h) => {
    let space = marginSpace(React.useContext(Context.context));
    Css.margin2(~v=space(v), ~h=space(h));
  };
  let usePadding4 = (~top, ~bottom, ~left, ~right) => {
    let theme = React.useContext(Context.context);
    Css.padding4(
      ~top=theme.space(top),
      ~bottom=theme.space(bottom),
      ~left=theme.space(left),
      ~right=theme.space(right),
    );
  };
  let margin4 = (~top, ~bottom, ~left, ~right) => {
    let space = marginSpace(React.useContext(Context.context));
    Css.margin4(
      ~top=space(top),
      ~bottom=space(bottom),
      ~left=space(left),
      ~right=space(right),
    );
  };

  /** Width styles yo */
  let useWidth = w => widthStyles_(React.useContext(Context.context), w);

  let useColor = (~highlight=0, ~alpha=1., color) => {
    React.useContext(Context.context).color(~highlight, ~alpha, color);
  };

  let useSpace = (~borderAdjust=0, space) => {
    React.useContext(Context.context).space(~borderAdjust, space);
  };

  let useFontFamily = f => {
    React.useContext(Context.context).fontFamily(f);
  };

  let useFontSize = f => {
    React.useContext(Context.context).fontSize(f);
  };

  let useFontWeight = f => {
    React.useContext(Context.context).fontWeight(f);
  };

  let useLineHeight = (~fontSize=Css.px(0), ~extraHeight=0, f) => {
    React.useContext(Context.context).lineHeight(~fontSize, ~extraHeight, f);
  };

  let useIsLight = () => {
    React.useContext(Context.context).isLight;
  };
};