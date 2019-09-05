open RxJs__;

type t('a) = behaviorSubject('a);

include MakeSubject({
  type t('a) = behaviorSubject('a);
});

[@bs.module "rxjs/_esm2015"] [@bs.new]
external make: 'a => behaviorSubject('a) = "BehaviorSubject";

[@bs.send] external getValue: behaviorSubject('a) => 'a = "getValue";