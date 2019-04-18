let s = React.string;
let i = a => a|>string_of_int|>React.string;
let a = React.array;
let l = a => a|>Belt_List.toArray|>React.array;