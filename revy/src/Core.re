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
    | `unsafeCustomValue(cssWidth)
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
    | `unsafeCustomValue(Css.length)
    | `responsive(t, t, t)
  ];
};

module Type = {
  type font = [ | `body | `title | `mono | `alt];

  type fontWeight = [ | `extraLight | `light | `normal | `bold | `extraBold];
};

module Color = {
  type backgroundColor = [
    | `primary
    | `secondary
    | `success
    | `warning
    | `error
    | `neutral
    | `brand1
    | `brand2
    | `body
    | `bodyText
    | `transparent
    | `highlight(int, backgroundColor)
    | `alpha(float, backgroundColor)
    | `unsafeCustomColor(Lab.t)
  ];

  type textColor = [
    | `primary
    | `secondary
    | `warning
    | `error
    | `success
    | `brand1
    | `brand2
    | `body
    | `quiet
    | `highlight(int, textColor)
    | `unsafeCustomColor(Lab.t)
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
  neutral: Lab.t,
  primary: Lab.t,
  secondary: Lab.t,
  success: Lab.t,
  warning: Lab.t,
  error: Lab.t,
  brand1: Lab.t,
  brand2: Lab.t,
  bodyBackground: Lab.t,
  bodyText: Lab.t,
  quiet: Lab.t,
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
module BackgroundColorContext = {
  let defaultColor: Color.backgroundColor = `body;
  let context = React.createContext(defaultColor);
  let provider = React.Context.provider(context);

  module Provider = {
    [@react.component]
    let make = (~value: Color.backgroundColor, ~children) => {
      let updateVal = value =>
        UnsafeCreateReactElement.use(
          Obj.magic(provider),
          {"value": value, "children": children},
        );
      switch (value) {
      | `transparent => children
      | `alpha(a, _) => a > 0.49 ? updateVal(value) : children
      | _ => updateVal(value)
      };
    };
  };
};
module Private = {
  let alphaFn = (alpha, lab) => {
    switch (lab) {
    | `lab(l, a, b, _) => `lab((l, a, b, alpha))
    };
  };

  let isLight = bodyBackground => {
    Lab.luminance(bodyBackground) > 50.;
  };

  let rec backgroundColor =
          (~theme, ~alpha=?, ~highlight=?, v: Color.backgroundColor) => {
    let highlightFn =
      switch (highlight) {
      | Some(h) =>
        (theme.colors.bodyBackground |> isLight ? Lab.darken : Lab.lighten)(h)
      | None => identity
      };
    (
      switch (v) {
      | `primary => theme.colors.primary
      | `neutral => theme.colors.neutral
      | `secondary => theme.colors.secondary
      | `success => theme.colors.success
      | `warning => theme.colors.warning
      | `error => theme.colors.error
      | `brand1 => theme.colors.brand1
      | `brand2 => theme.colors.brand2
      | `body => theme.colors.bodyBackground
      | `bodyText => theme.colors.bodyText
      | `highlight(i, c) => backgroundColor(~theme, ~highlight=i, c)
      | `alpha(f, c) => backgroundColor(~theme, ~alpha=f, c)
      | `transparent => `lab((100., 100., 100., 0.))
      | `unsafeCustomColor(c) => c
      }
    )
    |> highlightFn
    |> (
      switch (alpha) {
      | Some(a) => alphaFn(a)
      | None => identity
      }
    );
  };

  let textColor = (~theme, ~highlight=?, ~tint=?, v: Color.backgroundColor) => {
    let bgColor = backgroundColor(~theme, v);
    let highlightFn =
      switch (highlight) {
      | Some(h) => (bgColor |> isLight ? Lab.darken : Lab.lighten)(h)
      | None => identity
      };
    let (lightColor, darkColor) =
      isLight(theme.colors.bodyBackground)
        ? (theme.colors.bodyBackground, theme.colors.bodyText)
        : (theme.colors.bodyText, theme.colors.bodyBackground);
    let tintC =
      switch (tint) {
      | None => None
      | Some(t) => Some(backgroundColor(~theme, t))
      };
    bgColor
    |> Lab.getContrastColor(~tint=?tintC, ~lightColor, ~darkColor)
    |> highlightFn;
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
    | `normal => `normal
    | `medium => `medium
    | `bold => `bold
    | `extraBold => `extraBold
    };
  };

  let rec findMinStep = (test, i) => {
    test(i) ? i : findMinStep(test, i + 1);
  };

  let space = (~negative=false, ~theme, ~borderAdjust=0, v) => {
    let length = v => Css.px(theme.baseGridUnit * v - borderAdjust);
    let multiplier = negative ? (-1) : 1;
    switch (v) {
    | `auto => Obj.magic(Css.auto)
    | `noSpace => Css.px(0)
    | `half => 1 * multiplier |> length
    | `single => 2 * multiplier |> length
    | `double => 4 * multiplier |> length
    | `triple => 6 * multiplier |> length
    | `quad => 8 * multiplier |> length
    | `quint => 10 * multiplier |> length
    | `number(i) => i * multiplier |> length
    | `unsafeCustomValue(v) => v
    | `closest(pixels) =>
      let rem = pixels mod theme.baseGridUnit;
      let extra = rem == 0 ? 0 : 1;
      (pixels / theme.baseGridUnit + extra)
      * theme.baseGridUnit
      * multiplier
      |> Css.px;
    | `responsive(_, _, _) => 6 * multiplier |> length // TODO Fix
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
      ~baseLightness=70.,
      ~baseGridUnit=4,
      ~borderRadii={small: 4, medium: 6, large: 8},
      ~fonts={
               body: ["-apple-system", "BlinkMacSystemFont", "sans-serif"],
               title: ["-apple-system", "BlinkMacSystemFont", "sans-serif"],
               mono: ["monospace"],
               alt: ["-apple-system", "BlinkMacSystemFont", "sans-serif"],
             },
      ~hues={
              primary: `rgb((18, 120, 240)) |> Lab.fromRGB,
              secondary: `rgb((100, 100, 100)) |> Lab.fromRGB,
              warning: `rgb((214, 135, 5)) |> Lab.fromRGB,
              success: `rgb((44, 173, 2)) |> Lab.fromRGB,
              error: `rgb((230, 26, 26)) |> Lab.fromRGB,
              brand1: `rgb((213, 54, 222)) |> Lab.fromRGB,
              brand2: `rgb((54, 213, 222)) |> Lab.fromRGB,
              bodyBackground: `lab((100., 0., 0., 1.)),
              bodyText: `lab((10., 0., 0., 1.)),
              neutral: `rgb((40, 40, 40)) |> Lab.fromRGB,
              quiet: `rgb((130, 130, 130)) |> Lab.fromRGB,
            },
      ~gridWidth as width=960,
      (),
    ) => {
  let colors =
    Lab.{
      primary: hues.primary |> lightness(baseLightness),
      secondary: hues.secondary |> lightness(baseLightness),
      warning: hues.warning |> lightness(baseLightness),
      success: hues.success |> lightness(baseLightness),
      error: hues.error |> lightness(baseLightness),
      brand1: hues.brand1 |> lightness(baseLightness),
      brand2: hues.brand2 |> lightness(baseLightness),
      bodyBackground: hues.bodyBackground,
      bodyText: hues.bodyText,
      quiet: hues.quiet,
      neutral: hues.neutral |> lightness(80.),
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
      UnsafeCreateReactElement.use(
        Obj.magic(provider),
        {"value": value, "children": children},
      );
    };
  };
};
module Animations = {
  open Css;
  let focusAnimation__ =
    keyframes([
      (0, [opacity(1.), filter([`saturate(100.)])]),
      (50, [opacity(0.6), filter([`saturate(150.)])]),
      (100, [opacity(1.), filter([`saturate(100.)])]),
    ]);
  let focus = [
    animationName(focusAnimation__),
    animationDuration(1000),
    animationIterationCount(`infinite),
  ];
};
module Styles = {
  let marginSpace = (theme, v) => Obj.magic(Private.space(~theme, v)); // TODO fix
  let rec marginStyles_ = (theme, p) => {
    let marginSpace = v => Private.space(~theme, v);
    switch (p) {
    | None => []
    | Some(value) =>
      switch (value) {
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
      }
    };
  };
  let rec paddingStyles_ = (theme, p) => {
    switch (p) {
    | None => []
    | Some(value) =>
      switch (value) {
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
      }
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
    | `unsafeCustomValue(i) => Css.[width(i)]
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

  let useColor = (~highlight=?, ~alpha=?, c: Color.backgroundColor) => {
    Private.backgroundColor(
      ~theme=React.useContext(Context.context),
      ~highlight?,
      ~alpha?,
      c,
    )
    |> Lab.toCss;
  };
  let useLabColor = (~highlight=?, ~alpha=?, c: Color.backgroundColor) => {
    Private.backgroundColor(
      ~theme=React.useContext(Context.context),
      ~highlight?,
      ~alpha?,
      c,
    );
  };
  let useTextColor = (~tint=?, ~highlight=0, ~background=?, ()) => {
    let bg =
      switch (background) {
      | None => React.useContext(BackgroundColorContext.context)
      | Some(v) => v
      };
    Private.textColor(
      ~theme=React.useContext(Context.context),
      ~highlight,
      ~tint?,
      bg,
    )
    |> Lab.toCss;
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

  let useSpace = (~negative=?, ~borderAdjust=0, s) => {
    Private.space(
      ~negative?,
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