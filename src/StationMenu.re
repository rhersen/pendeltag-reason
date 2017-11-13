let component = ReasonReact.statelessComponent("StationMenu");

let make = (~stations, ~onClick, _children) => {
  ...component,
  render: (_self) =>
    ReasonReact.arrayToElement(
      Array.map(
        (station: Backend.station) =>
          <span key=station.signature>
            <span onClick=((_) => onClick(station.signature))>
              (ReasonReact.stringToElement(station.name))
            </span>
            <span> (ReasonReact.stringToElement({js| · |js})) </span>
          </span>,
        stations
      )
    )
};
