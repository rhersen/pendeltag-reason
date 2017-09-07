type geometry = {east: float, north: float};

type station = {signature: string, name: string, geometry};

type announcement = {
  id: string,
  activity: string,
  destination: string,
  location: string,
  time: string,
  estimated: option string,
  actual: option string
};

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
