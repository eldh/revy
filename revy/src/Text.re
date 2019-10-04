open Core;
exception InvalidValue(string);

let useTextStyles =
    (
      ~size,
      ~quiet=false,
      ~tintColor as tint=?,
      ~backgroundColor as bg_=?,
      ~fontFamily as fontFamily_=`body,
      ~lineHeight as lineHeight_,
      ~weight as weight_,
      (),
    ) => {
  let sizeVal = Styles.useFontSize(size);
  let bgStyles =
    switch (bg_) {
    | Some(p) => Css.[background(Styles.useColor(p))]
    | None => []
    };
  Css.[
    color(
      Styles.useTextColor(
        ~highlight=?quiet ? Some(-30) : None,
        ~tint?,
        ~background=?bg_,
        (),
      ),
    ),
    overflowY(`visible),
    fontSize(sizeVal),
    fontFamily(Styles.useFontFamily(fontFamily_)),
    lineHeight(
      Styles.useLineHeight(~fontSize=sizeVal, ~extraHeight=lineHeight_, ()),
    ),
    fontWeight(Styles.useFontWeight(weight_)),
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
      ~quiet=false,
      ~tintColor=?,
      ~style=?,
      ~children: React.element,
      (),
    ) => {
  let styles =
    useTextStyles(~size, ~quiet, ~lineHeight, ~weight, ~tintColor?, ());
  UnsafeCreateReactElement.use(
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
        ~tintColor=?,
        ~children,
        (),
      ) => {
    let styles =
      useTextStyles(~size, ~quiet, ~lineHeight, ~weight, ~tintColor?, ());
    UnsafeCreateReactElement.use(
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
        ~style=?,
        ~tintColor=?,
        ~backgroundColor=?,
        ~children,
        (),
      ) => {
    let styles =
      useTextStyles(
        ~size,
        ~quiet,
        ~lineHeight,
        ~weight,
        ~tintColor?,
        ~backgroundColor?,
        (),
      );
    let margin = Styles.useMargin(m);
    let padding = Styles.usePadding(p);
    UnsafeCreateReactElement.use(
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
        ~style=?,
        ~tintColor=?,
        ~children,
        (),
      ) => {
    let styles =
      useTextStyles(~size, ~lineHeight, ~weight, ~quiet, ~tintColor?, ());
    let margin = Styles.useMargin(Some(margin));
    UnsafeCreateReactElement.use(
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
        ~tintColor=?,
        ~children,
        (),
      ) => {
    let styles =
      useTextStyles(
        ~size,
        ~lineHeight,
        ~weight,
        ~quiet,
        ~tintColor?,
        ~fontFamily=`mono,
        (),
      );
    let margin = Styles.useMargin(Some(`margin(`noSpace)));
    let padding = Styles.usePadding(Some(`padding(`double)));
    <Box
      margin=m
      backgroundColor={`highlight((7, `body))}
      borderRadius={Css.px(6)}
      style=Css.[width(pct(100.)), overflow(`scroll)]>
      {UnsafeCreateReactElement.use(
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