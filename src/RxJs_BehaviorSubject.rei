open RxJs__;

type t('a) = behaviorSubject('a);

include (module type of
  MakeSubject({
    type t('a) = behaviorSubject('a);
  }));

let make: 'a => behaviorSubject('a);

[@bs.send] external getValue: behaviorSubject('a) => 'a = "getValue";