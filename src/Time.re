let el = ReasonReact.stringToElement;

let component = ReasonReact.statelessComponent("Time");

let make = (~announcement: Backend.announcement, _children) => {
  ...component,
  render: (_self) => {
    let formatTime = (s) => String.sub(s, 11, 5);
    <td className="time">
      (
        switch announcement.actual {
        | Some(s) => <b> (el(formatTime(s))) </b>
        | None =>
          switch announcement.estimated {
          | Some(s) => <i> (el(formatTime(s))) </i>
          | None => el(formatTime(announcement.time))
          }
        }
      )
    </td>
  }
};