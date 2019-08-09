open RxJs__;

type t('a) = connectableObservable('a);

include (module type of
  MakeObservable({
    type t('a) = connectableObservable('a);
  }));

include (module type of
  MakePipeable({
    type nonrec t('a) = t('a);
  }));

[@bs.send] external getSubject: t('a) => subject('a) = "getSubject";

let asConnectableObservable:
  observable('a) => option(connectableObservable('a));

[@bs.send] external connect: t('a) => subscription = "connect";