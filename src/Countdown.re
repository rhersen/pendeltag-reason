let component = ReasonReact.statelessComponent("Countdown");

let make = (~announcement, ~now, _children) => {
  ...component,
  render: (_self) =>
    <td className="countdown">
      (ReasonReact.stringToElement(Timediff.format(announcement, now)))
    </td>
};