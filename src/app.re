[%bs.raw {|require('./app.css')|}];

type action =
  | Stations (array Backend.station)
  | Announcements (array Backend.announcement)
  | Now float;

let el = ReasonReact.stringToElement;

let formatTime (s: string) => String.sub s 11 5;

let formatCountdown time now => {
  let r = (Backend.millis time -. now) /. 1000.;
  if ((-90.) < r && r < 300.) {
    Printf.sprintf "%4.1f" r
  } else {
    Printf.sprintf "%d min" (truncate (r /. 60.))
  }
};

type state = {
  stations: array Backend.station,
  name: Hashtbl.t string string,
  announcements: array Backend.announcement,
  now: float
};

let component = ReasonReact.reducerComponent "App";

let make _ => {
  ...component,
  initialState: fun () => {
    stations: [||],
    name: Hashtbl.create 231,
    announcements: [||],
    now: Backend.now ()
  },
  reducer: fun action state =>
    switch action {
    | Stations stations =>
      let name = Hashtbl.create 231;
      Array.iter
        (fun (station: Backend.station) => Hashtbl.add name station.signature station.name)
        stations;
      ReasonReact.Update {...state, name, stations}
    | Announcements announcements => ReasonReact.Update {...state, announcements}
    | Now now => ReasonReact.Update {...state, now}
    },
  didMount: fun self => {
    Backend.getStations (self.reduce (fun stations => Stations stations));
    Backend.interval (self.reduce (fun _ => Now (Backend.now ())));
    ReasonReact.NoUpdate
  },
  render: fun self =>
    <div className="App">
      (
        if (Array.length self.state.announcements != 0) {
          <div onClick=(self.reduce (fun _ => Announcements [||]))> (el "X") </div>
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
                              (self.reduce (fun announcements => Announcements announcements))
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
        <tbody>
          (
            ReasonReact.arrayToElement (
              Array.map
                (
                  fun (announcement: Backend.announcement) =>
                    <tr key=announcement.id>
                      <td> (el (formatTime announcement.time)) </td>
                      <td> (el (Hashtbl.find self.state.name announcement.destination)) </td>
                      <td>
                        <i>
                          (
                            el (
                              switch announcement.estimated {
                              | None => "-"
                              | Some s => formatTime s
                              }
                            )
                          )
                        </i>
                      </td>
                      <td>
                        <b>
                          (
                            el (
                              switch announcement.actual {
                              | None => "-"
                              | Some s => formatTime s
                              }
                            )
                          )
                        </b>
                      </td>
                      <td className="countdown">
                        (el (formatCountdown announcement.time self.state.now))
                      </td>
                    </tr>
                )
                self.state.announcements
            )
          )
        </tbody>
      </table>
    </div>
};