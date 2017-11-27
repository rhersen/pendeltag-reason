let formatTime = (s) => String.sub(s, 11, 5);

let component = ReasonReact.statelessComponent("Table");

let direction = (id) => {
  let t = Js.Re.test(id, [%re "/\\d\\d\\d\\d[24680]/"]);
  if (t) {"northbound"} else {"southbound"}
};

let make = (~announcements, ~now, _children) => {
  ...component,
  render: (_self) =>
    <table>
      <tbody>
        (
          ReasonReact.arrayToElement(
            Array.map(
              (announcement: Backend.announcement) =>
                <tr key=announcement.id className=(direction(announcement.id))>
                  <td className="id"> (ReasonReact.stringToElement(announcement.id)) </td>
                  <td className="destination">
                    (ReasonReact.stringToElement(Backend.name(announcement.destination)))
                  </td>
                  <AdvertisedTime announcement />
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