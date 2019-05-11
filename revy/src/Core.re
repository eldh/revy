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

module Layout = {
  type t =
    | Percent(float)
    | Eighth
    | Sixth
    | Quarter
    | Third
    | Half
    | Full
    | EscapeHatch(cssWidth)
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
    | EscapeHatch(Css.length)
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
    | Brand1
    | Brand2
    | Brand3
    | Brand4
    | BodyBackground
    | PrimaryText
    | SecondaryText
    | WarningText
    | ErrorText
    | SuccessText
    | Brand1Text
    | Brand2Text
    | Brand3Text
    | Brand4Text
    | BodyText
    | QuietText
    | Transparent
    | Highlight(int, t)
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

type borderRadii = {
  small: int,
  medium: int,
  large: int,
};

type colors = {
  neutral: Css.color,
  primary: Css.color,
  secondary: Css.color,
  success: Css.color,
  warning: Css.color,
  error: Css.color,
  brand1: Css.color,
  brand2: Css.color,
  brand3: Css.color,
  brand4: Css.color,
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
  borderRadii,
};

let responsive = (_theme, (s, m, l)) => {
  Css.[media("(min-width: 30em)", m), media("(min-width: 50em)", l), ...s];
};
module Private = {
  let alphaFn = (v, c) => {
    Css.(
      switch (c) {
      | `rgba(r, g, b, _a) => rgba(r, g, b, v)
      | `rgb(r, g, b) => rgba(r, g, b, v)
      | _ => c
      }
    );
  };

  let lighten = (factor, color: Css.color) =>
    switch (color) {
    | `rgb(_, _, _) as rgb => Lab.(rgb |> lightenRGB(factor))
    | `rgba(r, g, b, a) =>
      Lab.(`rgb((r, g, b)) |> lightenRGB(factor) |> alphaFn(a))
    | _ => color // TODO: Error / handle
    };

  let darken = (factor, rgb) => lighten(factor * (-1), rgb);

  let highlight = (factor, c: Css.color) =>
    switch (c) {
    | `rgb(_, _, _) as rgb => Lab.(rgb |> highlightRGB(factor))
    | `rgba(r, g, b, a) =>
      Lab.(`rgb((r, g, b)) |> highlightRGB(factor) |> alphaFn(a))
    | _ => c
    };

  let isLight = theme => {
    switch (theme.colors.bodyBackground) {
    | `rgb(_r, _g, _b) as rgb => Lab.luminanceRGB(rgb) > 0.5
    | `rgba(r, g, b, _a) => Lab.luminanceRGB(`rgb((r, g, b))) > 0.5
    | _ => true
    };
  };

  let rec color =
          (~theme, ~alpha=1., ~highlight=0, ~lighten as lightenVal=0, v) => {
    open Color;
    let highlightFn = (theme |> isLight ? darken : lighten)(highlight);
    (
      switch (v) {
      | Primary => theme.colors.primary
      | Secondary => theme.colors.secondary
      | Success => theme.colors.success
      | Warning => theme.colors.warning
      | Error => theme.colors.error
      | Brand1 => theme.colors.brand1
      | Brand2 => theme.colors.brand2
      | Brand3 => theme.colors.brand3
      | Brand4 => theme.colors.brand4
      | BodyBackground => theme.colors.bodyBackground
      | PrimaryText =>
        theme.colors.primary |> Obj.magic |> Lab.getContrastColorRGB
      | SecondaryText =>
        theme.colors.secondary |> Obj.magic |> Lab.getContrastColorRGB
      | WarningText =>
        theme.colors.warning |> Obj.magic |> Lab.getContrastColorRGB
      | ErrorText => theme.colors.error |> Obj.magic |> Lab.getContrastColorRGB
      | SuccessText =>
        theme.colors.success |> Obj.magic |> Lab.getContrastColorRGB
      | Brand1Text =>
        theme.colors.brand1 |> Obj.magic |> Lab.getContrastColorRGB
      | Brand2Text =>
        theme.colors.brand2 |> Obj.magic |> Lab.getContrastColorRGB
      | Brand3Text =>
        theme.colors.brand3 |> Obj.magic |> Lab.getContrastColorRGB
      | Brand4Text =>
        theme.colors.brand4 |> Obj.magic |> Lab.getContrastColorRGB
      | BodyText => theme.colors.bodyText
      | QuietText => theme.colors.quietText
      | Highlight(i, c) => color(~theme, ~highlight=i, c)
      | Transparent => `transparent
      | EscapeHatch(c) => c
      }
    )
    |> highlightFn
    |> (
      switch (lightenVal) {
      | 0 => (a => a)
      | a => lighten(a)
      }
    )
    |> (
      switch (alpha) {
      | 1. => (a => a)
      | a => alphaFn(a)
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
    let length = v => Css.px(theme.baseGridUnit * v - borderAdjust);
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
    | EscapeHatch(v) => Obj.magic(v)
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
let createTheme =
    (
      ~fontScale=1.25,
      ~baseFontSize=16,
      ~baseGridUnit=4,
      ~borderRadii={small: 4, medium: 6, large: 8},
      ~fonts={
               body: ["-apple-system", "BlinkMacSystemFont", "sans-serif"],
               title: ["-apple-system", "BlinkMacSystemFont", "sans-serif"],
               mono: ["monospace"],
               alt: ["-apple-system", "BlinkMacSystemFont", "sans-serif"],
             },
      ~hues=Css.{
                          primary: rgb(36, 133, 222),
                          secondary: rgb(100, 100, 100),
                          warning: rgb(214, 135, 5),
                          success: rgb(44, 173, 2),
                          error: rgb(230, 26, 26),
                          brand1: rgb(213, 54, 222),
                          brand2: rgb(54, 213, 222),
                          brand3: rgb(213, 222, 54),
                          brand4: rgb(28, 222, 125),
                          bodyBackground: rgb(255, 255, 255),
                          bodyText: rgb(40, 40, 40),
                          neutral: rgb(40, 40, 40),
                          quietText: rgb(130, 130, 130),
                        },
      ~gridWidth as width=960,
      (),
    ) => {
  let colors =
    Lab.{
      primary: hues.primary |> fromRGB |> lightness(80.) |> toRGB,
      secondary: hues.secondary |> fromRGB |> lightness(80.) |> toRGB,
      warning: hues.warning |> fromRGB |> lightness(80.) |> toRGB,
      success: hues.success |> fromRGB |> lightness(80.) |> toRGB,
      error: hues.error |> fromRGB |> lightness(80.) |> toRGB,
      brand1: hues.brand1 |> fromRGB |> lightness(80.) |> toRGB,
      brand2: hues.brand2 |> fromRGB |> lightness(80.) |> toRGB,
      brand3: hues.brand3 |> fromRGB |> lightness(80.) |> toRGB,
      brand4: hues.brand4 |> fromRGB |> lightness(80.) |> toRGB,
      bodyBackground: hues.bodyBackground,
      bodyText: hues.bodyText,
      quietText: hues.quietText,
      neutral: hues.neutral |> fromRGB |> lightness(80.) |> toRGB,
    };
  {colors, fonts, fontScale, baseFontSize, baseGridUnit, width, borderRadii};
};

// let standardColors = [| `primary]

module DefaultTheme = {
  let theme = createTheme();
};

module type ThemeDef = {
  type colorDef;
  let getColor: colorDef => Css.color;
};

module MakeTheme = (Defs: ThemeDef) => {
  let getColor = Defs.getColor;
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
    | EscapeHatch(i) => Css.[width(i)]
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

  let useColor = (~highlight=0, ~lighten=0, ~alpha=1., c) => {
    Private.color(
      ~theme=React.useContext(Context.context),
      ~highlight,
      ~lighten,
      ~alpha,
      c,
    );
  };

  let useBorderRadius = s => {
    let theme = React.useContext(Context.context);
    (
      switch (s) {
      | `small => theme.borderRadii.small
      | `medium => theme.borderRadii.medium
      | `large => theme.borderRadii.large
      }
    )
    |> Css.px;
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

  let setBodyStyle: Js.Json.t => unit = [%raw
    rule => "{
  let k = Object.keys(rule)[0].replace(/([a-z])([A-Z])/g, '$1-$2').toLowerCase();
  window.document.body.style[k] = rule[Object.keys(rule)[0]]
  return /* () */0
  }"
  ];
  type listenerId;
  type mediaQueryList = {
    .
    "matches": bool,
    "addListener": [@bs.meth] ((unit => unit) => listenerId),
    "removeListener": [@bs.meth] (listenerId => unit),
  };
  [@bs.val] [@bs.scope "window"]
  external matchMedia: string => mediaQueryList = "matchMedia";

  let useMatchesMedia = query => {
    let mql = matchMedia(query);
    let (value, setValue) = React.useState(() => mql##matches);

    React.useLayoutEffect1(
      () => {
        let handler = mql##addListener(() => setValue(_ => mql##matches));
        Some(() => mql##removeListener(handler));
      },
      [||],
    );

    value;
  };

  let usePrefersDarkMode = () =>
    useMatchesMedia("(prefers-color-scheme: dark)");

  let useBodyStyle = rules => {
    React.useLayoutEffect1(
      () => {
        List.map(rule => setBodyStyle(Css.toJson([rule])), rules) |> ignore;
        None;
      },
      rules |> Array.of_list,
    );
  };
};