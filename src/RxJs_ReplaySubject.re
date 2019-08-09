open RxJs__;

type t('a) = replay_subject('a);
include MakeSubject({
  type t('a) = replay_subject('a);
});

[@bs.module "rxjs"] [@bs.new]
external make2: (~bufferSize: int, ~windowTime: float) => replay_subject('a) =
  "ReplaySubject";

[@bs.module "rxjs"] [@bs.new]
external make: (~bufferSize: int) => replay_subject('a) = "ReplaySubject";