open Revy.UI;

module Checkbox = {
  open Revy.Core;
  let useInputStyles = () => {
    Css.[
      position(`absolute),
      cursor(`pointer),
      height(px(0)),
      width(px(0)),
      opacity(0.),
      // margin2(~v=Styles.useSpace(`single), ~h=Styles.useSpace(`single)),
      selector(
        "& ~ div",
        [
          position(`relative),
          height(pct(100.)),
          // margin(Styles.useSpace(~borderAdjust=10, `number(3))),
          // height(Css.Calc.(+)(Styles.useSpace(`double), px(20))),
          // margin(px(0)),
          marginLeft(px(0)),
          marginRight(Styles.useSpace(`half)),
          borderWidth(px(1)),
          borderStyle(`solid),
          borderColor(Styles.useColor(~highlight=10, `primary)),
          backgroundColor(Styles.useColor(`primary)),
          borderRadius(px(5)),
          width(px(20)),
          height(px(20)),
          after([
            contentRule(""),
            display(`block),
            position(`relative),
            top(px(2)),
            left(px(6)),
            width(px(5)),
            height(px(10)),
            borderTopWidth(px(0)),
            borderRightWidth(px(3)),
            borderBottomWidth(px(3)),
            borderLeftWidth(px(0)),
            transforms([rotate(deg(45)), scale(0.3, 0.3)]),
            transition(~duration=200, "all"),
            borderStyle(`solid),
            borderColor(transparent),
          ]),
        ],
      ),
      checked([
        selector(
          "& ~ div",
          [
            after([
              borderColor(Styles.useColor(`bodyBackground)),
              transforms([rotate(deg(45)), scale(1., 1.)]),
            ]),
          ],
        ),
      ]),
      disabled([
        selector("& ~ *", [opacity(0.5)]),
        selector("& ~ div", [borderColor(rgba(0, 0, 0, 0.5))]),
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
            | None => useInputStyles()
            | Some(v) => [useInputStyles(), v] |> List.concat
            }
          )
          |> Css.style
        }
        type_="checkbox"
      />
      <div />
      <Text.String color=`quietText> label </Text.String>
    </TouchableOpacity>;
  };
};

[@react.component]
let make = () => {
  let (bar, setBar) = React.useState(() => true);
  let (foo, setFoo) = React.useState(() => false);
  let (baz, setBaz) = React.useState(() => false);
  <ComponentsCard title="Checkbox">
    <Box
      direction=`column m={`margin4((`noSpace, `noSpace, `single, `single))}>
      <Checkbox
        value="bar"
        name="bar"
        label="Bar"
        id="bar"
        checked=bar
        onChange={_ => setBar(v => !v)}
      />
      <Checkbox
        value="foo"
        name="bar"
        label="Foo"
        id="foo"
        checked=foo
        onChange={_ => setFoo(v => !v)}
      />
      <Checkbox
        value="baz"
        name="bar"
        disabled=true
        label="Baz"
        id="baz"
        checked=baz
        onChange={_ => setBaz(v => !v)}
      />
    </Box>
  </ComponentsCard>;
};