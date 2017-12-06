let component = ReasonReact.statelessComponent("Destination");

let make = (~announcement: Backend.announcement, _children) => {
  ...component,
  render: (_self) =>
    <td className="destination">
      (ReasonReact.stringToElement(Backend.name(announcement.destination)))
    </td>
};