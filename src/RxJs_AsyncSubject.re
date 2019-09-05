open RxJs__;

type t('a) = asyncSubject('a);

include MakeSubject({
  type t('a) = asyncSubject('a);
});

[@bs.module "rxjs/_esm2015"] [@bs.new]
external make: unit => asyncSubject('a) = "AsyncSubject";