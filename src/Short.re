let el = ReasonReact.stringToElement;

let s = (announcement: Backend.announcement) =>
  Array.fold_left(
    (s1, s2) =>
      if (String.length(s2) >= 4 && String.compare(String.sub(s2, 0, 4), "Kort") == 0) {
        "K"
      } else if (String.length(s2) > 0) {
        "*"
      } else {
        s1
      },
    "",
    announcement.deviation
  );

let component = ReasonReact.statelessComponent("Short");

let make = (~announcement: Backend.announcement, _children) => {
  ...component,
  render: (_self) => <td className="short"> (el(s(announcement))) </td>
};
