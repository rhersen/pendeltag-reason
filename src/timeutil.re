let diffInMinutes = (t, s) => {
  let diffInSeconds = (t, s) => Timediff.diffHms(Timediff.parse(t), Timediff.parse(s));
  diffInSeconds(t, s) / 60
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
  announcement |> time |> Timediff.parse |> Timediff.diffHms(now) |> secondsToString
};
