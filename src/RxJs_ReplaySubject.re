open RxJs__;

type t('a) = replaySubject('a);
include MakeSubject({
  type t('a) = replaySubject('a);
});

[@bs.module "rxjs/_esm2015"] [@bs.new]
external make2: (~bufferSize: int, ~windowTime: float) => replaySubject('a) =
  "ReplaySubject";

[@bs.module "rxjs/_esm2015"] [@bs.new]
external make: (~bufferSize: int) => replaySubject('a) = "ReplaySubject";