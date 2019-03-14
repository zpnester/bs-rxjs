open RxJs__;

type t('a) = connectable_observable('a);

let asObservable: t('a) => observable('a);

let getSubject: t('a) => subject('a);

let asConnectableObservable:
  observable('a) => option(connectable_observable('a));

let connect: t('a) => subscription;
