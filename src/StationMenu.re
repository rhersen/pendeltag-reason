let component = ReasonReact.statelessComponent("StationMenu");

let make = (~stations, ~onClick, _children) => {
  ...component,
  render: (_self) =>
    <div id="navs">
      <StationBranch stations onClick inside=Areas.nw />
      <StationBranch stations onClick inside=Areas.ne className="pull-right" />
      <StationBranch stations onClick inside=Areas.ncw className="pull-left narrow" />
      <StationBranch stations onClick inside=Areas.nc className="center" />
      <StationBranch stations onClick inside=Areas.nce className="pull-right narrow" />
      <StationBranch stations onClick inside=Areas.c className="center wide" />
      <StationBranch stations onClick inside=Areas.scw className="pull-left narrow" />
      <StationBranch stations onClick inside=Areas.sc className="center narrow" />
      <StationBranch stations onClick inside=Areas.sce className="pull-right narrow" />
      <StationBranch stations onClick inside=Areas.sw />
      <StationBranch stations onClick inside=Areas.se className="pull-right" />
    </div>
};
