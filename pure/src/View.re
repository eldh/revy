let defaultStyles = Css.[display(`flex), boxSizing(`borderBox)];

[@react.component __MODULE__]
let make =
    (
      ~tag="div",
      ~onPress=None,
      ~a11yTitle as _a11yTitle=?,
      ~style=[],
      ~domProps=Js.Obj.empty(),
      ~children=?,
      (),
    ) => {
  let props =
    Js.Obj.assign(
      domProps,
      {
        "children": children,
        "onClick":onPress,
        "className": [style, defaultStyles]->List.concat->Css.style,
      },
    );
  EscapeHatch.use(tag, props);
};