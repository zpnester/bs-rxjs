open RxJs__;

type t('a) = observable('a);

include MakePipeable({
  type nonrec t('a) = t('a);
});

type subscribe_params('a) = {
  .
  "next": Js.Nullable.t('a => unit),
  "error": Js.Nullable.t(Js.Json.t => unit),
  "complete": Js.Nullable.t(unit => unit),
};

[@bs.send]
external subscribe_: (t('a), subscribe_params('a)) => subscription =
  "subscribe";

let subscribe =
    (
      self: t('a),
      ~next: option('a => unit)=?,
      ~error: option(Js.Json.t => unit)=?,
      ~complete: option(unit => unit)=?,
      (),
    ) => {
  let args = {
    "next": Js.Nullable.fromOption(next),
    "error": Js.Nullable.fromOption(error),
    "complete": Js.Nullable.fromOption(complete),
  };
  subscribe_(self, args);
};

[@bs.send]
external subscribeWithObserver_: (t('a), observer('a)) => subscription =
  "subscribe";

let subscribeWithObserver = (self: t('a), observer: observer('a)) =>
  subscribeWithObserver_(self, observer);

/////////

[@bs.module "rxjs"] [@bs.scope "Observable"]
external create: (observer('a) => unit) => observable('a) = "create";

[@bs.module "rxjs"] [@bs.scope "Observable"]
external createWithTeardown:
  ([@bs.uncurry] ((observer('a), unit) => unit)) => observable('a) =
  "create";
