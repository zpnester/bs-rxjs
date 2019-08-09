open RxJs__;

type t('a) = asyncSubject('a);

include (module type of
  MakeSubject({
    type t('a) = asyncSubject('a);
  }));

let make: unit => t('a);