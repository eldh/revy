let theme =
  Theme.make(
    ~fontScale=1.25,
    ~baseFontSize=14,
    ~baseGridUnit=5,
    ~fonts={
      body: ["-apple-system", "BlinkMacSystemFont", "sans-serif"],
      title: ["-apple-system", "BlinkMacSystemFont", "sans-serif"],
      mono: ["monospace"],
      alt: ["-apple-system", "BlinkMacSystemFont", "sans-serif"],
    },
    ~colors=
      Css.{
        primary: Css.rgb(110, 181, 247),
        primaryText:
          Lab.(fromRGB((110, 181, 247, 1.)) |> highlight(70) |> toCssRGB),
        secondary: Css.rgb(50, 40, 30),
        secondaryText:
          Lab.(fromRGB((50, 40, 30, 1.)) |> highlight(90) |> toCssRGB),
        warning: Css.rgb(235, 180, 71),
        warningText:
          Lab.(fromRGB((235, 180, 71, 1.)) |> lighten(-90) |> toCssRGB),
        success: Css.rgb(88, 214, 21),
        successText:
          Lab.(fromRGB((88, 214, 21, 1.)) |> lighten(-90) |> toCssRGB),
        error: rgb(240, 35, 35),
        errorText:
          Lab.(fromRGB((240, 35, 35, 1.)) |> lighten(-90) |> toCssRGB),
        bodyBackground: rgb(255, 255, 255),
        bodyText: rgb(0, 0, 0),
        quietText: rgb(50, 50, 50),
      },
    (),
  );