let component = ReasonReact.statelessComponent("Header");

let make = (~onClick, ~location, _children) => {
  ...component,
  render: (_self) =>
    <div>
      <span className="close" onClick> (ReasonReact.stringToElement({js|×|js})) </span>
      <span> (ReasonReact.stringToElement(" ")) </span>
      <h1> (ReasonReact.stringToElement(location)) </h1>
    </div>
};
