let component = ReasonReact.statelessComponent("StationMenu");

let make = (~stations, ~setAnnouncements, _children) => {
  ...component,
  render: (_self) =>
    ReasonReact.arrayToElement(
      Array.map(
        (station: Backend.station) =>
          <span
            key=station.signature
            onClick=((_) => Backend.getAnnouncements(setAnnouncements, station.signature))>
            (ReasonReact.stringToElement(station.name ++ " "))
          </span>,
        stations
      )
    )
};
