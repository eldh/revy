[@bs.config {jsx: 3}];

let highlightShadow =
  ThemeUtil.Style.shadows(
    Css.[
      boxShadow(~y=px(-1), ~blur=px(0), ~inset=true, hsla(0, 0, 100, 0.2)),
      boxShadow(~y=px(1), ~blur=px(0), ~inset=true, hsla(0, 0, 0, 0.2)),
    ],
  );

let useInputStyles = (~m, ()) => {
  let theme = React.useContext(ThemeContext.context);
  let styleStyles =
    switch (Theme.Flat) {
    | Flat => []
    | Raised => [highlightShadow]
    | Layers =>
      Css.[
        boxShadow(
          ~y=px(3),
          ~blur=px(5),
          ~inset=true,
          hsla(0, 0, 0, 0.15),
        ),
      ]
    };
  Theme.(
    Css.[
      [
        Css.padding2(
          ~v=theme.space(~borderAdjust=0, Space.Single),
          ~h=theme.space(~borderAdjust=0, Space.Single),
        ),
        textDecoration(`none),
        cursor(`pointer),
        lineHeight(theme.lineHeight(~fontSize=theme.fontSize(0), ())),
        fontSize(theme.fontSize(0)),
        fontFamily(theme.fontFamily(Theme.Type.Body)),
        borderWidth(px(0)),
        borderColor(theme.color(Color.Transparent)),
        borderRadius(theme.space(Theme.Space.Single)),
        borderStyle(`solid),
        backgroundColor(theme.color(~highlight=20, Color.BodyBackground)),
        color(theme.color(Color.BodyText)),
        focus([
          outlineStyle(`none),
          borderColor(theme.color(Color.Primary)),
        ]),
        // highlightShadow,
      ],
      Theme.Styles.margin(theme, m),
      styleStyles,
    ]
    ->List.concat
    ->Css.style
  );
};

[@react.component __MODULE__]
let make =
    (
      ~onClick as _=?,
      ~onChange,
      ~type_="text",
      ~disabled=false,
      ~onFocus=ignore,
      ~onBlur=ignore,
      ~placeholder="",
      ~m=Theme.margin(NoSpace),
      ~value,
      (),
    ) => {
  <input
    value
    placeholder
    disabled
    onChange
    onFocus
    className={useInputStyles(~m, ())}
    type_
  />;
};