open RxJs__;

type t('a) = websocket_subject('a);

let asObservable: t('a) => observable('a);
let asObserver: t('a) => observer('a);
let asSubject: t('a) => subject('a);

let make: (~url: string) => websocket_subject(Js.Json.t);
