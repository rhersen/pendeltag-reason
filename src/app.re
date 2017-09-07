[%bs.raw {|require('./app.css')|}];

type state = {stations: array Backend.station};

let handleStations stations _ => ReasonReact.Update {stations: stations};

let handleAnnouncements announcements _ => {
  Array.iter
    (
      fun (a: Backend.announcement) =>
        Js.log (
          a.time ^
          " " ^
          a.destination ^
          (
            switch a.estimated {
            | None => " "
            | Some s => s
            }
          ) ^ (
            switch a.actual {
            | None => " "
            | Some s => s
            }
          )
        )
    )
    announcements;
  ReasonReact.NoUpdate
};

let component = ReasonReact.statefulComponent "App";

let make _children => {
  ...component,
  initialState: fun () => {stations: [||]},
  didMount: fun self => {
    Backend.getStations (self.update handleStations);
    ReasonReact.NoUpdate
  },
  render: fun self =>
    <div className="App">
      <div className="App-header">
        <h2> (ReasonReact.stringToElement "Pendelt\229g") </h2>
      </div>
      <ul>
        (
          ReasonReact.arrayToElement (
            Array.map
              (
                fun (station: Backend.station) =>
                  <li
                    key=station.signature
                    onClick=(
                      fun _event => {
                        Js.log ("clicked " ^ station.signature);
                        Backend.getAnnouncements
                          (self.update handleAnnouncements) station.signature
                      }
                    )>
                    (ReasonReact.stringToElement station.name)
                  </li>
              )
              self.state.stations
          )
        )
      </ul>
    </div>
};
