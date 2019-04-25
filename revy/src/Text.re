open Revy.Core;
exception InvalidValue(string);

let useTextStyles =
    (
      ~size,
      ~color as color_,
      ~fontFamily as fontFamily_=Type.Body,
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
      ~weight=Type.Normal,
      ~size=0,
      ~tag="span",
      ~style=?,
      ~lineHeight=0,
      ~color=Color.BodyText,
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
        ~weight=Type.Normal,
        ~tag="span",
        ~size=0,
        ~style=?,
        ~lineHeight=0,
        ~color=Color.BodyText,
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
        ~weight=Type.Normal,
        ~tag="div",
        ~m=Margin(Space.Auto),
        ~size=0,
        ~style=?,
        ~lineHeight=0,
        ~color=Color.BodyText,
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
        ~weight=Type.Normal,
        ~tag="p",
        ~m=Margin4(Space.NoSpace, Space.NoSpace, Space.NoSpace, Space.Double),
        ~size=0,
        ~style=?,
        ~lineHeight=0,
        ~color=Color.BodyText,
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
        ~weight=Type.Normal,
        ~tag="pre",
        ~m=Margin2(Space.NoSpace, Space.Double),
        ~size=0,
        ~style=?,
        ~lineHeight=0,
        ~color=Color.BodyText,
        ~children,
        (),
      ) => {
    let styles =
      useTextStyles(
        ~size,
        ~lineHeight,
        ~weight,
        ~color,
        ~fontFamily=Type.Mono,
        (),
      );
    let margin = Styles.useMargin(Margin(Space.NoSpace));
    let padding = Styles.usePadding(Padding(Space.Double));
    <Box
      m
      backgroundColor=Color.(
        EscapeHatch(Styles.useColor(~highlight=7, BodyBackground))
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