let time = (announcement: Backend.announcement) =>
  switch announcement.estimated {
  | None =>
    switch announcement.actual {
    | None => announcement.time
    | Some(s) => s
    }
  | Some(s) => s
  };

let formatCountdown = (announcement: Backend.announcement, now) => {
  let (hour, minute, second) = now;
  switch (Js.Re.exec(time(announcement), [%re "/T(\\d\\d):(\\d\\d):(\\d\\d)/"])) {
  | None => string_of_int(0)
  | Some(result) =>
    let captures = Js.Re.captures(result);
    let match = (i) =>
      switch (Js.Nullable.to_opt(captures[i])) {
      | Some(capture) => int_of_string(capture)
      | None => 0
      };
    string_of_int(match(3) - second + (match(2) - minute) * 60 + (match(1) - hour) * 60 * 60)
  }
};

let component = ReasonReact.statelessComponent("Countdown");

let make = (~announcement, ~now, _children) => {
  ...component,
  render: (_self) =>
    <td className="countdown">
      (ReasonReact.stringToElement(formatCountdown(announcement, now)))
    </td>
};