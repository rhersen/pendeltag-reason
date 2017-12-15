let component = ReasonReact.statelessComponent("Table");

let make = (~announcements, ~now, _children) => {
  ...component,
  render: (_self) => {
    let direction = (id) =>
      Js.Re.test(id, [%re "/\\d\\d\\d[24680]/"]) ? "northbound" : "southbound";
    let tr = (announcement: Backend.announcement) =>
      <tr key=announcement.id className=(direction(announcement.id))>
        <TrainId announcement />
        <Short announcement />
        <Destination announcement />
        <AdvertisedTime announcement />
        <Time announcement />
        <Delay announcement />
        <Countdown announcement now />
        <Deviation announcement />
      </tr>;
    <table>
      <tbody> (announcements |> Array.map(tr) |> ReasonReact.arrayToElement) </tbody>
    </table>
  }
};