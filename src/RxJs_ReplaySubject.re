open RxJs__;

type t('a) = replay_subject('a);
include MakeSubject({
  type t('a) = replay_subject('a);
});

[@bs.module "rxjs"] [@bs.new]
external make:
  (~bufferSize: int=?, ~windowTime: int=?, unit) => replay_subject('a) =
  "ReplaySubject";
