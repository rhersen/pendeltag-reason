[%bs.raw {|require('./app.css')|}];

type geometry = {east: float, north: float};

type station = {signature: string, name: string, geometry};

type state = {stations: array station};

let getStations: (array station => unit) => unit = [%bs.raw
  {|
 function (callback) {
   var request = new XMLHttpRequest();
   request.open('GET', "/json/stations", true);
   request.onload = function () {
     const stations = JSON.parse(this.responseText).RESPONSE.RESULT[0].TrainStation;
     callback(stations.map(function (station) {
       return [station.LocationSignature, station.AdvertisedShortLocationName, [station.Geometry.WGS84.east, station.Geometry.WGS84.north]];
     }))
   }
   request.onerror = onerror;
   request.send();
 }
|}
];

let handleStations stations _ => ReasonReact.Update {stations: stations};

let component = ReasonReact.statefulComponent "App";

let make _children => {
  ...component,
  initialState: fun () => {stations: [||]},
  didMount: fun self => {
    getStations (self.update handleStations);
    ReasonReact.NoUpdate
  },
  render: fun {state} =>
    <div className="App">
      <div className="App-header">
        <h2> (ReasonReact.stringToElement "Pendelt\229g") </h2>
      </div>
      <ul>
        (
          ReasonReact.arrayToElement (
            Array.map
              (
                fun station =>
                  <li key=station.signature>
                    (ReasonReact.stringToElement station.name)
                  </li>
              )
              state.stations
          )
        )
      </ul>
    </div>
};
