type t = RxJs__.scheduler;

[@bs.send] external now: t => float = "now";

[@bs.send]
external schedule:
  (
    t,
    Js.Nullable.t('state) => unit,
    ~delay: float=?,
    ~state: Js.Nullable.t('state)=?,
    unit
  ) =>
  RxJs__.subscription =
  "schedule";
