open RxJs__;

type t('a) = behavior_subject('a);

let asObservable: t('a) => observable('a);
let asObserver: t('a) => observer('a);
let asSubject: t('a) => subject('a);

let make: 'a => behavior_subject('a);

let getValue: behavior_subject('a) => 'a;
