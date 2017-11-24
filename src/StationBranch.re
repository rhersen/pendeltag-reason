let component = ReasonReact.statelessComponent("StationBranch");

let make = (~stations, ~className="pull-left", ~inside, ~onClick, _children) => {
  ...component,
  render: (_self) =>
    <nav className>
      (
        ReasonReact.arrayToElement(
          Array.map(
            (station: Backend.station) =>
              if (inside(station)) {
                <div key=station.signature onClick=((_) => onClick(station.signature))>
                  (ReasonReact.stringToElement(station.name))
                </div>
              } else {
                ReasonReact.nullElement
              },
            stations
          )
        )
      )
    </nav>
};