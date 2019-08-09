open RxJs__;

type t('a) = replay_subject('a);

include (module type of
  MakeSubject({
    type t('a) = replay_subject('a);
  }));

let make2: (~bufferSize: int, ~windowTime: float) => replay_subject('a);

let make: (~bufferSize: int) => replay_subject('a);