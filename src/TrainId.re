let component = ReasonReact.statelessComponent("TrainId");

let make = (~announcement: Backend.announcement, _children) => {
  ...component,
  render: (_self) =>
    <td className="id">
      (ReasonReact.stringToElement(Backend.name(announcement.id)))
    </td>
};