open RxJs__;

type t('a) = connectableObservable('a);

include MakeObservable({
  type nonrec t('a) = t('a);
});

include MakePipeable({
  type nonrec t('a) = t('a);
});

[@bs.send] external getSubject: t('a) => subject('a) = "getSubject";

external oAsJson__: observable('a) => Js.Json.t = "%identity";

external mapOptionUnsafe__:
  option(Js.Json.t) => option(connectableObservable('a)) =
  "%identity";

/* instanceof won't work, CO is O with connect method, not real instance of ConnectableObservable */
let asConnectableObservable_: Js.Json.t => option(Js.Json.t) = [%raw
  {|
  function(o) {
    if (o.connect && o.getSubject) {
      return o;
    }
  }
  |}
];

let asConnectableObservable:
  observable('a) => option(connectableObservable('a)) =
  obs => asConnectableObservable_(oAsJson__(obs))->mapOptionUnsafe__;

[@bs.send] external connect: t('a) => subscription = "connect";