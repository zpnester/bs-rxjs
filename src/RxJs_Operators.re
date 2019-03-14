open RxJs__;

[@bs.module "rxjs/operators"]
external map: ('a => 'b) => operator('a, 'b) = "map";

[@bs.module "rxjs/operators"]
external mapi: (('a, int) => 'b) => operator('a, 'b) = "map";

[@bs.module "rxjs/operators"]
external mapTo: 'b => operator('a, 'b) = "mapTo";

[@bs.module "rxjs/operators"]
external filter: ('a => bool) => operator('a, 'a) = "filter";

[@bs.module "rxjs/operators"]
external merge: observable('a) => operator('a, 'a) = "merge";

[@bs.module "rxjs/operators"]
external mergeAll: (~concurrent: int=?, unit) => operator(observable('a), 'a) =
  "mergeAll";

[@bs.module "rxjs/operators"] [@bs.variadic]
external concat: array(observable('a)) => operator('a, 'a) = "concat";

[@bs.module "rxjs/operators"]
external concatAll: unit => operator(observable('a), 'a) = "concatAll";

[@bs.module "rxjs/operators"]
external concatAllPromises: unit => operator(Js.Promise.t('a), 'a) =
  "concatAll";

/* 'b not used */
[@bs.module "rxjs/operators"]
external debounce: (unit => observable('b)) => operator('a, 'a) = "debounce";

[@bs.module "rxjs/operators"]
external debounceTime: int => operator('a, 'a) = "debounceTime";

[@bs.module "rxjs/operators"] external take: int => operator('a, 'a) = "take";

[@bs.module "rxjs/operators"]
external takeUntil: observable('b) => operator('a, 'a) = "takeUntil";

[@bs.module "rxjs/operators"]
external takeWhile: ('a => bool) => operator('a, 'a) = "takeWhile";

[@bs.module "rxjs/operators"]
external delay:
  ([@bs.unwrap] [ | `Int(int) | `Float(float) | `Date(Js.Date.t)]) =>
  operator('a, 'a) =
  "delay";

[@bs.module "rxjs/operators"]
external delayWhen:
  (
    ('a, int) => observable('b),
    ~subscriptionDelay: observable('c)=?,
    unit
  ) =>
  operator('a, 'a) =
  "delayWhen";

[@bs.module "rxjs/operators"] [@bs.variadic]
external startWith: array('a) => operator('a, 'a) = "startWith";

[@bs.module "rxjs/operators"] [@bs.variadic]
external endWith: array('a) => operator('a, 'a) = "endWith";

[@bs.module "rxjs/operators"]
external pairwise: unit => operator('a, ('a, 'a)) = "pairwise";

[@bs.module "rxjs/operators"] [@bs.variadic]
external withLatestFromMany:
  array(observable('a)) => operator('a, array('a)) =
  "withLatestFrom";

[@bs.module "rxjs/operators"]
external withLatestFrom: observable('b) => operator('a, ('a, 'b)) =
  "withLatestFrom";

[@bs.module "rxjs/operators"]
external withLatestFrom2:
  (observable('b), observable('c)) => operator('a, ('a, 'b, 'c)) =
  "withLatestFrom";

[@bs.module "rxjs/operators"]
external withLatestFrom3:
  (observable('b), observable('c), observable('d)) =>
  operator('a, ('a, 'b, 'c, 'd)) =
  "withLatestFrom";

[@bs.module "rxjs/operators"]
external withLatestFrom4:
  (observable('b), observable('c), observable('d), observable('e)) =>
  operator('a, ('a, 'b, 'c, 'd, 'e)) =
  "withLatestFrom";

[@bs.module "rxjs/operators"]
external every: ('a => bool) => operator('a, bool) = "every";

[@bs.module "rxjs/operators"]
external catchError: (Js.Json.t => observable('a)) => operator('a, 'a) =
  "catchError";

[@bs.module "rxjs/operators"]
external retry: int => operator('a, 'a) = "retry";

/* 'b not used */
[@bs.module "rxjs/operators"]
external retryWhen:
  (observable(Js.Json.t) => observable('b)) => operator('a, 'a) =
  "retryWhen";

[@bs.module "rxjs/operators"]
external first: unit => operator('a, 'a) = "first";

[@bs.module "rxjs/operators"]
external ignoreElements: unit => operator('a, 'a) = "ignoreElements";

[@bs.module "rxjs/operators"]
external last: unit => operator('a, 'a) = "last";

/* 'b not used */
[@bs.module "rxjs/operators"]
external sample: observable('b) => operator('a, 'a) = "sample";

/* 'b not used */
[@bs.module "rxjs/operators"]
external sampleTime: int => operator('a, 'a) = "sampleTime";

[@bs.module "rxjs/operators"]
external single: ('a => bool) => operator('a, 'a) = "single";

[@bs.module "rxjs/operators"] external skip: int => operator('a, 'a) = "skip";

/* 'b not used */
[@bs.module "rxjs/operators"]
external skipUntil: observable('b) => operator('a, 'a) = "skipUntil";

[@bs.module "rxjs/operators"]
external skipWhile: ('a => bool) => operator('a, 'a) = "skipWhile";

[@bs.module "rxjs/operators"]
external throttle: ('a => observable('b)) => operator('a, 'a) = "throttle";

[@bs.module "rxjs/operators"]
external throttlePromise: ('a => Js.Promise.t('b)) => operator('a, 'a) =
  "throttle";

[@bs.module "rxjs/operators"]
external throttleTime: int => operator('a, 'a) = "throttleTime";

[@bs.module "rxjs/operators"]
external buffer: observable('b) => operator('a, array('a)) = "buffer";

[@bs.module "rxjs/operators"]
external bufferCount: int => operator('a, array('a)) = "bufferCount";

[@bs.module "rxjs/operators"]
external bufferTime:
  (int, ~bufferCreationInterval: int=?, unit) => operator('a, array('a)) =
  "bufferTime";

/* TODO promise, bs.unwrap is not enough */
[@bs.module "rxjs/operators"]
external bufferToggle:
  (observable('b), 'b => observable('c)) => operator('a, array('a)) =
  "bufferToggle";

[@bs.module "rxjs/operators"]
external bufferWhen: (unit => observable('a)) => operator('a, array('a)) =
  "bufferWhen";

[@bs.module "rxjs/operators"]
external concatMap: ('a => observable('b)) => operator('a, 'b) = "concatMap";

[@bs.module "rxjs/operators"]
external mergeMap: ('a => observable('b)) => operator('a, 'b) = "mergeMap";

/* TODO result selector */
[@bs.module "rxjs/operators"]
external flatMap: ('a => observable('b)) => operator('a, 'b) = "flatMap";

[@bs.module "rxjs/operators"]
external flatMapi: (('a, int) => observable('b)) => operator('a, 'b) =
  "flatMap";

[@bs.module "rxjs/operators"]
external concatMapTo: observable('b) => operator('a, 'b) = "concatMapTo";

/* concurrent TODO */
[@bs.module "rxjs/operators"]
external expand: (('a, int) => observable('b)) => operator('a, 'b) =
  "expand";

/* TODO 3 more optional params */
[@bs.module "rxjs/operators"]
external groupBy: ('a => 'key) => operator('a, observable('a)) = "groupBy";

[@bs.module "rxjs/operators"]
external toArray: unit => operator('a, array('a)) = "toArray";

[@bs.module "rxjs/operators"]
external reduce: (('b, 'a, int) => 'b, 'b) => operator('a, 'b) = "reduce";

[@bs.module "rxjs/operators"]
external scan: (('b, 'a, int) => 'b, 'b) => operator('a, 'b) = "scan";

/* partition moved to Observable */

[@bs.module "rxjs/operators"] [@bs.variadic]
external pluck: array(string) => operator('a, Js.Json.t) = "pluck";

/* TODO result selector */
[@bs.module "rxjs/operators"]
external switchMap: (('a, int) => observable('b)) => operator('a, 'b) =
  "switchMap";

[@bs.module "rxjs/operators"]
external window: observable('b) => operator('a, observable('a)) = "window";

[@bs.module "rxjs/operators"]
external windowCount:
  (int, ~startWindowEvery: int=?, unit) => operator('a, observable('a)) =
  "windowCount";

/* 'c not used */
[@bs.module "rxjs/operators"]
external windowToggle:
  (observable('b), 'b => observable('c)) => operator('a, observable('a)) =
  "windowToggle";

[@bs.module "rxjs/operators"]
external windowTime: int => operator('a, observable('a)) = "windowTime";

[@bs.module "rxjs/operators"]
external windowWhen:
  (unit => observable('b)) => operator('a, observable('a)) =
  "windowWhen";

/* TODO observer */
[@bs.module "rxjs/operators"]
external tap:
  (
    ~next: 'a => unit=?,
    ~error: Js.Json.t => unit=?,
    ~complete: unit => unit=?,
    unit
  ) =>
  operator('a, 'a) =
  "tap";

/* TODO Notification */
/* dematerialize skipped, Notification impl required */

[@bs.module "rxjs/operators"]
external finalize: (unit => unit) => operator('a, 'a) = "finalize";

[@bs.module "rxjs/operators"]
external repeat: int => operator('a, 'a) = "repeat";

[@bs.module "rxjs/operators"]
external timeout:
  ([@bs.unwrap] [ | `Int(int) | `Float(float) | `Date(Js.Date.t)]) =>
  operator('a, 'a) =
  "timeout";

[@bs.module "rxjs/operators"]
external timeoutWith:
  (
    [@bs.unwrap] [ | `Int(int) | `Float(float) | `Date(Js.Date.t)],
    observable('a)
  ) =>
  operator('a, 'a) =
  "timeoutWith";

[@bs.module "rxjs/operators"]
external combineAll: unit => operator(observable('a), array('a)) =
  "combineAll";

[@bs.module "rxjs/operators"]
external defaultIfEmpty: 'a => operator('a, 'a) = "defaultIfEmpty";

[@bs.module "rxjs/operators"]
external sequenceEqual: observable('a) => operator('a, bool) =
  "sequenceEqual";

[@bs.module "rxjs/operators"]
external multicast:
  (
  [@bs.unwrap]
  [ | `Subject(subject('a)) | `Factory(unit => subject('a))]
  ) =>
  operator('a, 'a) =
  "multicast";

[@bs.module "rxjs/operators"]
external share: unit => operator('a, 'a) = "share";

[@bs.module "rxjs/operators"]
external shareReplay:
  (~bufferSize: int=?, ~windowTime: int=?, unit) => operator('a, 'a) =
  "shareReplay";

/* TODO selector */
[@bs.module "rxjs/operators"]
external publish: unit => operator('a, 'a) = "publish";

[@bs.module "rxjs/operators"]
external publishBehavior: 'a => operator('a, 'a) = "publishBehavior";

[@bs.module "rxjs/operators"]
external publishLast: unit => operator('a, 'a) = "publishLast";

/* TODO selector */
[@bs.module "rxjs/operators"]
external publishReplay:
  (~bufferSize: int=?, ~windowTime: int=?, unit) => operator('a, 'a) =
  "publishReplay";

/* 'b not used */
[@bs.module "rxjs/operators"]
external audit: ('a => observable('b)) => operator('a, 'a) = "audit";

[@bs.module "rxjs/operators"]
external auditTime: int => operator('a, 'a) = "auditTime";

[@bs.module "rxjs/operators"]
external exhaust: unit => operator(observable('a), 'a) = "exhaust";

[@bs.module "rxjs/operators"]
external exhaustMap:
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
  operator('a, 'c) =
  "exhaustMap";

[@bs.module "rxjs/operators"]
external elementAt: (int, ~defaultValue: 'a=?, unit) => operator('a, 'a) =
  "elementAt";

[@bs.module "rxjs/operators"]
external find_:
  (('a, int, observable('a)) => bool) => operator('a, Js.Undefined.t('a)) =
  "find";

let find = (predicate: ('a, int, observable('a)) => bool) =>
  RxJs_Operator.make(src =>
    src->RxJs_Observable.pipe2(find_(predicate), map(Js.Undefined.toOption))
  );

[@bs.module "rxjs/operators"]
external findIndex: (('a, int, observable('a)) => bool) => operator('a, int) =
  "findIndex";

[@bs.module "rxjs/operators"]
external isEmpty: unit => operator('a, bool) = "isEmpty";

[@bs.module "rxjs/operators"]
external max: (('a, 'a) => float) => operator('a, 'a) = "max";

[@bs.module "rxjs/operators"]
external min: (('a, 'a) => float) => operator('a, 'a) = "min";

[@bs.module "rxjs/operators"]
external switchAll: unit => operator(observable('a), 'a) = "switchAll";

[@bs.module "rxjs/operators"]
external onErrorResumeNext: array(observable('a)) => operator('a, 'a) =
  "onErrorResumeNext";

[@bs.module "rxjs/operators"]
external refCount: unit => operator('a, 'a) = "refCount";

[@bs.module "rxjs/operators"]
external throwIfEmpty:
  (~errorFactory: unit => unit=?, unit) => operator('a, 'a) =
  "throwIfEmpty";

[@bs.module "rxjs/operators"]
external timestamp:
  unit =>
  operator(
    'a,
    {
      .
      "timestamp": float,
      "value": 'a,
    },
  ) =
  "timestamp";

/* keySelector skipped for type safety */
[@bs.module "rxjs/operators"]
external distinctUntilChanged:
  (~compare: ('a, 'a) => bool=?, unit) => operator('a, 'a) =
  "distinctUntilChanged";
/* distinctUntilKeyChanged skipped for type safety */
