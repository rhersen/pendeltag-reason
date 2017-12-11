let el = ReasonReact.stringToElement;

let component = ReasonReact.statelessComponent("TrainId");

let make = (~announcement: Backend.announcement, _children) => {
  ...component,
  render: (_self) => <td className="id"> (el(announcement.id)) </td>
};