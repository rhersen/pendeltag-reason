[%bs.raw {|require('./app.css')|}];

type action =
  | Stations (array Backend.station)
  | Announcements (array Backend.announcement);

type state = {
  stations: array Backend.station,
  announcements: array Backend.announcement
};

let el = ReasonReact.stringToElement;

let component = ReasonReact.reducerComponent "App";

let formatTime (s: string) => String.sub s 11 5;

let make _ => {
  ...component,
  initialState: fun () => {stations: [||], announcements: [||]},
  reducer: fun action state =>
    switch action {
    | Stations stations => ReasonReact.Update {...state, stations}
    | Announcements announcements =>
      ReasonReact.Update {...state, announcements}
    },
  didMount: fun self => {
    Backend.getStations (self.reduce (fun stations => Stations stations));
    ReasonReact.NoUpdate
  },
  render: fun self =>
    <div className="App">
      <div className="App-header"> <h2> (el "Pendelt\229g") </h2> </div>
      (
        if (Array.length self.state.announcements != 0) {
          <div onClick=(self.reduce (fun _ => Announcements [||]))>
            (el "X")
          </div>
        } else {
          <div>
            (
              ReasonReact.arrayToElement (
                Array.map
                  (
                    fun (station: Backend.station) =>
                      <span
                        key=station.signature
                        onClick=(
                          fun _ =>
                            Backend.getAnnouncements
                              (
                                self.reduce (
                                  fun announcements =>
                                    Announcements announcements
                                )
                              )
                              station.signature
                        )>
                        (el (station.name ^ " "))
                      </span>
                  )
                  self.state.stations
              )
            )
          </div>
        }
      )
      <table>
        (
          ReasonReact.arrayToElement (
            Array.map
              (
                fun (announcement: Backend.announcement) =>
                  <tr key=announcement.id>
                    <td> (el (formatTime announcement.time)) </td>
                    <td> (el announcement.destination) </td>
                    <td>
                      (
                        el (
                          switch announcement.estimated {
                          | None => "-"
                          | Some s => formatTime s
                          }
                        )
                      )
                    </td>
                    <td>
                      (
                        el (
                          switch announcement.actual {
                          | None => "-"
                          | Some s => formatTime s
                          }
                        )
                      )
                    </td>
                  </tr>
              )
              self.state.announcements
          )
        )
      </table>
    </div>
};
