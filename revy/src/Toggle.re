open Core;
let getToggleStyles = () => {
  Css.[
    position(`absolute),
    cursor(`pointer),
    height(px(0)),
    width(px(0)),
    opacity(0.),
    selector(
      "& ~ div",
      [
        backgroundColor(Styles.getColor(`secondary)),
        borderColor(Styles.getColor(~highlight=10, `secondary)),
        borderRadius(px(25)),
        borderStyle(`solid),
        borderWidth(px(1)),
        height(px(24)),
        marginLeft(px(0)),
        marginRight(Styles.getSpace(`half)),
        position(`relative),
        transition(~duration=200, "all"),
        width(px(38)),
        after([
          contentRule(""),
          borderRadius(pct(50.)),
          display(`block),
          height(px(20)),
          width(px(20)),
          left(px(2)),
          top(px(2)),
          position(`relative),
          transition(~duration=200, "all"),
          backgroundColor(Styles.getColor(`body)),
          boxShadow(~y=px(1), ~blur=px(3), rgba(0, 0, 0, 0.3)),
        ]),
      ],
    ),
    checked([
      selector(
        "& ~ div",
        [
          backgroundColor(Styles.getColor(`primary)),
          borderColor(Styles.getColor(~highlight=10, `primary)),
          after([
            transform(translateX(px(14))),
            backgroundColor(Styles.getColor(`body)),
          ]),
        ],
      ),
    ]),
    disabled([
      selector("& ~ *", [opacity(0.5)]),
      selector("& ~ div", [borderColor(Styles.getColor(~alpha=0.5, `body))]),
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
    style=Css.[cursor(`pointer), height(Styles.getSpace(`closest(26)))]
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
          | None => getToggleStyles()
          | Some(v) => [getToggleStyles(), v] |> List.concat
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