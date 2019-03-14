open RxJs__;

type t('a) = async_subject('a);

let asObservable: t('a) => observable('a);

let asObserver: t('a) => observer('a);
let asSubject: t('a) => subject('a);

let make: unit => async_subject('a);
