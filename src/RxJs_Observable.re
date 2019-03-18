open RxJs__;

type t('a) = observable('a);

[@bs.send] [@bs.variadic]
external pipe: (t('a), array(operatorFunction('a, 'a))) => observable('a) =
  "pipe";

[@bs.send] external pipe0: t('a) => observable('a) = "pipe";

[@bs.send]
external pipe1: (t('a), operatorFunction('a, 'b)) => observable('b) =
  "pipe";

[@bs.send]
external pipe2:
  (t('a), operatorFunction('a, 'b), operatorFunction('b, 'c)) =>
  observable('c) =
  "pipe";
[@bs.send]
external pipe3:
  (
    t('a),
    operatorFunction('a, 'b),
    operatorFunction('b, 'c),
    operatorFunction('c, 'd)
  ) =>
  observable('d) =
  "pipe";

[@bs.send]
external pipe4:
  (
    t('a),
    operatorFunction('a, 'b),
    operatorFunction('b, 'c),
    operatorFunction('c, 'd),
    operatorFunction('d, 'e)
  ) =>
  observable('e) =
  "pipe";

[@bs.send]
external pipe5:
  (
    t('a),
    operatorFunction('a, 'b),
    operatorFunction('b, 'c),
    operatorFunction('c, 'd),
    operatorFunction('d, 'e),
    operatorFunction('e, 'f)
  ) =>
  observable('f) =
  "pipe";

[@bs.send]
external pipe6:
  (
    t('a),
    operatorFunction('a, 'b),
    operatorFunction('b, 'c),
    operatorFunction('c, 'd),
    operatorFunction('d, 'e),
    operatorFunction('e, 'f),
    operatorFunction('f, 'g)
  ) =>
  observable('g) =
  "pipe";

[@bs.send]
external pipe7:
  (
    t('a),
    operatorFunction('a, 'b),
    operatorFunction('b, 'c),
    operatorFunction('c, 'd),
    operatorFunction('d, 'e),
    operatorFunction('e, 'f),
    operatorFunction('f, 'g),
    operatorFunction('g, 'h)
  ) =>
  observable('h) =
  "pipe";

[@bs.send]
external pipe8:
  (
    t('a),
    operatorFunction('a, 'b),
    operatorFunction('b, 'c),
    operatorFunction('c, 'd),
    operatorFunction('d, 'e),
    operatorFunction('e, 'f),
    operatorFunction('f, 'g),
    operatorFunction('g, 'h),
    operatorFunction('h, 'i)
  ) =>
  observable('i) =
  "pipe";



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
