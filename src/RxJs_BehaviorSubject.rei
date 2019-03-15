open RxJs__;

type t('a) = behavior_subject('a);

include (module type of
  MakeSubject({
    type t('a) = behavior_subject('a);
  }));

let make: 'a => behavior_subject('a);

/* safe to call unless FFI'd BehaviorSubject from JS */
[@bs.send] external getValue: behavior_subject('a) => 'a = "getValue";
