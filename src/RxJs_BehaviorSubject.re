open RxJs__;

type t('a) = behavior_subject('a);

include MakeSubject({
  type t('a) = behavior_subject('a);
});

[@bs.module "rxjs"] [@bs.new]
external make: 'a => behavior_subject('a) = "BehaviorSubject";

/* safe to call unless FFI'd BehaviorSubject from JS */
[@bs.send] external getValue: behavior_subject('a) => 'a = "getValue";
