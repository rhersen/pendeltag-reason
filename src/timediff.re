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

let diffInSeconds = ((h0, m0, s0), (h1, m1, s1)) => {
  let hours = 3600;
  let d = (h1 - h0) * 60 * 60 + (m1 - m0) * 60 + s1 - s0;
  d < (-12) * hours ? d + 24 * hours : d
};

let format = (announcement: Backend.announcement, now) => {
  let time = (announcement: Backend.announcement) =>
    switch announcement.actual {
    | Some(s) => s
    | None =>
      switch announcement.estimated {
      | Some(s) => s
      | None => announcement.time
      }
    };
  let pad = (i) => i < 10 ? "0" ++ string_of_int(i) : string_of_int(i);
  let secondsToString = (d) =>
    if (d <= (-100)) {
      ""
    } else if (d < 100) {
      string_of_int(d) ++ "s"
    } else if (d < 600) {
      string_of_int(d / 60) ++ ":" ++ pad(d mod 60)
    } else {
      string_of_int(d / 60) ++ "min"
    };
  announcement |> time |> parse |> diffInSeconds(now) |> secondsToString
};