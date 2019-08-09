type t = RxJs__.scheduler;

[@bs.send] external now: t => float = "now";

[@bs.send]
external schedule3:
  (t, option('state) => unit, ~delay: float, ~state: option('state)) =>
  RxJs__.subscription =
  "schedule";

[@bs.send]
external schedule2:
  (t, option('state) => unit, ~delay: float) => RxJs__.subscription =
  "schedule";

[@bs.send]
external schedule: (t, option('state) => unit) => RxJs__.subscription =
  "schedule";