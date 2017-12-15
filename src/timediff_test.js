import Timediff from "./timediff.re";

describe("Timediff.format", () => {
  test("empty input", () => {
    expect(Timediff.format(["", "", "", "", "", 0, 0], [0, 0, 0])).toBe("0s");
  });

  test("seconds", () => {
    expect(actual("T13:38:00", [13, 37, 30])).toBe("30s");
    expect(actual("T13:38:00", [13, 37, 40])).toBe("20s");
    expect(actual("T13:38:00", [13, 37, 1])).toBe("59s");
  });

  test("minutes:seconds", () => {
    expect(actual("T13:38:00", [13, 36, 0])).toBe("2:00");
    expect(actual("T13:38:00", [13, 35, 55])).toBe("2:05");
    expect(actual("T13:38:00", [13, 35, 50])).toBe("2:10");
  });

  test("minutes", () => {
    expect(actual("T13:38:00", [13, 27, 0])).toBe("11min");
  });

  test("across day boundary", () => {
    expect(actual("T00:05:00", [23, 59, 0])).toBe("6:00");
  });

  test("don't show negative minutes", () => {
    expect(actual("T13:36:00", [13, 38, 0])).toBe("");
  });
});

function actual(t, now) {
  return Timediff.format(["", "", "", [], "", t, 0, 0], now);
}
