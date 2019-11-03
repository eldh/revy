open Core;
let useInputStyles = () => {
  Css.[
    position(`absolute),
    cursor(`pointer),
    height(px(0)),
    width(px(0)),
    opacity(0.),
    selector(
      "& ~ div",
      [
        borderColor(Styles.getColor(`primary)),
        borderRadius(px(4)),
        borderStyle(`solid),
        borderWidth(px(1)),
        height(pct(100.)),
        height(px(16)),
        marginLeft(px(0)),
        marginRight(Styles.getSpace(`half)),
        position(`relative),
        transition(~duration=200, "all"),
        width(px(16)),
        after([
          contentRule(""),
          borderLeftWidth(px(0)),
          borderColor(`transparent),
          borderTopWidth(px(0)),
          borderRightWidth(px(2)),
          borderBottomWidth(px(2)),
          borderStyle(`solid),
          display(`block),
          height(px(8)),
          left(px(5)),
          position(`relative),
          top(px(2)),
          transforms([rotate(deg(45.)), scale(1., 1.)]),
          transition(~duration=200, "all"),
          width(px(4)),
        ]),
      ],
    ),
    checked([
      selector(
        "& ~ div",
        [after([borderColor(Styles.getTextColor(~tint=`primary, ()))])],
      ),
    ]),
    disabled([selector("& ~ *", [opacity(0.5)])]),
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
      ~onFocus=?,
      ~onBlur=?,
      ~checked,
      ~value,
      ~name="",
      (),
    ) => {
  <TouchableOpacity
    direction=`row
    tag="label"
    align=`center
    style=Css.[cursor(`pointer), height(Styles.getSpace(`closest(21)))]
    onPress={disabled ? ignore : onChange |> Obj.magic}
    domProps={"htmlFor": id}>
    <input
      checked
      value
      name
      id
      disabled
      onChange
      ?onFocus
      ?onBlur
      label
      className={
        (
          switch (styles) {
          | None => useInputStyles()
          | Some(v) => [useInputStyles(), v] |> List.concat
          }
        )
        |> Css.style
      }
      type_="checkbox"
    />
    <View />
    <Text.String> label </Text.String>
  </TouchableOpacity>;
};