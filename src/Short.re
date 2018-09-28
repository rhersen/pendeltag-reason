let el = ReasonReact.stringToElement;

let s = (announcement: Backend.announcement) =>
  Array.fold_left(
    (r, s) =>
      if (String.length(s) >= 4 && String.compare(String.sub(s, 0, 4), "Kort") == 0) {
        r ++ "K"
      } else if (String.length(s) > 0) {
        r ++ "*"
      } else {
        r
      },
    "",
    announcement.deviation
  );

let component = ReasonReact.statelessComponent("Short");

let make = (~announcement: Backend.announcement, _children) => {
  ...component,
  render: (_self) => <td className="short"> (el(s(announcement))) </td>
};
