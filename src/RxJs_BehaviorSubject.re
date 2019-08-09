open RxJs__;

type t('a) = behaviorSubject('a);

include MakeSubject({
  type t('a) = behaviorSubject('a);
});

[@bs.module "rxjs"] [@bs.new]
external make: 'a => behaviorSubject('a) = "BehaviorSubject";

[@bs.send] external getValue: behaviorSubject('a) => 'a = "getValue";