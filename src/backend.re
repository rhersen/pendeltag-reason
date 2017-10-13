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

external getStations : (array station => unit) => unit = "getStations" [@@bs.module "./ajax"];

external getAnnouncements : (array announcement => unit) => string => unit =
  "getAnnouncements" [@@bs.module "./ajax"];

external hour : unit => int = "hour" [@@bs.module "./ajax"];

external minute : unit => int = "minute" [@@bs.module "./ajax"];

external second : unit => int = "second" [@@bs.module "./ajax"];

external interval : (unit => unit) => int = "interval" [@@bs.module "./ajax"];

external clear : int => unit = "clear" [@@bs.module "./ajax"];