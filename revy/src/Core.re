// type cssFontFamily = array(string);
exception InvalidValue(string);
let identity = a => a;

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
  type t = [
    | `percent(float)
    | `eighth
    | `sixth
    | `quarter
    | `third
    | `half
    | `full
    | `escapeHatch(cssWidth)
    | `auto
    | `responsive(t, t, t)
  ];
};

module Space = {
  type t = [
    | `auto
    | `noSpace
    | `half
    | `single
    | `double
    | `triple
    | `quad
    | `quint
    | `number(int)
    | `escapeHatch(Css.length)
    | `responsive(t, t, t)
  ];
};

module Type = {
  type font = [ | `body | `title | `mono | `alt];

  type fontWeight = [ | `extraLight | `light | `normal | `bold | `extraBold];
};

module Color = {
  type t = [
    | `primary
    | `secondary
    | `success
    | `warning
    | `error
    | `brand1
    | `brand2
    | `bodyBackground
    | `primaryText
    | `secondaryText
    | `warningText
    | `errorText
    | `successText
    | `brand1Text
    | `brand2Text
    | `bodyText
    | `quietText
    | `transparent
    | `highlight(int, t)
    | `escapeHatch(Css.color)
  ];
};

type margin = [
  | `auto
  | `margin(Space.t)
  | `marginTop(Space.t)
  | `marginBottom(Space.t)
  | `marginLeft(Space.t)
  | `marginRight(Space.t)
  | `margin2(Space.t, Space.t)
  | `margin4(Space.t, Space.t, Space.t, Space.t)
  | `responsive(margin, margin, margin)
];

type padding = [
  | `padding(Space.t)
  | `paddingTop(Space.t)
  | `paddingBottom(Space.t)
  | `paddingLeft(Space.t)
  | `paddingRight(Space.t)
  | `padding2(Space.t, Space.t)
  | `padding4(Space.t, Space.t, Space.t, Space.t)
  | `responsive(padding, padding, padding)
];

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

  let isLight = bodyBackground => {
    switch (bodyBackground) {
    | `rgb(_r, _g, _b) as rgb => Lab.luminanceRGB(rgb) > 0.5
    | `rgba(r, g, b, _a) => Lab.luminanceRGB(`rgb((r, g, b))) > 0.5
    | _ => true
    };
  };

  let rec color = (~theme, ~alpha=1., ~highlight=0, v) => {
    let highlightFn =
      (theme.colors.bodyBackground |> isLight ? darken : lighten)(highlight);
    (
      switch (v) {
      | `primary => theme.colors.primary
      | `secondary => theme.colors.secondary
      | `success => theme.colors.success
      | `warning => theme.colors.warning
      | `error => theme.colors.error
      | `brand1 => theme.colors.brand1
      | `brand2 => theme.colors.brand2
      | `bodyBackground => theme.colors.bodyBackground
      | `primaryText => theme.colors.primary |> Lab.getContrastColorRGB
      | `secondaryText => theme.colors.secondary |> Lab.getContrastColorRGB
      | `warningText => theme.colors.warning |> Lab.getContrastColorRGB
      | `errorText => theme.colors.error |> Lab.getContrastColorRGB
      | `successText => theme.colors.success |> Lab.getContrastColorRGB
      | `brand1Text => theme.colors.brand1 |> Lab.getContrastColorRGB
      | `brand2Text => theme.colors.brand2 |> Lab.getContrastColorRGB
      | `bodyText => theme.colors.bodyText
      | `quietText => theme.colors.quietText
      | `highlight(i, c) => color(~theme, ~highlight=i, c)
      | `transparent => `transparent
      | `escapeHatch(c) => c
      }
    )
    |> highlightFn
    |> (
      switch (alpha) {
      | 1. => identity
      | a => alphaFn(a)
      }
    );
  };

  let fontFamily = (~theme, v) =>
    (
      switch (v) {
      | `title => theme.fonts.title
      | `mono => theme.fonts.mono
      | `body => theme.fonts.body
      | `alt => theme.fonts.alt
      }
    )
    |> String.concat(", ");

  let fontSize = (~theme, n) => {
    (theme.fontScale ** n->float_of_int *. theme.baseFontSize->float_of_int)
    ->int_of_float
    ->Css.px;
  };

  let fontWeight = (~theme as _, v) => {
    switch (v) {
    | `extraLight => `extraLight
    | `light => `light
    | `bold => `bold
    | `normal => `normal
    | `extraBold => `extraBold
    };
  };

  let rec findMinStep = (test, i) => {
    test(i) ? i : findMinStep(test, i + 1);
  };

  let space = (~theme, ~borderAdjust=0, v) => {
    let length = v => Css.px(theme.baseGridUnit * v - borderAdjust);
    switch (v) {
    | `auto => Obj.magic(Css.auto)
    | `noSpace => Css.px(0)
    | `half => 1 |> length
    | `single => 2 |> length
    | `double => 3 |> length
    | `triple => 6 |> length
    | `quad => 8 |> length
    | `quint => 10 |> length
    | `number(i) => i |> length
    | `escapeHatch(v) => v
    | `closest(pixels) =>
      let rem = pixels mod theme.baseGridUnit;
      let extra = rem == 0 ? 0 : 1;
      (pixels / theme.baseGridUnit + extra)
      * theme.baseGridUnit
      |> Log.pass(extra)
      |> Css.px;
    | `responsive(_, _, _) => 6 |> length // TODO Fix
    };
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
          i
          * theme.baseGridUnit
          |> float_of_int > (fontSize |> getPx |> float_of_int)
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
              primary: rgb(18, 120, 240),
              secondary: rgb(100, 100, 100),
              warning: rgb(214, 135, 5),
              success: rgb(44, 173, 2),
              error: rgb(230, 26, 26),
              brand1: rgb(213, 54, 222),
              brand2: rgb(54, 213, 222),
              bodyBackground: rgb(255, 255, 255),
              bodyText: rgb(40, 40, 40),
              neutral: rgb(40, 40, 40),
              quietText: rgb(130, 130, 130),
            },
      ~gridWidth as width=960,
      (),
    ) => {
  let baseLightness = Private.isLight(hues.bodyBackground) ? 70. : 70.;
  let colors =
    Lab.{
      primary: hues.primary |> fromRGB |> lightness(baseLightness) |> toRGB,
      secondary:
        hues.secondary |> fromRGB |> lightness(baseLightness) |> toRGB,
      warning: hues.warning |> fromRGB |> lightness(baseLightness) |> toRGB,
      success: hues.success |> fromRGB |> lightness(baseLightness) |> toRGB,
      error: hues.error |> fromRGB |> lightness(baseLightness) |> toRGB,
      brand1: hues.brand1 |> fromRGB |> lightness(baseLightness) |> toRGB,
      brand2: hues.brand2 |> fromRGB |> lightness(baseLightness) |> toRGB,
      bodyBackground: hues.bodyBackground,
      bodyText: hues.bodyText,
      quietText: hues.quietText,
      neutral: hues.neutral |> fromRGB |> lightness(80.) |> toRGB,
    };
  {colors, fonts, fontScale, baseFontSize, baseGridUnit, width, borderRadii};
};

module DefaultTheme = {
  let theme = createTheme();
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
    let marginSpace = v => Private.space(~theme, v);
    switch (p) {
    | `auto => [Css.margin(`auto)]
    | `margin(i) => [Css.margin(marginSpace(i))]
    | `marginTop(i) => [Css.marginTop(marginSpace(i))]
    | `marginBottom(i) => [Css.marginBottom(marginSpace(i))]
    | `marginLeft(i) => [Css.marginLeft(marginSpace(i))]
    | `marginRight(i) => [Css.marginRight(marginSpace(i))]
    | `margin2(x, y) => [
        Css.margin2(~v=marginSpace(y), ~h=marginSpace(x)),
      ]
    | `margin4(l, t, r, b) => [
        Css.margin4(
          ~top=marginSpace(t),
          ~bottom=marginSpace(b),
          ~right=marginSpace(r),
          ~left=marginSpace(l),
        ),
      ]
    | `responsive(s, m, l) =>
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
    | `padding(i) => [Css.padding(Private.space(~theme, i))]
    | `paddingTop(i) => [Css.paddingTop(Private.space(~theme, i))]
    | `paddingBottom(i) => [Css.paddingBottom(Private.space(~theme, i))]
    | `paddingLeft(i) => [Css.paddingLeft(Private.space(~theme, i))]
    | `paddingRight(i) => [Css.paddingRight(Private.space(~theme, i))]
    | `padding2(x, y) => [
        Css.padding2(
          ~v=Private.space(~theme, y),
          ~h=Private.space(~theme, x),
        ),
      ]
    | `padding4(l, t, r, b) => [
        Css.padding4(
          ~top=Private.space(~theme, t),
          ~bottom=Private.space(~theme, b),
          ~right=Private.space(~theme, r),
          ~left=Private.space(~theme, l),
        ),
      ]
    | `responsive(s, m, l) =>
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
    | `percent(v) => Css.[width(pct(v))]
    | `eighth => Css.[width(pct(100. /. 8.))]
    | `sixth => Css.[width(pct(100. /. 6.))]
    | `quarter => Css.[width(pct(100. /. 4.))]
    | `third => Css.[width(pct(100. /. 3.))]
    | `half => Css.[width(pct(100. /. 2.))]
    | `full => Css.[maxWidth(px(w)), width(pct(100.))]
    | `auto => Css.[width(`auto)]
    | `escapeHatch(i) => Css.[width(i)]
    | `responsive(s, m, l) =>
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
    Private.isLight(React.useContext(Context.context).colors.bodyBackground);
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