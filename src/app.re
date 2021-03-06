[%bs.raw {|require('./app.css')|}];

type action =
  | Stations (array Backend.station)
  | Announcements (array Backend.announcement) int
  | Now (int, int, int);

let el = ReasonReact.stringToElement;

let formatTime (s: string) => String.sub s 11 5;

let formatCountdown (announcement: Backend.announcement) now => {
  let time =
    switch announcement.estimated {
    | None => announcement.time
    | Some s => s
    };
  switch (Js.Re.exec time [%re "/T(\\d\\d):(\\d\\d):(\\d\\d)/"]) {
  | None => time
  | Some result =>
    let match = Js.Re.matches result;
    let (hour, minute, second) = now;
    string_of_int (
      int_of_string match.(3) - second + (int_of_string match.(2) - minute) * 60 +
      (int_of_string match.(1) - hour) * 60 * 60
    )
  }
};

type state = {
  stations: array Backend.station,
  name: Hashtbl.t string string,
  announcements: array Backend.announcement,
  now: (int, int, int),
  intervalId: int
};

let getName name destination =>
  if (Hashtbl.mem name destination) {
    Hashtbl.find name destination
  } else {
    destination
  };

let component = ReasonReact.reducerComponent "App";

let make _ => {
  ...component,
  initialState: fun () => {
    stations: [||],
    name: Hashtbl.create 53,
    announcements: [||],
    now: Backend.now (),
    intervalId: 0
  },
  reducer: fun action state =>
    switch action {
    | Stations stations =>
      let name = Hashtbl.create 53;
      Array.iter
        (fun (station: Backend.station) => Hashtbl.add name station.signature station.name)
        stations;
      ReasonReact.Update {...state, name, stations}
    | Announcements announcements intervalId =>
      ReasonReact.Update {...state, announcements, intervalId}
    | Now now => ReasonReact.Update {...state, now}
    },
  didMount: fun self => {
    Backend.getStations (self.reduce (fun stations => Stations stations));
    ReasonReact.NoUpdate
  },
  render: fun self =>
    <div className="App">
      (
        if (Array.length self.state.announcements != 0) {
          <div
            onClick=(
              self.reduce (
                fun _ => {
                  Backend.clear self.state.intervalId;
                  Announcements [||] 0
                }
              )
            )>
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
                        className="station"
                        onClick=(
                          fun _ =>
                            Backend.getAnnouncements
                              (
                                self.reduce (
                                  fun announcements =>
                                    Announcements
                                      announcements
                                      (
                                        Backend.interval (
                                          self.reduce (fun _ => Now (Backend.now ()))
                                        )
                                      )
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
        <tbody>
          (
            ReasonReact.arrayToElement (
              Array.map
                (
                  fun (announcement: Backend.announcement) =>
                    <tr key=announcement.id>
                      <td> (el (formatTime announcement.time)) </td>
                      <td> (el (getName self.state.name announcement.destination)) </td>
                      <td>
                        (
                          switch announcement.actual {
                          | None =>
                            switch announcement.estimated {
                            | None => el ""
                            | Some s => <i> (el (formatTime s)) </i>
                            }
                          | Some s => <b> (el (formatTime s)) </b>
                          }
                        )
                      </td>
                      <td className="countdown">
                        (el (formatCountdown announcement self.state.now))
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