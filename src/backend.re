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

external getStations : (array station => unit) => unit =
  "getStations" [@@bs.module "./ajax"];

external getAnnouncements : (array announcement => unit) => string => unit =
  "getAnnouncements" [@@bs.module "./ajax"];

external now : unit => float = "now" [@@bs.module "./ajax"];

external millis : string => float = "millis" [@@bs.module "./ajax"];
