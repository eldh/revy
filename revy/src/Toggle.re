open Core;
let useToggleStyles = () => {
  Css.[
    position(`absolute),
    cursor(`pointer),
    height(px(0)),
    width(px(0)),
    opacity(0.),
    selector(
      "& ~ div",
      [
        backgroundColor(Styles.useColor(`secondary)),
        borderColor(Styles.useColor(~highlight=10, `secondary)),
        borderRadius(px(25)),
        borderStyle(`solid),
        borderWidth(px(1)),
        height(px(24)),
        marginLeft(px(0)),
        marginRight(Styles.useSpace(`half)),
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
          backgroundColor(Styles.useColor(`body)),
          boxShadow(~y=px(1), ~blur=px(3), rgba(0, 0, 0, 0.3)),
        ]),
      ],
    ),
    checked([
      selector(
        "& ~ div",
        [
          backgroundColor(Styles.useColor(`primary)),
          borderColor(Styles.useColor(~highlight=10, `primary)),
          after([
            transform(translateX(px(14))),
            backgroundColor(Styles.useColor(`body)),
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
      ~m=`margin(`noSpace),
      ~checked,
      ~value,
      ~name="",
      (),
    ) => {
  <TouchableOpacity
    direction=`row
    tag="label"
    align=`center
    style=Css.[cursor(`pointer), height(Styles.useSpace(`closest(26)))]
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
          | None => useToggleStyles()
          | Some(v) => [useToggleStyles(), v] |> List.concat
          }
        )
        |> Css.style
      }
      type_="checkbox"
    />
    <div />
    <Text.String> label </Text.String>
  </TouchableOpacity>;
};