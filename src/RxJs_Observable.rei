open RxJs__;

type t('a) = observable('a);

[@bs.send]
external pipe: (t('a), operator('a, 'b)) => observable('b) = "pipe";

[@bs.send]
external pipe2:
  (t('a), operator('a, 'b), operator('b, 'c)) => observable('c) =
  "pipe";

[@bs.send]
external pipe3:
  (t('a), operator('a, 'b), operator('b, 'c), operator('c, 'd)) =>
  observable('d) =
  "pipe";

[@bs.send]
external pipe4:
  (
    t('a),
    operator('a, 'b),
    operator('b, 'c),
    operator('c, 'd),
    operator('d, 'e)
  ) =>
  observable('e) =
  "pipe";

[@bs.send]
external pipe5:
  (
    t('a),
    operator('a, 'b),
    operator('b, 'c),
    operator('c, 'd),
    operator('d, 'e),
    operator('e, 'f)
  ) =>
  observable('f) =
  "pipe";

[@bs.send]
external pipe6:
  (
    t('a),
    operator('a, 'b),
    operator('b, 'c),
    operator('c, 'd),
    operator('d, 'e),
    operator('e, 'f),
    operator('f, 'g)
  ) =>
  observable('g) =
  "pipe";

[@bs.send]
external pipe7:
  (
    t('a),
    operator('a, 'b),
    operator('b, 'c),
    operator('c, 'd),
    operator('d, 'e),
    operator('e, 'f),
    operator('f, 'g),
    operator('g, 'h)
  ) =>
  observable('h) =
  "pipe";

[@bs.send]
external pipe8:
  (
    t('a),
    operator('a, 'b),
    operator('b, 'c),
    operator('c, 'd),
    operator('d, 'e),
    operator('e, 'f),
    operator('f, 'g),
    operator('g, 'h),
    operator('h, 'i)
  ) =>
  observable('i) =
  "pipe";

let partition:
  (t('a), ('a, int) => bool) => (observable('a), observable('a));

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

/////

[@bs.module "rxjs"] [@bs.scope "Observable"]
external create: (observer('a) => unit) => observable('a) = "create";

[@bs.module "rxjs"] [@bs.scope "Observable"]
external createWithTeardown:
  ([@bs.uncurry] ((observer('a), unit) => unit)) => observable('a) =
  "create";

[@bs.module "rxjs"] [@bs.variadic]
external of_: array('a) => observable('a) = "of";

[@bs.module "rxjs"] [@bs.variadic]
external race: array(observable('a)) => observable('a) = "race";

[@bs.module "rxjs"] external fromArray: array('a) => observable('a) = "from";

[@bs.module "rxjs"]
external fromPromise: Js.Promise.t('a) => observable('a) = "from";
[@bs.module "rxjs"]
external fromString: string => observable(string) = "from";

[@bs.module "rxjs"] external empty: observable('a) = "EMPTY";
[@bs.module "rxjs"] external never: observable('a) = "NEVER";

[@bs.module "rxjs"] external interval: int => observable(int) = "interval";

[@bs.module "rxjs"]
external zip2: (observable('a), observable('b)) => observable(('a, 'b)) =
  "zip";

[@bs.module "rxjs"]
external zip3:
  (observable('a), observable('b), observable('c)) =>
  observable(('a, 'b, 'c)) =
  "zip";

[@bs.module "rxjs"]
external zip4:
  (observable('a), observable('b), observable('c), observable('d)) =>
  observable(('a, 'b, 'c, 'd)) =
  "zip";

[@bs.module "rxjs"] [@bs.variadic]
external zip: array(observable('a)) => observable(array('a)) = "zip";

let timer:
  (
    ~delay: [ | `Int(int) | `Float(float) | `Date(Js.Date.t)]=?,
    ~period: int=?,
    unit
  ) =>
  observable(int);

[@bs.module "rxjs"]
external range: (~start: int, ~count: int) => observable(int) = "range";

[@bs.module "rxjs"]
external fromEvent: (Dom.eventTarget, string) => observable(Dom.event) =
  "fromEvent";

[@bs.module "rxjs"] [@bs.variadic]
external combineLatest: array(observable('a)) => observable(array('a)) =
  "combineLatest";

[@bs.module "rxjs"]
external combineLatest2:
  (observable('a), observable('b)) => observable(('a, 'b)) =
  "combineLatest";

[@bs.module "rxjs"]
external combineLatest3:
  (observable('a), observable('b), observable('c)) =>
  observable(('a, 'b, 'c)) =
  "combineLatest";

[@bs.module "rxjs"]
external combineLatest4:
  (observable('a), observable('b), observable('c), observable('d)) =>
  observable(('a, 'b, 'c, 'd)) =
  "combineLatest";

[@bs.module "rxjs"] [@bs.variadic]
external forkJoin: array(observable('a)) => observable(array('a)) =
  "forkJoin";

[@bs.module "rxjs"]
external forkJoin2:
  (observable('a), observable('b)) => observable(('a, 'b)) =
  "forkJoin";

[@bs.module "rxjs"]
external forkJoin3:
  (observable('a), observable('b), observable('c)) =>
  observable(('a, 'b, 'c)) =
  "forkJoin";

[@bs.module "rxjs"]
external forkJoin4:
  (observable('a), observable('b), observable('c), observable('d)) =>
  observable(('a, 'b, 'c, 'd)) =
  "forkJoin";

[@bs.module "rxjs"] [@bs.variadic]
external merge: array(observable('a)) => observable('a) = "merge";

[@bs.module "rxjs"] external throwError: 'e => observable('a) = "throwError";

[@bs.send]
external toPromise: observable('a) => Js.Promise.t('a) = "toPromise";

[@bs.module "rxjs"] [@bs.variadic]
external concat: array(observable('a)) => observable('a) = "concat";

[@bs.module "rxjs"]
external iif:
  (unit => bool, observable('a), observable('a)) => observable('a) =
  "iif";
