open RxJs__;

type t('a) = async_subject('a);

include (module type of
  MakeSubject({
    type t('a) = async_subject('a);
  }));

let make: unit => t('a);