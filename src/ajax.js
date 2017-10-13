function onerror(e) {
  console.error(e);
}

function getStations(callback) {
  var request = new XMLHttpRequest();
  request.open("GET", "/json/stations", true);

  request.onload = function() {
    const results = JSON.parse(this.responseText).RESPONSE.RESULT[0]
      .TrainStation;
    callback(
      results.map(function(r) {
        return [
          r.LocationSignature,
          r.AdvertisedShortLocationName,
          [r.Geometry.WGS84.east, r.Geometry.WGS84.north]
        ];
      })
    );
  };

  request.onerror = onerror;
  request.send();
}

function getAnnouncements(callback, signature) {
  var request = new XMLHttpRequest();

  request.open(
    "GET",
    "/json/departures?since=0:15&until=0:59&locations=" + signature,
    true
  );

  request.onload = function() {
    if (this.status !== 200) {
      callback([]);
      return;
    }

    const results = JSON.parse(this.responseText).RESPONSE.RESULT[0]
      .TrainAnnouncement;

    if (!results) {
      callback([]);
      return;
    }

    callback(
      results.map(function(r) {
        function option(field) {
          return r[field] ? [r[field]] : 0;
        }

        return [
          r.AdvertisedTrainIdent,
          r.ActivityType,
          r.ToLocation && r.ToLocation.length
            ? r.ToLocation[0].LocationName
            : "?",
          r.LocationSignature,
          r.AdvertisedTimeAtLocation,
          option("EstimatedTimeAtLocation"),
          option("TimeAtLocation")
        ];
      })
    );
  };

  request.onerror = onerror;
  request.send();
}

function hour() {
  const now = new Date();
  return now.getHours();
}

function minute() {
  const now = new Date();
  return now.getMinutes();
}

function second() {
  const now = new Date();
  return now.getSeconds();
}

function interval(callback) {
  return setInterval(callback, 256);
}

function clear(intervalId) {
  return clearInterval(intervalId);
}

module.exports = {
  getStations,
  getAnnouncements,
  hour,
  minute,
  second,
  interval,
  clear
};
