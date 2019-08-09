# Revy

Revy is a set of tools for creating design systems for ReasonReact. It builds on the Atomic Design principles and provides building blocks from sub-atomic to molecule level.

## From quarks to organisms

The smallest building blocks of a design system, the sub-atomic particles, help us define colors, spacings, typography etc.

### Themes

Revy is built around themes. You define a small set of values, which are used by Revy to generate a complete theme with everything you need for building your design system - colors, font sizes, spacings, etc. This makes it easy to white-label your app and to support dark mode.

### Colors

Revy includes a lean but powerful color manipulation library, built around the [LAB color space](https://en.wikipedia.org/wiki/CIELAB_color_space). LAB has a few advantages compared to [sRGB](https://en.wikipedia.org/wiki/SRGB), which is commonly used on the web. First, it's designed for human vision, so that mixing colors work in a uniform way. This means it's easy to get lighter and darker shades, to get inverted colors etc in a way that provides visually pleasing results. Second, it's a much larger color space than sRGB, so it can express colors that are usually not available on the web. This is becoming more important as browsers and displays are starting to support wider color gamut.

### Spacings

Revy themes define a base grid unit, which is then used to calculate spacings. This makes it easy to maintain a consistent vertical rythm across all types of elements. Revy also includes responsive layout helpers for easy mobile-first design.

### Typography

Fonts, weights and sizes are built into Revy's type mangaement. By using a [type scale](https://type-scale.com), Revy ensures your design system has balanced and hamronious font sizes. Combined with the base grid unit, Revy also sets line heights that fit neatly in the vertical grid. Aditionally, Revy automatically selects accessible text colors for all text, making it easier to re-use text components in different parts of the app.

### Animations

TBD, something something spring physics... (react-spring)

### Components

Revy UI is a set of basic components that most applications will need, like layout, form fields, buttons, text components, etc. Think of it as a lightweight alternative to Bootstrap, Material UI et al.

## Creating your universe

Using the base Revy components (`View`, `TouchableOpacity`, `Text`, etc), you can build whatever you need for your application. Revy has sane defualts for most use cases, but there are also escape hatches for the cases where you need to do something custom, like a color that's not in the design system, a one-off spacing or a custom font weight.

## Bring meaning to the world
