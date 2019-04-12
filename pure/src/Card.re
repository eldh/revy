[@bs.send] external blur: Js.t({..}) => unit = "blur";

  [@react.component]
  let make = (~children, ()) => {
      <button
        className=Css.(
          style([
            borderWidth(px(0)),
            cursor(`pointer),
            fontWeight(`bold),
            focus([
              outlineStyle(`none),
              backgroundColor(rgb(20, 150, 70)),
            ]),
            active([backgroundColor(rgb(200, 200, 200))]),
          ])
        )>
        children
      </button>
    ;
  };