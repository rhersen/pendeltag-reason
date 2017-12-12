let el = ReasonReact.stringToElement;

let s = (announcement: Backend.announcement) =>
  Array.fold_left(
    (s1, s2) => String.sub(s2, 0, 6) == "Kort t" ? "K" : s1,
    "",
    announcement.deviation
  );

let component = ReasonReact.statelessComponent("Short");

let make = (~announcement: Backend.announcement, _children) => {
  ...component,
  render: (_self) => <td className="short"> (el(s(announcement))) </td>
};