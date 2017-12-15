let el = ReasonReact.stringToElement;

let component = ReasonReact.statelessComponent("AdvertisedTime");

let make = (~announcement: Backend.announcement, _children) => {
  ...component,
  render: (_self) => {
    let formatTime = (s) => String.sub(s, 11, 5);
    <td className="advertised">
      (
        switch announcement.actual {
        | Some(_) => el(formatTime(announcement.time))
        | None =>
          switch announcement.estimated {
          | Some(_) => el(formatTime(announcement.time))
          | None => ReasonReact.nullElement
          }
        }
      )
    </td>
  }
};