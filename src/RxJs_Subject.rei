open RxJs__;

type t('a) = subject('a);

include (module type of
  MakeObservable({
    type t('a) = subject('a);
  }));
include (module type of
  MakeObserver({
    type t('a) = subject('a);
  }));

let asSubject: observable('a) => option(subject('a));

let make: unit => subject('a);
