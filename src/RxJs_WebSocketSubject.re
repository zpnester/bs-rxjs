open RxJs__;

type t('a) = websocketSubject('a);

include MakeSubject({
  type t('a) = websocketSubject('a);
});

[@bs.module "rxjs/webSocket"] [@bs.new]
external make: (~url: string) => websocketSubject(Js.Json.t) =
  "WebSocketSubject";