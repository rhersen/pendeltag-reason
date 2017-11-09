let component = ReasonReact.statelessComponent("StationMenu");

let make = (~stations, ~onClick, _children) => {
  ...component,
  render: (_self) =>
    ReasonReact.arrayToElement(
      Array.map(
        (station: Backend.station) =>
          <span>
            <span key=station.signature onClick=((_) => onClick(station.signature))>
              (ReasonReact.stringToElement(station.name))
            </span>
            <span> (ReasonReact.stringToElement({js| · |js})) </span>
          </span>,
        stations
      )
    )
};
