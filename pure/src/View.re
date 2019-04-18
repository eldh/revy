let defaultStyles = Css.[display(`flex), boxSizing(`borderBox)];

[@react.component]
let make =
    (
      ~tag="div",
      ~onPress=None,
      ~a11yTitle as _a11yTitle=?,
      ~style=[],
      ~domProps=None,
      ~children=?,
      (),
    ) => {
  let props = {
    "children": children,
    "onClick": onPress,
    "className": [style, defaultStyles] |> List.concat |> Css.style,
  };

  EscapeHatch.use(
    tag,
    switch (domProps) {
    | Some(p) => Js.Obj.assign(p, props)
    | None => props
    },
  );
};