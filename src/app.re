[%bs.raw {|require('./app.css')|}];

type action =
  | Stations (array Backend.station)
  | Announcements (array Backend.announcement);

type state = {
  stations: array Backend.station,
  announcements: array Backend.announcement
};

let component = ReasonReact.reducerComponent "App";

let formatAnnouncement (a: Backend.announcement) =>
  a.time ^
  a.destination ^
  (
    switch a.estimated {
    | None => ""
    | Some s => " estimated: " ^ s
    }
  ) ^ (
    switch a.actual {
    | None => ""
    | Some s => " actual: " ^ s
    }
  );

let make _ => {
  ...component,
  initialState: fun () => {stations: [||], announcements: [||]},
  reducer: fun action state =>
    switch action {
    | Stations stations => ReasonReact.Update {...state, stations}
    | Announcements announcements =>
      Array.iter (fun a => a |> formatAnnouncement |> Js.log) announcements;
      ReasonReact.Update {...state, announcements}
    },
  didMount: fun self => {
    Backend.getStations (self.reduce (fun stations => Stations stations));
    ReasonReact.NoUpdate
  },
  render: fun self =>
    <div className="App">
      <div className="App-header">
        <h2> (ReasonReact.stringToElement "Pendelt\229g") </h2>
      </div>
      (
        Array.length self.state.announcements != 0 ?
          <div onClick=(self.reduce (fun _ => Announcements [||]))>
            (ReasonReact.stringToElement "X")
          </div> :
          <div> (ReasonReact.stringToElement "aoeu") </div>
      )
      <div>
        (
          ReasonReact.stringToElement (
            string_of_int (Array.length self.state.announcements) ^ " announcements"
          )
        )
      </div>
      <ul>
        (
          ReasonReact.arrayToElement (
            Array.map
              (
                fun (announcement: Backend.announcement) =>
                  <li> (ReasonReact.stringToElement announcement.destination) </li>
              )
              self.state.announcements
          )
        )
      </ul>
      <ul>
        (
          ReasonReact.arrayToElement (
            Array.map
              (
                fun (station: Backend.station) =>
                  <li
                    key=station.signature
                    onClick=(
                      fun _ =>
                        Backend.getAnnouncements
                          (
                            self.reduce (
                              fun announcements => Announcements announcements
                            )
                          )
                          station.signature
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
