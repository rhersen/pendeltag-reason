let formatTime = (s) => String.sub(s, 11, 5);

let component = ReasonReact.statelessComponent("Table");

let make = (~announcements, ~now, _children) => {
  ...component,
  render: (_self) =>
    <table>
      <tbody>
        (
          ReasonReact.arrayToElement(
            Array.map(
              (announcement: Backend.announcement) =>
                <tr key=announcement.id>
                  <td> (ReasonReact.stringToElement(formatTime(announcement.time))) </td>
                  <td> (ReasonReact.stringToElement(Backend.name(announcement.destination))) </td>
                  <Time announcement />
                  <Countdown announcement now />
                </tr>,
              announcements
            )
          )
        )
      </tbody>
    </table>
};