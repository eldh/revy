open Core;
exception InvalidValue(string);

let getTextStyles =
    (
      ~size,
      ~quiet=false,
      ~tintColor as tint=?,
      ~backgroundColor as bg_=?,
      ~fontFamily as fontFamily_=`body,
      ~textDecoration as textDecoration_=`none,
      ~lineHeight as lineHeight_,
      ~weight as weight_,
      (),
    ) => {
  let sizeVal = Styles.getFontSize(size);
  let bgStyles =
    switch (bg_) {
    | Some(p) => Css.[background(Styles.getColor(p))]
    | None => []
    };
  Css.[
    color(
      Styles.getTextColor(
        ~highlight=?quiet ? Some(-30) : None,
        ~tint?,
        ~background=?bg_,
        (),
      ),
    ),
    overflowY(`visible),
    fontSize(sizeVal),
    textDecoration(textDecoration_),
    fontFamily(Styles.getFontFamily(fontFamily_)),
    lineHeight(
      Styles.getLineHeight(~fontSize=sizeVal, ~extraHeight=lineHeight_, ()),
    ),
    fontWeight(Styles.getFontWeight(weight_)),
    ...bgStyles,
  ];
};

[@react.component]
let make =
    (
      ~weight=`normal,
      ~size=0,
      ~tag="span",
      ~lineHeight=0,
      ~textDecoration=?,
      ~quiet=false,
      ~tintColor=?,
      ~style=?,
      ~children: React.element,
      (),
    ) => {
  let styles =
    getTextStyles(
      ~size,
      ~quiet,
      ~lineHeight,
      ~textDecoration?,
      ~weight,
      ~tintColor?,
      (),
    );
  UnsafeCreateReactElement.create(
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
        ~quiet=false,
        ~style=?,
        ~lineHeight=0,
        ~textDecoration=?,
        ~tintColor=?,
        ~children,
        (),
      ) => {
    let styles =
      getTextStyles(
        ~size,
        ~quiet,
        ~lineHeight,
        ~textDecoration?,
        ~weight,
        ~tintColor?,
        (),
      );
    UnsafeCreateReactElement.create(
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
        ~margin as m=?,
        ~padding as p=?,
        ~quiet=false,
        ~size=0,
        ~lineHeight=0,
        ~textDecoration=?,
        ~style=?,
        ~tintColor=?,
        ~backgroundColor=?,
        ~children,
        (),
      ) => {
    let styles =
      getTextStyles(
        ~size,
        ~quiet,
        ~lineHeight,
        ~weight,
        ~textDecoration?,
        ~tintColor?,
        ~backgroundColor?,
        (),
      );
    let margin = Styles.getMargin(m);
    let padding = Styles.getPadding(p);
    UnsafeCreateReactElement.create(
      tag,
      {
        "className": {
          (
            switch (style) {
            | Some(p) => [styles, margin, padding, p]
            | None => [styles, margin, padding]
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
        ~margin=`margin4((`noSpace, `noSpace, `noSpace, `double)),
        ~size=0,
        ~quiet=false,
        ~lineHeight=0,
        ~textDecoration=?,
        ~style=?,
        ~tintColor=?,
        ~children,
        (),
      ) => {
    let styles =
      getTextStyles(
        ~size,
        ~lineHeight,
        ~textDecoration?,
        ~weight,
        ~quiet,
        ~tintColor?,
        (),
      );
    let margin = Styles.getMargin(Some(margin));
    UnsafeCreateReactElement.create(
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
        ~margin as m=`margin2((`noSpace, `double)),
        ~size=0,
        ~quiet=false,
        ~style=?,
        ~lineHeight=0,
        ~textDecoration=?,
        ~tintColor=?,
        ~children,
        (),
      ) => {
    let styles =
      getTextStyles(
        ~size,
        ~lineHeight,
        ~weight,
        ~quiet,
        ~textDecoration?,
        ~tintColor?,
        ~fontFamily=`mono,
        (),
      );
    let margin = Styles.getMargin(Some(`margin(`noSpace)));
    let padding = Styles.getPadding(Some(`padding(`double)));
    <Box
      margin=m
      backgroundColor={`highlight((7, `body))}
      borderRadius={Css.px(6)}
      style=Css.[width(pct(100.)), overflow(`scroll)]>
      {UnsafeCreateReactElement.create(
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