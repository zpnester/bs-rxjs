open RxJs__;

type t('a) = websocketSubject('a);

include (module type of
  MakeSubject({
    type t('a) = websocketSubject('a);
  }));

let make: (~url: string) => websocketSubject(Js.Json.t);