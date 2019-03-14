open RxJs__;

type t('a) = connectable_observable('a);
include MakeObservable({
  type t('a) = connectable_observable('a);
});

[@bs.send] external getSubject: t('a) => subject('a) = "getSubject";

[@bs.val] [@bs.module "rxjs"]
external connectableObservableCtor: Js.Json.t = "ConnectableObservable";

external oAsJson__: observable('a) => Js.Json.t = "%identity";
external coFromJsonUnsafe__: Js.Json.t => connectable_observable('a) =
  "%identity";

/* instanceof won't work, pipe returns observable with connect method, not real instance of ConnectableObservable */
let asConnectableObservable_:
  (Js.Json.t, Js.Json.t) => Js.Nullable.t(Js.Json.t) = [%raw
  {|
  function(o, c) {
    if (o.connect && o.getSubject) {
      return o;
    } else {
      return null;
    }
  }
  |}
];

let asConnectableObservable:
  observable('a) => option(connectable_observable('a)) =
  obs =>
    asConnectableObservable_(oAsJson__(obs), connectableObservableCtor)
    ->Js.Nullable.toOption
    ->Belt.Option.map(coFromJsonUnsafe__);

[@bs.send] external connect: t('a) => subscription = "connect";
