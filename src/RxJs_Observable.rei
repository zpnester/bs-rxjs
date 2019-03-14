open RxJs__;

type t('a) = observable('a);

let pipe: (t('a), RxJs_Operator.t('a, 'b)) => observable('b);

let pipe2:
  (t('a), RxJs_Operator.t('a, 'b), RxJs_Operator.t('b, 'c)) =>
  observable('c);
let pipe3:
  (
    t('a),
    RxJs_Operator.t('a, 'b),
    RxJs_Operator.t('b, 'c),
    RxJs_Operator.t('c, 'd)
  ) =>
  observable('d);

let pipe4:
  (
    t('a),
    RxJs_Operator.t('a, 'b),
    RxJs_Operator.t('b, 'c),
    RxJs_Operator.t('c, 'd),
    RxJs_Operator.t('d, 'e)
  ) =>
  observable('e);

let pipe5:
  (
    t('a),
    RxJs_Operator.t('a, 'b),
    RxJs_Operator.t('b, 'c),
    RxJs_Operator.t('c, 'd),
    RxJs_Operator.t('d, 'e),
    RxJs_Operator.t('e, 'f)
  ) =>
  observable('f);

let pipe6:
  (
    t('a),
    RxJs_Operator.t('a, 'b),
    RxJs_Operator.t('b, 'c),
    RxJs_Operator.t('c, 'd),
    RxJs_Operator.t('d, 'e),
    RxJs_Operator.t('e, 'f),
    RxJs_Operator.t('f, 'g)
  ) =>
  observable('g);

let pipe7:
  (
    t('a),
    RxJs_Operator.t('a, 'b),
    RxJs_Operator.t('b, 'c),
    RxJs_Operator.t('c, 'd),
    RxJs_Operator.t('d, 'e),
    RxJs_Operator.t('e, 'f),
    RxJs_Operator.t('f, 'g),
    RxJs_Operator.t('g, 'h)
  ) =>
  observable('h);

let pipe8:
  (
    t('a),
    RxJs_Operator.t('a, 'b),
    RxJs_Operator.t('b, 'c),
    RxJs_Operator.t('c, 'd),
    RxJs_Operator.t('d, 'e),
    RxJs_Operator.t('e, 'f),
    RxJs_Operator.t('f, 'g),
    RxJs_Operator.t('g, 'h),
    RxJs_Operator.t('h, 'i)
  ) =>
  observable('i);

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

let subscribeObserver: (t('a), observer('a)) => subscription;

let create: (observer('a) => unit) => observable('a);
let createWithTeardown: ((observer('a), unit) => unit) => observable('a);

[@bs.module "rxjs"] [@bs.variadic]
external of_: array('a) => observable('a) = "of";

[@bs.module "rxjs"] [@bs.variadic]
external race: array(observable('a)) => observable('a) = "race";

let fromArray: array('a) => observable('a);
let fromPromise: Js.Promise.t('a) => observable('a);
let fromString: string => observable(string);
let empty: observable('a);
let never: observable('a);
let interval: int => observable(int);

let zip2: (observable('a), observable('b)) => observable(('a, 'b));
let zip3:
  (observable('a), observable('b), observable('c)) =>
  observable(('a, 'b, 'c));

let zip4:
  (observable('a), observable('b), observable('c), observable('d)) =>
  observable(('a, 'b, 'c, 'd));

[@bs.module "rxjs"] [@bs.variadic]
external zip: array(observable('a)) => observable(array('a)) = "zip";

let timer:
  (
    ~delay: [ | `Int(int) | `Float(float) | `Date(Js.Date.t)]=?,
    ~period: int=?,
    unit
  ) =>
  observable(int);

let range: (~start: int, ~count: int) => observable(int);

let fromEvent: (Dom.eventTarget, string) => observable(Dom.event);

[@bs.module "rxjs"] [@bs.variadic]
external combineLatest: array(observable('a)) => observable(array('a)) =
  "combineLatest";

let combineLatest2:
  (observable('a), observable('b)) => observable(('a, 'b));

let combineLatest3:
  (observable('a), observable('b), observable('c)) =>
  observable(('a, 'b, 'c));

let combineLatest4:
  (observable('a), observable('b), observable('c), observable('d)) =>
  observable(('a, 'b, 'c, 'd));

[@bs.module "rxjs"] [@bs.variadic]
external forkJoin: array(observable('a)) => observable(array('a)) =
  "forkJoin";

let forkJoin2: (observable('a), observable('b)) => observable(('a, 'b));

let forkJoin3:
  (observable('a), observable('b), observable('c)) =>
  observable(('a, 'b, 'c));

let forkJoin4:
  (observable('a), observable('b), observable('c), observable('d)) =>
  observable(('a, 'b, 'c, 'd));

[@bs.module "rxjs"] [@bs.variadic]
external merge: array(observable('a)) => observable('a) = "merge";

let throwError: 'e => observable('a);

let toPromise: observable('a) => Js.Promise.t('a);

[@bs.module "rxjs"] [@bs.variadic]
external concat: array(observable('a)) => observable('a) = "concat";

let iif: (unit => bool, observable('a), observable('a)) => observable('a);
