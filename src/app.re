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
     const results = JSON.parse(this.responseText).RESPONSE.RESULT[0].TrainStation;
     callback(results.map(function (r) {
       return [r.LocationSignature, r.AdvertisedShortLocationName, [r.Geometry.WGS84.east, r.Geometry.WGS84.north]];
     }))
   }
   request.onerror = onerror;
   request.send();
 }
|}
];

type announcement = {
  id: string,
  activity: string,
  destination: string,
  location: string,
  time: string,
  estimated: option string,
  actual: option string
};

let getAnnouncements: (array announcement => unit) => string => unit = [%bs.raw
  {|
 function (callback, signature) {
   console.log(signature);
   var request = new XMLHttpRequest();
   request.open('GET', "/json/departures?since=0:15&until=0:59&locations=" + signature, true);
   request.onload = function () {
     console.log(JSON.parse(this.responseText).RESPONSE.RESULT[0].TrainAnnouncement);
     const results = JSON.parse(this.responseText).RESPONSE.RESULT[0].TrainAnnouncement;
     callback(results.map(function (r) {
       function option(field) {
         return r[field] ? [r[field]] : 0;
       }
       return [
          r.AdvertisedTrainIdent,
          r.ActivityType,
          r.ToLocation.length ? r.ToLocation[0].LocationName : "?",
          r.LocationSignature,
          r.AdvertisedTimeAtLocation,
          r.EstimatedTimeAtLocation ? [r.EstimatedTimeAtLocation] : 0,
          r.TimeAtLocation ? [r.TimeAtLocation] : 0];
     }))
   }
   request.onerror = onerror;
   request.send();
 }
|}
];

let handleStations stations _ => ReasonReact.Update {stations: stations};

let handleAnnouncements announcements _ => {
  Array.iter
    (
      fun a =>
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
    getStations (self.update handleStations);
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
                fun station =>
                  <li
                    key=station.signature
                    onClick=(
                      fun _event => {
                        Js.log ("clicked " ^ station.signature);
                        getAnnouncements
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
