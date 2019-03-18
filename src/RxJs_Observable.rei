open RxJs__;

type t('a) = observable('a);

include (module type of
  MakePipeable({
    type nonrec t('a) = t('a);
  }));

let subscribe:
  (
    t('a),
    ~next: 'a => unit=?,
    ~error: Js.Json.t => unit=?,
    ~complete: unit => unit=?,
    unit
  ) =>
  subscription;

let subscribeWithObserver: (t('a), observer('a)) => subscription;

[@bs.module "rxjs"] [@bs.scope "Observable"]
external create: (observer('a) => unit) => observable('a) = "create";

[@bs.module "rxjs"] [@bs.scope "Observable"]
external createWithTeardown:
  ([@bs.uncurry] ((observer('a), unit) => unit)) => observable('a) =
  "create";
