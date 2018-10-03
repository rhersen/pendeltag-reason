let parse = (t) => {
  let hmsTuple = (hms) =>
    switch hms {
    | [Some(h1), Some(m1), Some(s1)] => (h1, m1, s1)
    | _ => (0, 0, 0)
    };
  let parseInt = (capture) =>
    switch (Js.Nullable.to_opt(capture)) {
    | Some(capture) => Some(int_of_string(capture))
    | None => None
    };
  switch (Js.Re.exec(t, [%re "/T(\\d\\d):(\\d\\d):(\\d\\d)/"])) {
  | None => (0, 0, 0)
  | Some(result) =>
    let captures = Js.Re.captures(result);
    [1, 2, 3] |> List.map((i) => parseInt(captures[i])) |> hmsTuple
  }
};

let diffHms = ((h0, m0, s0), (h1, m1, s1)) => {
  let hours = 3600;
  let d = (h1 - h0) * 60 * 60 + (m1 - m0) * 60 + s1 - s0;
  d < (-12) * hours ? d + 24 * hours : d
};
