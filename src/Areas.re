let south_north = (station: Backend.station, south, north) => station.north > south && station.north < north;

let east = (station: Backend.station, south, north, east) =>
  station.north > south && station.north < north && station.east > east;

let west = (station: Backend.station, south, north, west) =>
  station.north > south && station.north < north && station.east < west;

let east_west = (station: Backend.station, south, north, east, west) =>
  station.north > south && station.north < north && station.east > east && station.east < west;

let nw = (station: Backend.station) => west(station, 59.35, 59.58, 17.898);

let ne = (station: Backend.station) => east(station, 59.37, 59.58, 17.898);

let ncw = (station: Backend.station) => west(station, 59.35, 59.37, 18.);

let nce = (station: Backend.station) => east(station, 59.35, 59.37, 18.);

let nc = (station: Backend.station) => south_north(station, 59.34, 59.35);

let c = (station: Backend.station) => south_north(station, 59.28, 59.34);

let sc = (station: Backend.station) => south_north(station, 59.26, 59.28);

let scw = (station: Backend.station) => west(station, 59.236, 59.26, 18.);

let sce = (station: Backend.station) => east(station, 59.236, 59.26, 18.);

let sw = (station: Backend.station) => east_west(station, 59.08, 59.236, 17.63, 17.98);

let se = (station: Backend.station) => east(station, 59.08, 59.236, 17.98);
