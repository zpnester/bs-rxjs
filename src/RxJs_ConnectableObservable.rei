open RxJs__;

type t('a) = connectable_observable('a);

include (module type of
  MakeObservable({
    type t('a) = connectable_observable('a);
  }));

include (module type of
  MakePipeable({
    type nonrec t('a) = t('a);
  }));

[@bs.send] external getSubject: t('a) => subject('a) = "getSubject";

let asConnectableObservable:
  observable('a) => option(connectable_observable('a));

[@bs.send] external connect: t('a) => subscription = "connect";