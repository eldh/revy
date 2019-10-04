let useInputStyles = (~margin as m=?, ()) => {
  Core.(
    [
      Css.[
        Css.padding2(
          ~v=Styles.useSpace(~borderAdjust=0, `single),
          ~h=Styles.useSpace(~borderAdjust=0, `single),
        ),
        textDecoration(`none),
        lineHeight(
          Styles.useLineHeight(~fontSize=Styles.useFontSize(0), ()),
        ),
        fontSize(Styles.useFontSize(0)),
        fontFamily(Styles.useFontFamily(`body)),
        boxSizing(`borderBox),
        borderRadius(Css.px(6)),
        borderWidth(px(0)),
        borderColor(Styles.useColor(`transparent)),
        borderStyle(`solid),
        backgroundColor(Styles.useColor(~alpha=0.07, `bodyText)),
        color(Styles.useTextColor()),
        // boxShadow(
        //   ~y=px(0),
        //   ~blur=px(0),
        //   ~spread=px(1),
        //   ~inset=true,
        //   Styles.useColor(~alpha=0.07, `bodyText),
        // ),
        focus([
          outlineStyle(`none),
          boxShadow(
            ~y=px(0),
            ~blur=px(0),
            ~spread=px(1),
            ~inset=true,
            Styles.useColor(`primary),
          ),
        ]),
        disabled([opacity(0.7)]),
      ],
      Styles.useMargin(m),
    ]
    |> List.concat
  );
};
module Input = {
  [@react.component]
  let make =
      (
        ~onChange,
        ~value,
        ~id=?,
        ~label=?,
        ~type_="text",
        ~disabled=?,
        ~style=?,
        ~onFocus=?,
        ~onBlur=?,
        ~onKeyDown=?,
        ~onKeyPress=?,
        ~onKeyUp=?,
        ~onClick=?,
        ~placeholder=?,
        ~margin=?,
        (),
      ) => {
    <input
      value
      onChange
      type_
      ?onKeyDown
      ?onKeyPress
      ?onKeyUp
      ?label
      ?disabled
      ?id
      ?placeholder
      ?onFocus
      ?onClick
      ?onBlur
      className={
        (
          switch (style) {
          | None => useInputStyles(~margin?, ())
          | Some(l) => [useInputStyles(~margin?, ()), l] |> List.concat
          }
        )
        |> Css.style
      }
    />;
  };
};

[@bs.get] external getForm: Dom.element => Dom.element = "form";
[@bs.send] external requestSubmitForm: Dom.element => unit = "requestSubmit";
[@bs.get] external getScrollHeight: Dom.element => int = "scrollHeight";
[@bs.send]
external setAttribute: (Dom.element, string, string) => unit = "setAttribute";
[@bs.send]
external dispatchEvent: (Dom.element, Dom.event) => unit = "dispatchEvent";
[@bs.new] external newEvent: string => Dom.event = "Event";

let submitForm = form => {
  form->dispatchEvent(newEvent("submit"));
};

module Textarea = {
  [@react.component]
  let make =
      (
        ~onChange as onChangeProp,
        ~value,
        ~id=?,
        ~label=?,
        ~disabled=?,
        ~style=?,
        ~onFocus=?,
        ~onBlur=?,
        ~onClick=?,
        ~onKeyDown=?,
        ~onKeyPress=?,
        ~onKeyUp=?,
        ~placeholder=?,
        ~margin=?,
        (),
      ) => {
    let domRef = React.useRef(Js.Nullable.null);
    let onChange = e => {
      // There's probably a more react-y way of doing this...
      let current = domRef |> React.Ref.current |> Js.Nullable.toOption;
      switch (current) {
      | Some(el) =>
        el->setAttribute("style", "height:auto");
        let h = getScrollHeight(el);
        el->setAttribute("style", "height:" ++ (h |> string_of_int) ++ "px");
      | None => ()
      };

      onChangeProp(e);
    };

    let onKeyDown = e => {
      let current = domRef |> React.Ref.current |> Js.Nullable.toOption;
      let key = ReactEvent.Keyboard.key(e);
      let cmd = ReactEvent.Keyboard.metaKey(e);
      if (key === "Enter" && cmd) {
        ReactEvent.Keyboard.preventDefault(e);
        ReactEvent.Keyboard.stopPropagation(e);
        switch (current) {
        | Some(el) => el |> getForm |> submitForm
        | None => ()
        };
      };
      switch (onKeyDown) {
      | Some(fn) => fn(e)
      | None => ()
      };
    };
    <textarea
      ref={ReactDOMRe.Ref.domRef(domRef)}
      value
      onChange
      onKeyDown
      ?onKeyPress
      ?onKeyUp
      ?label
      ?disabled
      ?id
      ?placeholder
      ?onFocus
      ?onClick
      ?onBlur
      className={
        [
          Css.[resize(`none), width(pct(100.))],
          switch (style) {
          | None => []
          | Some(l) => l
          },
          useInputStyles(~margin?, ()),
        ]
        |> List.concat
        |> Css.style
      }
    />;
  };
};
module Label = {
  [@react.component]
  let make = (~children, ~htmlFor=?, ()) => {
    <label
      ?htmlFor
      className={
        Text.useTextStyles(
          ~size=-1,
          ~quiet=true,
          ~lineHeight=1,
          ~weight=`normal,
          (),
        )
        |> Css.style
      }>
      children
    </label>;
  };
};