open RxJs__;

type t('a) = websocket_subject('a);

include (module type of
  MakeSubject({
    type t('a) = websocket_subject('a);
  }));

let make: (~url: string) => websocket_subject(Js.Json.t);