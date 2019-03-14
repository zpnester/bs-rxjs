open RxJs__;

let map: ('a => 'b) => operator('a, 'b);

let mapi: (('a, int) => 'b) => operator('a, 'b);

let mapTo: 'b => operator('a, 'b);

let filter: ('a => bool) => operator('a, 'a);

let merge: observable('a) => operator('a, 'a);

let mergeAll: (~concurrent: int=?, unit) => operator(observable('a), 'a);

[@bs.module "rxjs/operators"] [@bs.variadic]
external concat: array(observable('a)) => operator('a, 'a) = "concat";

let concatAll: unit => operator(observable('a), 'a);

let concatAllPromises: unit => operator(Js.Promise.t('a), 'a);

let debounce: (unit => observable('b)) => operator('a, 'a);

let debounceTime: int => operator('a, 'a);

let take: int => operator('a, 'a);

let takeUntil: observable('b) => operator('a, 'a);

let takeWhile: ('a => bool) => operator('a, 'a);

let delay:
  [ | `Int(int) | `Float(float) | `Date(Js.Date.t)] => operator('a, 'a);

let delayWhen:
  (
    ('a, int) => observable('b),
    ~subscriptionDelay: observable('c)=?,
    unit
  ) =>
  operator('a, 'a);

[@bs.module "rxjs/operators"] [@bs.variadic]
external startWith: array('a) => operator('a, 'a) = "startWith";

[@bs.module "rxjs/operators"] [@bs.variadic]
external endWith: array('a) => operator('a, 'a) = "endWith";

let pairwise: unit => operator('a, ('a, 'a));

[@bs.module "rxjs/operators"] [@bs.variadic]
external withLatestFromMany:
  array(observable('a)) => operator('a, array('a)) =
  "withLatestFrom";

let withLatestFrom: observable('b) => operator('a, ('a, 'b));
let withLatestFrom2:
  (observable('b), observable('c)) => operator('a, ('a, 'b, 'c));
let withLatestFrom3:
  (observable('b), observable('c), observable('d)) =>
  operator('a, ('a, 'b, 'c, 'd));
let withLatestFrom4:
  (observable('b), observable('c), observable('d), observable('e)) =>
  operator('a, ('a, 'b, 'c, 'd, 'e));

let every: ('a => bool) => operator('a, bool);

let catchError: (Js.Json.t => observable('a)) => operator('a, 'a);

let retry: int => operator('a, 'a);

let retryWhen:
  (observable(Js.Json.t) => observable('b)) => operator('a, 'a);

let first: unit => operator('a, 'a);

let ignoreElements: unit => operator('a, 'a);

let last: unit => operator('a, 'a);

let sample: observable('b) => operator('a, 'a);

let sampleTime: int => operator('a, 'a);

let single: ('a => bool) => operator('a, 'a);

let skip: int => operator('a, 'a);

let skipUntil: observable('b) => operator('a, 'a);

let skipWhile: ('a => bool) => operator('a, 'a);

let throttle: ('a => observable('b)) => operator('a, 'a);

let throttlePromise: ('a => Js.Promise.t('b)) => operator('a, 'a);

let throttleTime: int => operator('a, 'a);

let buffer: observable('b) => operator('a, array('a));

let bufferCount: int => operator('a, array('a));

let bufferTime:
  (int, ~bufferCreationInterval: int=?, unit) => operator('a, array('a));

let bufferToggle:
  (observable('b), 'b => observable('c)) => operator('a, array('a));

let bufferWhen: (unit => observable('a)) => operator('a, array('a));

let concatMap: ('a => observable('b)) => operator('a, 'b);

let mergeMap: ('a => observable('b)) => operator('a, 'b);

let flatMap: ('a => observable('b)) => operator('a, 'b);

let flatMapi: (('a, int) => observable('b)) => operator('a, 'b);

let concatMapTo: observable('b) => operator('a, 'b);

let expand: (('a, int) => observable('b)) => operator('a, 'b);

let groupBy: ('a => 'key) => operator('a, observable('a));

let toArray: unit => operator('a, array('a));

let reduce: (('b, 'a, int) => 'b, 'b) => operator('a, 'b);

let scan: (('b, 'a, int) => 'b, 'b) => operator('a, 'b);

[@bs.module "rxjs/operators"] [@bs.variadic]
external pluck: array(string) => operator('a, Js.Json.t) = "pluck";

let switchMap: (('a, int) => observable('b)) => operator('a, 'b);

let window: observable('b) => operator('a, observable('a));

let windowCount:
  (int, ~startWindowEvery: int=?, unit) => operator('a, observable('a));

let windowToggle:
  (observable('b), 'b => observable('c)) => operator('a, observable('a));

let windowTime: int => operator('a, observable('a));

let windowWhen: (unit => observable('b)) => operator('a, observable('a));

let tap:
  (
    ~next: 'a => unit=?,
    ~error: Js.Json.t => unit=?,
    ~complete: unit => unit=?,
    unit
  ) =>
  operator('a, 'a);

let finalize: (unit => unit) => operator('a, 'a);

let repeat: int => operator('a, 'a);

let timeout:
  [ | `Int(int) | `Float(float) | `Date(Js.Date.t)] => operator('a, 'a);

let timeoutWith:
  ([ | `Int(int) | `Float(float) | `Date(Js.Date.t)], observable('a)) =>
  operator('a, 'a);

let combineAll: unit => operator(observable('a), array('a));

let defaultIfEmpty: 'a => operator('a, 'a);

let sequenceEqual: observable('a) => operator('a, bool);

let multicast:
  [ | `Subject(subject('a)) | `Factory(unit => subject('a))] =>
  operator('a, 'a);

let share: unit => operator('a, 'a);

let shareReplay:
  (~bufferSize: int=?, ~windowTime: int=?, unit) => operator('a, 'a);

let publish: unit => operator('a, 'a);

let publishBehavior: 'a => operator('a, 'a);

let publishLast: unit => operator('a, 'a);

let publishReplay:
  (~bufferSize: int=?, ~windowTime: int=?, unit) => operator('a, 'a);

let audit: ('a => observable('b)) => operator('a, 'a);

let auditTime: int => operator('a, 'a);

let exhaust: unit => operator(observable('a), 'a);

let exhaustMap:
  (
    ('a, int) => observable('b),
    ~resultSelector: (
                       ~outerValue: 'a,
                       ~innerValue: 'b,
                       ~outerIndex: int,
                       ~innerIndex: int
                     ) =>
                     'c
                       =?,
    unit
  ) =>
  operator('a, 'c);

let elementAt: (int, ~defaultValue: 'a=?, unit) => operator('a, 'a);

let find: (('a, int, observable('a)) => bool) => operator('a, option('a));

let findIndex: (('a, int, observable('a)) => bool) => operator('a, int);

let isEmpty: unit => operator('a, bool);

let max: (('a, 'a) => float) => operator('a, 'a);
let min: (('a, 'a) => float) => operator('a, 'a);

let switchAll: unit => operator(observable('a), 'a);

let onErrorResumeNext: array(observable('a)) => operator('a, 'a);

let refCount: unit => operator('a, 'a);

let throwIfEmpty: (~errorFactory: unit => unit=?, unit) => operator('a, 'a);

let timestamp:
  unit =>
  operator(
    'a,
    {
      .
      "timestamp": float,
      "value": 'a,
    },
  );

let distinctUntilChanged:
  (~compare: ('a, 'a) => bool=?, unit) => operator('a, 'a);
