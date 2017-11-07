[%bs.raw {|require('./app.css')|}];

[@bs.module] external logo : string = "./logo.svg";

let formatTime = (s) => String.sub(s, 11, 5);

type action =
  | Stations(array(Backend.station))
  | Announcements(array(Backend.announcement));

type state = {
  stations: array(Backend.station),
  announcements: array(Backend.announcement)
};

let component = ReasonReact.reducerComponent("App");

let make = (_children) => {
  ...component,
  initialState: () => {stations: [||], announcements: [||]},
  reducer: (action, state) =>
    switch action {
    | Stations(stations) => ReasonReact.Update({...state, stations})
    | Announcements(announcements) => ReasonReact.Update({...state, announcements})
    },
  didMount: (self) => {
    Backend.getStations(self.reduce((stations) => Stations(stations)));
    ReasonReact.NoUpdate
  },
  render: (self) =>
    <div className="App">
      (
        if (Array.length(self.state.announcements) > 0) {
          <div onClick=(self.reduce((_event) => Announcements([||])))>
            (ReasonReact.stringToElement("X"))
          </div>
        } else {
          ReasonReact.arrayToElement(
            Array.map(
              (station: Backend.station) =>
                <span
                  key=station.signature
                  onClick=(
                    (_) =>
                      Backend.getAnnouncements(
                        self.reduce((announcements) => Announcements(announcements)),
                        station.signature
                      )
                  )>
                  (ReasonReact.stringToElement(station.name ++ " "))
                </span>,
              self.state.stations
            )
          )
        }
      )
      <table>
        <tbody>
          (
            ReasonReact.arrayToElement(
              Array.map(
                (announcement: Backend.announcement) =>
                  <tr key=announcement.id>
                    <td> (ReasonReact.stringToElement(announcement.id)) </td>
                    <td> (ReasonReact.stringToElement(formatTime(announcement.time))) </td>
                    <td> (ReasonReact.stringToElement(announcement.destination)) </td>
                    <td>
                      (
                        switch announcement.actual {
                        | Some(s) => <b> (ReasonReact.stringToElement(formatTime(s))) </b>
                        | None =>
                          switch announcement.estimated {
                          | Some(s) => <i> (ReasonReact.stringToElement(formatTime(s))) </i>
                          | None => ReasonReact.stringToElement("-")
                          }
                        }
                      )
                    </td>
                  </tr>,
                self.state.announcements
              )
            )
          )
        </tbody>
      </table>
    </div>
};
