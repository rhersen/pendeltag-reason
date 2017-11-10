[%bs.raw {|require('./app.css')|}];

[@bs.module] external logo : string = "./logo.svg";

type action =
  | Stations(array(Backend.station))
  | Announcements(array(Backend.announcement));

type state = {
  stations: array(Backend.station),
  announcements: array(Backend.announcement),
  now: (int, int, int)
};

let component = ReasonReact.reducerComponent("App");

let make = (_children) => {
  ...component,
  initialState: () => {stations: [||], announcements: [||], now: Backend.now()},
  reducer: (action, state) =>
    switch action {
    | Stations(stations) => ReasonReact.Update({...state, stations})
    | Announcements(announcements) => ReasonReact.Update({...state, announcements})
    },
  didMount: ({reduce}) => {
    Backend.getStations(reduce((stations) => Stations(stations)));
    ReasonReact.NoUpdate
  },
  render: ({reduce, state: {announcements, stations, now}}) =>
    <div className="App">
      (
        if (Array.length(announcements) > 0) {
          <Header
            onClick=(reduce((_event) => Announcements([||])))
            location=(Backend.name(announcements[0].location))
          />
        } else {
          <StationMenu
            stations
            onClick=(
              Backend.getAnnouncements(reduce((announcements) => Announcements(announcements)))
            )
          />
        }
      )
      <Table announcements now />
    </div>
};