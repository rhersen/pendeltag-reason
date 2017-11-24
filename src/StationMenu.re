let component = ReasonReact.statelessComponent("StationMenu");

let nw = (station: Backend.station) =>
  station.north > 59.35 && station.north < 59.58 && station.east < 17.898;

let ne = (station: Backend.station) =>
  station.north > 59.37 && station.north < 59.58 && station.east > 17.898;

let ncw = (station: Backend.station) =>
  station.north > 59.35 && station.north < 59.37 && station.east < 18.;

let nce = (station: Backend.station) =>
  station.north > 59.35 && station.north < 59.37 && station.east > 18.;

let nc = (station: Backend.station) => station.north > 59.34 && station.north < 59.35;

let c = (station: Backend.station) => station.north > 59.28 && station.north < 59.34;

let sc = (station: Backend.station) => station.north > 59.26 && station.north < 59.28;

let scw = (station: Backend.station) =>
  station.north > 59.236 && station.north < 59.26 && station.east < 18.;

let sce = (station: Backend.station) =>
  station.north > 59.236 && station.north < 59.26 && station.east > 18.;

let sw = (station: Backend.station) =>
  station.north > 59.08 && station.north < 59.236 && station.east > 17.63 && station.east < 17.98;

let se = (station: Backend.station) =>
  station.north > 59.08 && station.north < 59.236 && station.east > 17.98;

let make = (~stations, ~onClick, _children) => {
  ...component,
  render: (_self) =>
    <div id="navs">
      <StationBranch stations onClick inside=nw />
      <StationBranch stations onClick inside=ne className="pull-right" />
      <StationBranch stations onClick inside=ncw className="pull-left narrow" />
      <StationBranch stations onClick inside=nc className="center" />
      <StationBranch stations onClick inside=nce className="pull-right narrow" />
      <StationBranch stations onClick inside=c className="center wide" />
      <StationBranch stations onClick inside=scw className="pull-left narrow" />
      <StationBranch stations onClick inside=sc className="center narrow" />
      <StationBranch stations onClick inside=sce className="pull-right narrow" />
      <StationBranch stations onClick inside=sw />
      <StationBranch stations onClick inside=se className="pull-right" />
    </div>
};