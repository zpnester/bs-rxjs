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

[@bs.module "rxjs"] [@bs.new] external make: unit => subject('a) = "Subject";
