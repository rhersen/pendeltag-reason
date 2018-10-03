let el = ReasonReact.stringToElement;

let component = ReasonReact.statelessComponent("Header");

let make = (~onClick, ~location, _children) => {
  ...component,
  render: (_self) => <div> <span className="close" onClick> (el({js|⇐|js})) </span> <h1> (el(location)) </h1> </div>
};
