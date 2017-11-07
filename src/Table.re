let formatTime = (s) => String.sub(s, 11, 5);

let component = ReasonReact.statelessComponent("Table");

let make = (~announcements, _children) => {
  ...component,
  render: (_self) =>
    <table>
      <tbody>
        (
          ReasonReact.arrayToElement(
            Array.map(
              (announcement: Backend.announcement) =>
                <tr key=announcement.id>
                  <td> (ReasonReact.stringToElement(announcement.id)) </td>
                  <td> (ReasonReact.stringToElement(formatTime(announcement.time))) </td>
                  <td> (ReasonReact.stringToElement(announcement.destination)) </td>
                  <td>
                    (
                      switch announcement.actual {
                      | Some(s) => <b> (ReasonReact.stringToElement(formatTime(s))) </b>
                      | None =>
                        switch announcement.estimated {
                        | Some(s) => <i> (ReasonReact.stringToElement(formatTime(s))) </i>
                        | None => ReasonReact.stringToElement("-")
                        }
                      }
                    )
                  </td>
                </tr>,
              announcements
            )
          )
        )
      </tbody>
    </table>
};
