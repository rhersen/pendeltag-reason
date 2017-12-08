let diff = (t, s) =>
  switch (Timediff.diffInSeconds(Timediff.parse(t), Timediff.parse(s)) / 60) {
  | 0 => ReasonReact.stringToElement("i tid")
  | d => ReasonReact.stringToElement(string_of_int(d) ++ " min")
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
          | None => ReasonReact.stringToElement("")
          }
        }
      )
    </td>
};