open Revy.Core;
exception InvalidValue(string);

let useTextStyles =
    (
      ~size,
      ~color as color_,
      ~fontFamily as fontFamily_=`body,
      ~lineHeight as lineHeight_,
      ~weight as weight_,
      (),
    ) => {
  let sizeVal = Styles.useFontSize(size);
  Css.[
    color(Styles.useColor(color_)),
    fontSize(sizeVal),
    fontFamily(Styles.useFontFamily(fontFamily_)),
    lineHeight(
      Styles.useLineHeight(~fontSize=sizeVal, ~extraHeight=lineHeight_, ()),
    ),
    fontWeight(Styles.useFontWeight(weight_)),
  ];
};

[@react.component]
let make =
    (
      ~weight=`normal,
      ~size=0,
      ~tag="span",
      ~style=?,
      ~lineHeight=0,
      ~color=`bodyText,
      ~children,
      (),
    ) => {
  let styles = useTextStyles(~size, ~lineHeight, ~weight, ~color, ());
  EscapeHatch.use(
    tag,
    {
      "className": {
        (
          switch (style) {
          | Some(p) => [styles, p] |> List.concat
          | None => styles
          }
        )
        |> Css.style;
      },
      "children": children,
    },
  );
};

module String = {
  [@react.component]
  let make =
      (
        ~weight=`normal,
        ~tag="span",
        ~size=0,
        ~style=?,
        ~lineHeight=0,
        ~color=`bodyText,
        ~children,
        (),
      ) => {
    let styles = useTextStyles(~size, ~lineHeight, ~weight, ~color, ());
    EscapeHatch.use(
      tag,
      {
        "className": {
          (
            switch (style) {
            | Some(p) => [styles, p] |> List.concat
            | None => styles
            }
          )
          |> Css.style;
        },
        "children": children |> React.string,
      },
    );
  };
};

module Block = {
  [@react.component]
  let make =
      (
        ~weight=`normal,
        ~tag="div",
        ~m=`margin(`auto),
        ~size=0,
        ~style=?,
        ~lineHeight=0,
        ~color=`bodyText,
        ~children,
        (),
      ) => {
    let styles = useTextStyles(~size, ~lineHeight, ~weight, ~color, ());
    let margin = Styles.useMargin(m);
    EscapeHatch.use(
      tag,
      {
        "className": {
          (
            switch (style) {
            | Some(p) => [styles, margin, p]
            | None => [styles, margin]
            }
          )
          |> List.concat
          |> Css.style;
        },
        "children": children,
      },
    );
  };
};

module Paragraph = {
  [@react.component]
  let make =
      (
        ~weight=`normal,
        ~tag="p",
        ~m=`margin4(`noSpace, `noSpace, `noSpace, `double),
        ~size=0,
        ~style=?,
        ~lineHeight=0,
        ~color=`bodyText,
        ~children,
        (),
      ) => {
    let styles = useTextStyles(~size, ~lineHeight, ~weight, ~color, ());
    let margin = Styles.useMargin(m);
    EscapeHatch.use(
      tag,
      {
        "className": {
          (
            switch (style) {
            | Some(p) => [styles, margin, p]
            | None => [styles, margin]
            }
          )
          |> List.concat
          |> Css.style;
        },
        "children": children |> React.string,
      },
    );
  };
};

module Code = {
  [@react.component]
  let make =
      (
        ~weight=`normal,
        ~tag="pre",
        ~m=`margin2(`noSpace, `double),
        ~size=0,
        ~style=?,
        ~lineHeight=0,
        ~color=`bodyText,
        ~children,
        (),
      ) => {
    let styles =
      useTextStyles(
        ~size,
        ~lineHeight,
        ~weight,
        ~color,
        ~fontFamily=`mono,
        (),
      );
    let margin = Styles.useMargin(`margin(`noSpace));
    let padding = Styles.usePadding(`padding(`double));
    <Box
      m
      backgroundColor=(
        `escapeHatch(Styles.useColor(~highlight=7, `bodyBackground))
      )
      borderRadius={Css.px(6)}
      style=Css.[width(pct(100.)), overflow(`scroll)]>
      {EscapeHatch.use(
         tag,
         {
           "className":
             {(
                switch (style) {
                | Some(p) => [styles, margin, padding, p]
                | None => [styles, margin, padding]
                }
              )
              |> List.concat
              |> Css.style},
           "children": children |> React.string,
         },
       )}
    </Box>;
  };
};