open RxJs__;

type t('a) = replay_subject('a);

include (module type of
  MakeSubject({
    type t('a) = replay_subject('a);
  }));

[@bs.module "rxjs"] [@bs.new]
external make:
  (~bufferSize: int=?, ~windowTime: int=?, unit) => replay_subject('a) =
  "ReplaySubject";
