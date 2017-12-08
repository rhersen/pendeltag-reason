let el = ReasonReact.stringToElement;

let component = ReasonReact.statelessComponent("Countdown");

let make = (~announcement, ~now, _children) => {
  ...component,
  render: (_self) => <td className="countdown"> (el(Timediff.format(announcement, now))) </td>
};