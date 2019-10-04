open Core;
let useRadiobuttonStyles = () => {
  Css.[
    position(`absolute),
    cursor(`pointer),
    height(px(0)),
    width(px(0)),
    opacity(0.),
    selector(
      "& ~ div",
      [
        position(`relative),
        height(pct(100.)),
        marginLeft(px(0)),
        marginRight(Styles.useSpace(`half)),
        after([
          contentRule(""),
          boxSizing(`borderBox),
          display(`block),
          position(`relative),
          top(Calc.(-)(pct(50.), px(10))),
          left(px(0)),
          backgroundColor(`transparent),
          width(px(20)),
          height(px(20)),
          borderRadius(pct(50.)),
          transition(~duration=200, "all"),
          borderWidth(px(1)),
          borderStyle(`solid),
          borderColor(Styles.useColor(~highlight=10, `primary)),
          boxShadow(~inset=true, ~spread=px(0), Styles.useColor(`primary)),
        ]),
      ],
    ),
    checked([
      selector(
        "& ~ div",
        [
          after([
            backgroundColor(`transparent),
            boxShadow(
              ~inset=true,
              ~spread=px(6),
              Styles.useColor(`primary),
            ),
          ]),
        ],
      ),
    ]),
    disabled([
      selector("& ~ *", [opacity(0.5)]),
      selector("& ~ div", [borderColor(Styles.useColor(~alpha=0.5, `bodyText))]),
    ]),
  ];
};

[@react.component]
let make =
    (
      ~onChange,
      ~label,
      ~id="",
      ~disabled=false,
      ~styles=?,
      ~onFocus=ignore,
      ~onBlur=ignore,
      ~checked,
      ~value,
      ~name="",
      (),
    ) => {
  <TouchableOpacity
    direction=`row
    tag="label"
    align=`center
    style=Css.[cursor(`pointer), height(Styles.useSpace(`closest(21)))]
    onPress={disabled ? ignore : onChange |> Obj.magic}
    domProps={"htmlFor": id}>
    <input
      checked
      value
      name
      id
      disabled
      onChange
      onFocus
      onBlur
      label
      className={
        (
          switch (styles) {
          | None => useRadiobuttonStyles()
          | Some(v) => [useRadiobuttonStyles(), v] |> List.concat
          }
        )
        |> Css.style
      }
      type_="radio"
    />
    <div />
    <Text.String> label </Text.String>
  </TouchableOpacity>;
};