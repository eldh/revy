[@bs.config {jsx: 3}];

[@react.component __MODULE__]
let make = () =>
  <ThemeContext.Provider value=InvertedTheme.theme>
    <Box direction=`row wrap=`nowrap>
      <>
        <Sidebar />
        <Box alignContent=`center> <> <Test /> <DefaultView /> </> </Box>
      </>
    </Box>
  </ThemeContext.Provider>;