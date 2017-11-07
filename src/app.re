[%bs.raw {|require('./app.css')|}];

[@bs.module] external logo : string = "./logo.svg";

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
          <StationMenu
            stations=self.state.stations
            setAnnouncements=(self.reduce((announcements) => Announcements(announcements)))
          />
        }
      )
      <Table announcements=self.state.announcements />
    </div>
};
