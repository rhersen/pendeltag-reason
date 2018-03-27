let el = ReasonReact.stringToElement;

let s = (announcement: Backend.announcement) =>
  Array.fold_left(
    (s1, s2) => s1 ++ (String.length(s2) >= 6 && String.sub(s2, 0, 6) == "Kort t" ? "" : s2),
    "",
    announcement.deviation
  );

let component = ReasonReact.statelessComponent("Deviation");

let make = (~announcement: Backend.announcement, _children) => {
  ...component,
  render: (_self) => <td className="deviation"> (el(s(announcement))) </td>
};
