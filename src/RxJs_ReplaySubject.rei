open RxJs__;

type t('a) = replaySubject('a);

include (module type of
  MakeSubject({
    type t('a) = replaySubject('a);
  }));

let make2: (~bufferSize: int, ~windowTime: float) => replaySubject('a);

let make: (~bufferSize: int) => replaySubject('a);