let el = ReasonReact.stringToElement;

let component = ReasonReact.statelessComponent("Deviation");

let make = (~announcement: Backend.announcement, _children) => {
  ...component,
  render: (_self) => <td className="deviation"> (el(announcement.deviation)) </td>
};