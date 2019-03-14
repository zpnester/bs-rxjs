open RxJs__;

type t = subscription;

[@bs.send] external unsubscribe: subscription => unit = "";
