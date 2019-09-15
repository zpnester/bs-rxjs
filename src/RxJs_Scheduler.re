type t = RxJs__.scheduler;

[@bs.send] external now: t => float = "now";

[@bs.send]
external schedule3:
  (t, 'state => unit, ~delay: float, 'state) =>
  RxJs__.subscription =
  "schedule";

[@bs.send]
external schedule2:
  (t, unit => unit, ~delay: float) => RxJs__.subscription =
  "schedule";

[@bs.send]
external schedule: (t, unit => unit) => RxJs__.subscription =
  "schedule";