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

let format = (d) =>
  if (d <= (-100)) {
    ""
  } else if (d < 100) {
    string_of_int(d) ++ "s"
  } else if (d < 600) {
    string_of_int(d / 60) ++ ":" ++ pad(d mod 60)
  } else {
    string_of_int(d / 60) ++ "min"
  };

let formatDiff = (now, time) =>
  switch time {
  | [h, m, s] =>
    let (hour, minute, second) = now;
    let d = (h - hour) * 60 * 60 + (m - minute) * 60 + s - second;
    format(d < (-12) * hours ? d + 24 * hours : d)
  | _ => "wrong length"
  };

let match = (capture) =>
  switch (Js.Nullable.to_opt(capture)) {
  | Some(capture) => int_of_string(capture)
  | None => 0
  };

let format = (announcement: Backend.announcement, now) =>
  switch (Js.Re.exec(time(announcement), [%re "/T(\\d\\d):(\\d\\d):(\\d\\d)/"])) {
  | None => time(announcement)
  | Some(result) =>
    let captures = Js.Re.captures(result);
    [1, 2, 3] |> List.map((i) => captures[i]) |> List.map(match) |> formatDiff(now)
  };