let defaultStyles = Css.[display(`flex), boxSizing(`borderBox)];

[@react.component]
let make =
    (
      ~tag="div",
      ~onPress=?,
      ~onMouseOver=?,
      ~onMouseOut=?,
      ~a11yTitle as _a11yTitle=?,
      ~style=[],
      ~domProps=None,
      ~children=?,
      (),
    ) => {
  let props = {
    "children": children,
    "onClick": onPress,
    "onMouseOver": onMouseOver,
    "onMouseOut": onMouseOut,
    "className": [style, defaultStyles] |> List.concat |> Css.style,
  };

  UnsafeCreateReactElement.create(
    tag,
    switch (domProps) {
    | Some(p) => Js.Obj.assign(p, props)
    | None => props
    },
  );
};