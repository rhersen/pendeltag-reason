let el = ReasonReact.stringToElement;

let diff = (t, s) =>
  switch (Timeutil.diffInSeconds(t, s) / 60) {
  | 0 => el("i tid")
  | d => el(string_of_int(d) ++ " min")
  };

let component = ReasonReact.statelessComponent("Delay");

let make = (~announcement: Backend.announcement, _children) => {
  ...component,
  render: (_self) =>
    <td className="delay">
      (
        switch announcement.actual {
        | Some(s) => diff(announcement.time, s)
        | None =>
          switch announcement.estimated {
          | Some(s) => <i> (diff(announcement.time, s)) </i>
          | None => el("")
          }
        }
      )
    </td>
};
