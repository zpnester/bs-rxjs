open RxJs__;

type t('a) = websocket_subject('a);

include MakeSubject({
  type t('a) = websocket_subject('a);
});

[@bs.module "rxjs/webSocket"] [@bs.new]
external make: (~url: string) => websocket_subject(Js.Json.t) =
  "WebSocketSubject";