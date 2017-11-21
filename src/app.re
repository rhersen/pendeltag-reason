[%bs.raw {|require('./app.css')|}];

type action =
  | Stations(array(Backend.station))
  | Announcements(array(Backend.announcement))
  | Now((int, int, int));

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
    | Stations(stations) =>
      Array.sort(
        (a: Backend.station, b: Backend.station) => - Pervasives.compare(a.north, b.north),
        stations
      );
      ReasonReact.Update({...state, stations})
    | Announcements(announcements) => ReasonReact.Update({...state, announcements})
    | Now(hms) => ReasonReact.Update({...state, now: hms})
    },
  didMount: ({reduce}) => {
    Backend.getStations(reduce((stations) => Stations(stations)));
    ReasonReact.NoUpdate
  },
  render: ({reduce, state: {announcements, stations, now}}) => {
    let tick = () => Now(Backend.now());
    let handleAnnouncements = (announcements) => {
      Backend.interval(reduce(tick));
      Announcements(announcements)
    };
    let clear = (_event) => {
      Backend.clear();
      Announcements([||])
    };
    <div className="App">
      (
        if (Array.length(announcements) > 0) {
          <Header onClick=(reduce(clear)) location=(Backend.name(announcements[0].location)) />
        } else {
          <StationMenu stations onClick=(Backend.getAnnouncements(reduce(handleAnnouncements))) />
        }
      )
      <Table announcements now />
    </div>
  }
};