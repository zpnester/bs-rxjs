open RxJs__;

type t = subscription;

[@bs.send] external unsubscribe: t => unit = "unsubscribe";

[@bs.get] external closed: t => bool = "closed";

[@bs.module "rxjs"] [@bs.scope "Subscription"] external empty: t = "EMPTY";

// no external
let make: unit => t;

let makeU: (unit => unit) => t;

[@bs.send] external add: (t, t) => t = "add";
[@bs.send] external addT: (t, unit => unit) => t = "add";

[@bs.send] external remove: (t, t) => unit = "remove";