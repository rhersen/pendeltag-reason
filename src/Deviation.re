let el = ReasonReact.stringToElement;

let s = (announcement: Backend.announcement) =>
  switch (Array.to_list(announcement.deviation)) {
  | [] => "inga"
  | [one] => one
  | _ => "*"
  };

let component = ReasonReact.statelessComponent("Deviation");

let make = (~announcement: Backend.announcement, _children) => {
  ...component,
  render: (_self) => <td className="deviation"> (el(s(announcement))) </td>
};