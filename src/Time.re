let component = ReasonReact.statelessComponent("Time");

let make = (~announcement: Backend.announcement, _children) => {
  ...component,
  render: (_self) => {
    let formatTime = (s) => String.sub(s, 11, 5);
    <td className="time">
      (
        switch announcement.actual {
        | Some(s) => <b> (ReasonReact.stringToElement(formatTime(s))) </b>
        | None =>
          switch announcement.estimated {
          | Some(s) => <i> (ReasonReact.stringToElement(formatTime(s))) </i>
          | None => ReasonReact.stringToElement(formatTime(announcement.time))
          }
        }
      )
    </td>
  }
};