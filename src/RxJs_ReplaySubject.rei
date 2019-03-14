open RxJs__;

type t('a) = replay_subject('a);

let asObservable: t('a) => observable('a);
let asObserver: t('a) => observer('a);
let asSubject: t('a) => subject('a);

let make:
  (~bufferSize: int=?, ~windowTime: int=?, unit) => replay_subject('a);
