open RxJs__;

type t('a) = subject('a);

let asObservable: t('a) => observable('a);
let asObserver: t('a) => observer('a);
let asSubject: observable('a) => option(subject('a));

let make: unit => subject('a);
