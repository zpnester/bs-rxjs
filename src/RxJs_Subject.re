open RxJs__;

type t('a) = subject('a);

include MakeObservable({
  type t('a) = subject('a);
});
include MakeObserver({
  type t('a) = subject('a);
});

[@bs.module "rxjs"] [@bs.new] external make: unit => subject('a) = "Subject";

external observableToJson__: observable('a) => Js.Json.t = "%identity";
external mapOptionUnsafe__: option(Js.Json.t) => option(subject('a)) =
  "%identity";

[@bs.val] [@bs.module "rxjs"] external subjectCtor: Js.Json.t = "Subject";

let asSubject_: (Js.Json.t, Js.Json.t) => Js.Nullable.t(Js.Json.t) = [%raw
  {|
  function(o, c) {
    if (o instanceof c) {
      return o;
    } else {
      return null;
    }
  }
  |}
];

let asSubject: observable('a) => option(subject('a)) =
  obs =>
    asSubject_(observableToJson__(obs), subjectCtor)
    ->Js.Nullable.toOption
    ->mapOptionUnsafe__;
