let el = ReasonReact.stringToElement;

let s = (announcement: Backend.announcement) => {
  Js.log("fold_left");
  Array.fold_left(
    (s1, s2) => {
      Js.log(s2);
      Js.log(String.sub(s2, 0, 4));
      Js.log(String.compare(String.sub(s2, 0, 4), "Kort"));
      String.compare(String.sub(s2, 0, 4), "Kort") == 0 ? "K" : s1
    },
    "",
    announcement.deviation
  )
};

let component = ReasonReact.statelessComponent("Short");

let make = (~announcement: Backend.announcement, _children) => {
  ...component,
  render: (_self) => <td className="short"> (el(s(announcement))) </td>
};