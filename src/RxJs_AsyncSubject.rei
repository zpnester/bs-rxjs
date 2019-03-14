open RxJs__;

type t('a) = async_subject('a);

include (module type of
  MakeSubject({
    type t('a) = async_subject('a);
  }));

[@bs.module "rxjs"] [@bs.new]
external make: unit => async_subject('a) = "AsyncSubject";
