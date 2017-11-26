let hours = 3600;

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

let secondsToString = (d: int) => {
  let minutes = float_of_int(d) /. 60.;
  Printf.sprintf("%.1f", minutes)
};

let diffInSeconds = (now, hms) =>
  switch hms {
  | [h, m, s] =>
    let (hour, minute, second) = now;
    let d = (h - hour) * 60 * 60 + (m - minute) * 60 + s - second;
    d < (-12) * hours ? d + 24 * hours : d
  | _ => 0
  };

let parseInt = (capture) =>
  switch (Js.Nullable.to_opt(capture)) {
  | Some(capture) => int_of_string(capture)
  | None => 0
  };

let format = (announcement: Backend.announcement, now) =>
  switch (Js.Re.exec(time(announcement), [%re "/T(\\d\\d):(\\d\\d):(\\d\\d)/"])) {
  | None => time(announcement)
  | Some(result) =>
    let captures = Js.Re.captures(result);
    [1, 2, 3]
    |> List.map((i) => captures[i])
    |> List.map(parseInt)
    |> diffInSeconds(now)
    |> secondsToString
  };