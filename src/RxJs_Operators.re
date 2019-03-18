open RxJs__;

[@bs.module "rxjs/operators"]
external map: ('a => 'b) => operatorFunction('a, 'b) = "map";

[@bs.module "rxjs/operators"]
external mapi: (('a, int) => 'b) => operatorFunction('a, 'b) = "map";

[@bs.module "rxjs/operators"]
external mapTo: 'b => operatorFunction('a, 'b) = "mapTo";

[@bs.module "rxjs/operators"]
external filter: ('a => bool) => operatorFunction('a, 'a) = "filter";

[@bs.module "rxjs/operators"]
external filteri: (('a, int) => bool) => operatorFunction('a, 'a) = "filter";

[@bs.module "rxjs/operators"]
external mergeAll:
  (~concurrent: int=?, unit) => operatorFunction(observable('a), 'a) =
  "mergeAll";

[@bs.module "rxjs/operators"]
external concatAll: unit => operatorFunction(observable('a), 'a) =
  "concatAll";

[@bs.module "rxjs/operators"]
external concatAllP: unit => operatorFunction(Js.Promise.t('a), 'a) =
  "concatAll";

/* 'b not used */
[@bs.module "rxjs/operators"]
external debounce: (unit => observable('b)) => operatorFunction('a, 'a) =
  "debounce";

[@bs.module "rxjs/operators"]
external debounceP: (unit => Js.Promise.t('b)) => operatorFunction('a, 'a) =
  "debounce";

[@bs.module "rxjs/operators"]
external debounceTime: float => operatorFunction('a, 'a) = "debounceTime";

[@bs.module "rxjs/operators"]
external debounceTimeS: (float, scheduler) => operatorFunction('a, 'a) =
  "debounceTime";

[@bs.module "rxjs/operators"]
external take: int => operatorFunction('a, 'a) = "take";

[@bs.module "rxjs/operators"]
external takeUntil: observable('b) => operatorFunction('a, 'a) = "takeUntil";

[@bs.module "rxjs/operators"]
external takeWhile: ('a => bool) => operatorFunction('a, 'a) = "takeWhile";

[@bs.module "rxjs/operators"]
external takeWhilei: (('a, int) => bool) => operatorFunction('a, 'a) =
  "takeWhile";

[@bs.module "rxjs/operators"]
external delay:
  ([@bs.unwrap] [ | `Number(float) | `Date(Js.Date.t)]) =>
  operatorFunction('a, 'a) =
  "delay";

[@bs.module "rxjs/operators"]
external delayS:
  ([@bs.unwrap] [ | `Number(float) | `Date(Js.Date.t)], scheduler) =>
  operatorFunction('a, 'a) =
  "delay";

// 'b
[@bs.module "rxjs/operators"]
external delayWhen:
  (
    ('a, int) => observable('b),
    ~subscriptionDelay: observable('c)=?,
    unit
  ) =>
  operatorFunction('a, 'a) =
  "delayWhen";

[@bs.module "rxjs/operators"] [@bs.variadic]
external startWith: array('a) => operatorFunction('a, 'a) = "startWith";

[@bs.module "rxjs/operators"]
external startWith1S: ('a, scheduler) => operatorFunction('a, 'a) =
  "startWith";

[@bs.module "rxjs/operators"]
external startWith2S: ('a, 'a, scheduler) => operatorFunction('a, 'a) =
  "startWith";

[@bs.module "rxjs/operators"]
external startWith3S: ('a, 'a, 'a, scheduler) => operatorFunction('a, 'a) =
  "startWith";

[@bs.module "rxjs/operators"]
external startWith4S: ('a, 'a, 'a, 'a, scheduler) => operatorFunction('a, 'a) =
  "startWith";

[@bs.module "rxjs/operators"] [@bs.variadic]
external endWith: array('a) => operatorFunction('a, 'a) = "endWith";

[@bs.module "rxjs/operators"]
external endWith1S: ('a, scheduler) => operatorFunction('a, 'a) = "endWith";

[@bs.module "rxjs/operators"]
external endWith2S: ('a, 'a, scheduler) => operatorFunction('a, 'a) =
  "endWith";

[@bs.module "rxjs/operators"]
external endWith3S: ('a, 'a, 'a, scheduler) => operatorFunction('a, 'a) =
  "endWith";

[@bs.module "rxjs/operators"]
external endWith4S:
  ('a, 'a, 'a, 'a, scheduler, unit) => operatorFunction('a, 'a) =
  "endWith";

[@bs.module "rxjs/operators"]
external pairwise: unit => operatorFunction('a, ('a, 'a)) = "pairwise";

[@bs.module "rxjs/operators"] [@bs.variadic]
external withLatestFrom:
  array(observable('a)) => operatorFunction('a, array('a)) =
  "withLatestFrom";

[@bs.module "rxjs/operators"]
external withLatestFrom1: observable('b) => operatorFunction('a, ('a, 'b)) =
  "withLatestFrom";

[@bs.module "rxjs/operators"]
external withLatestFrom2:
  (observable('b), observable('c)) => operatorFunction('a, ('a, 'b, 'c)) =
  "withLatestFrom";

[@bs.module "rxjs/operators"]
external withLatestFrom3:
  (observable('b), observable('c), observable('d)) =>
  operatorFunction('a, ('a, 'b, 'c, 'd)) =
  "withLatestFrom";

[@bs.module "rxjs/operators"]
external withLatestFrom4:
  (observable('b), observable('c), observable('d), observable('e)) =>
  operatorFunction('a, ('a, 'b, 'c, 'd, 'e)) =
  "withLatestFrom";

[@bs.module "rxjs/operators"]
external every: ('a => bool) => operatorFunction('a, bool) = "every";

[@bs.module "rxjs/operators"]
external catchError:
  ((Js.Json.t, observable('a)) => observable('a)) =>
  operatorFunction('a, 'a) =
  "catchError";

[@bs.module "rxjs/operators"]
external retry: (~count: int=?, unit) => operatorFunction('a, 'a) = "retry";

/* 'b not used */
[@bs.module "rxjs/operators"]
external retryWhen:
  (observable(Js.Json.t) => observable('b)) => operatorFunction('a, 'a) =
  "retryWhen";

[@bs.module "rxjs/operators"]
external first: (~predicate: 'a => bool=?, 'a) => operatorFunction('a, 'a) =
  "first";

[@bs.module "rxjs/operators"]
external firsti:
  (~predicate: ('a, int, observable('a)) => bool=?, 'a) =>
  operatorFunction('a, 'a) =
  "first";

[@bs.module "rxjs/operators"]
external ignoreElements: unit => operatorFunction('a, 'a) = "ignoreElements";

[@bs.module "rxjs/operators"]
external last: (~predicate: 'a => bool=?, 'a) => operatorFunction('a, 'a) =
  "last";

[@bs.module "rxjs/operators"]
external lasti:
  (~predicate: ('a, int, observable('a)) => bool=?, 'a) =>
  operatorFunction('a, 'a) =
  "last";

/* 'b not used */
[@bs.module "rxjs/operators"]
external sample: observable('b) => operatorFunction('a, 'a) = "sample";

[@bs.module "rxjs/operators"]
external sampleTime: float => operatorFunction('a, 'a) = "sampleTime";

[@bs.module "rxjs/operators"]
external sampleTimeS: (float, scheduler) => operatorFunction('a, 'a) =
  "sampleTime";

[@bs.module "rxjs/operators"]
external single: ('a => bool) => operatorFunction('a, 'a) = "single";

[@bs.module "rxjs/operators"]
external singlei:
  (('a, int, observable('a)) => bool) => operatorFunction('a, 'a) =
  "single";

[@bs.module "rxjs/operators"]
external skip: int => operatorFunction('a, 'a) = "skip";

/* 'b not used */
[@bs.module "rxjs/operators"]
external skipUntil: observable('b) => operatorFunction('a, 'a) = "skipUntil";

[@bs.module "rxjs/operators"]
external skipWhile: ('a => bool) => operatorFunction('a, 'a) = "skipWhile";

[@bs.module "rxjs/operators"]
external skipWhilei: (('a, int) => bool) => operatorFunction('a, 'a) =
  "skipWhile";

[@bs.module "rxjs/operators"]
external throttle: ('a => observable('b)) => operatorFunction('a, 'a) =
  "throttle";

[@bs.module "rxjs/operators"]
external throttleP:
  (
    'a => Js.Promise.t('b),
    ~config: {
               .
               "leading": bool,
               "trailing": bool,
             }
               =?,
    unit
  ) =>
  operatorFunction('a, 'a) =
  "throttle";

[@bs.module "rxjs/operators"]
external throttleTime:
  (
    float,
    ~scheduler: scheduler=?,
    ~config: {
               .
               "leading": bool,
               "trailing": bool,
             }
               =?,
    unit
  ) =>
  operatorFunction('a, 'a) =
  "throttleTime";

[@bs.module "rxjs/operators"]
external buffer: observable('b) => operatorFunction('a, array('a)) =
  "buffer";

[@bs.module "rxjs/operators"]
external bufferCount:
  (int, ~startBufferEvery: float=?, unit) => operatorFunction('a, array('a)) =
  "bufferCount";

[@bs.module "rxjs/operators"]
external bufferTime:
  (
    float,
    ~bufferCreationInterval: int=?,
    ~maxBufferSize: int=?,
    ~scheduler: RxJs_Scheduler.t=?,
    unit
  ) =>
  operatorFunction('a, array('a)) =
  "bufferTime";

[@bs.module "rxjs/operators"]
external bufferToggle:
  (observable('b), 'b => observable('c)) => operatorFunction('a, array('a)) =
  "bufferToggle";

[@bs.module "rxjs/operators"]
external bufferToggleP:
  (Js.Promise.t('b), 'b => Js.Promise.t('c)) =>
  operatorFunction('a, array('a)) =
  "bufferToggle";

[@bs.module "rxjs/operators"]
external bufferWhen:
  (unit => observable('b)) => operatorFunction('a, array('a)) =
  "bufferWhen";

// resultSelector deprecated
[@bs.module "rxjs/operators"]
external concatMap: ('a => observable('b)) => operatorFunction('a, 'b) =
  "concatMap";

[@bs.module "rxjs/operators"]
external concatMapi:
  (('a, int) => observable('b)) => operatorFunction('a, 'b) =
  "concatMap";

[@bs.module "rxjs/operators"]
external mergeMap:
  ('a => observable('b), ~concurrent: int=?, unit) =>
  operatorFunction('a, 'b) =
  "mergeMap";

[@bs.module "rxjs/operators"]
external mergeMapi:
  (('a, int) => observable('b), ~concurrent: int=?, unit) =>
  operatorFunction('a, 'b) =
  "mergeMap";

// resultSelector is deprecated

[@bs.module "rxjs/operators"]
external flatMap:
  ('a => observable('b), ~concurrent: int=?, unit) =>
  operatorFunction('a, 'b) =
  "flatMap";

[@bs.module "rxjs/operators"]
external flatMapi:
  (('a, int) => observable('b), ~concurrent: int=?, unit) =>
  operatorFunction('a, 'b) =
  "flatMap";

[@bs.module "rxjs/operators"]
external concatMapTo: observable('b) => operatorFunction('a, 'b) =
  "concatMapTo";

[@bs.module "rxjs/operators"]
external expand:
  ('a => observable('b), ~concurrent: int=?, ~scheduler: scheduler=?, unit) =>
  operatorFunction('a, 'b) =
  "expand";

[@bs.module "rxjs/operators"]
external expandi:
  (
    ('a, int) => observable('b),
    ~concurrent: int=?,
    ~scheduler: scheduler=?,
    unit
  ) =>
  operatorFunction('a, 'b) =
  "expand";

/* TODO 3 more optional params */
[@bs.module "rxjs/operators"]
external groupBy: ('a => 'key) => operatorFunction('a, observable('a)) =
  "groupBy";

[@bs.module "rxjs/operators"]
external toArray: unit => operatorFunction('a, array('a)) = "toArray";

[@bs.module "rxjs/operators"]
external reduce: ('b, 'a => 'b, 'b) => operatorFunction('a, 'b) = "reduce";

[@bs.module "rxjs/operators"]
external reducei: (('b, 'a, int) => 'b, 'b) => operatorFunction('a, 'b) =
  "reduce";

[@bs.module "rxjs/operators"]
external scan: (('b, 'a) => 'b, 'b) => operatorFunction('a, 'b) = "scan";

[@bs.module "rxjs/operators"]
external scani: (('b, 'a, int) => 'b, 'b) => operatorFunction('a, 'b) =
  "scan";

/* partition moved to Observable */

[@bs.module "rxjs/operators"] [@bs.variadic]
external pluck: array(string) => operatorFunction('a, Js.Json.t) = "pluck";

/* result selector is deprecated */
[@bs.module "rxjs/operators"]
external switchMap: ('a => observable('b)) => operatorFunction('a, 'b) =
  "switchMap";

[@bs.module "rxjs/operators"]
external switchMapi:
  (('a, int) => observable('b)) => operatorFunction('a, 'b) =
  "switchMap";

[@bs.module "rxjs/operators"]
external switchMapTo: observable('a) => operatorFunction('a, 'a) =
  "switchMapTo";

[@bs.module "rxjs/operators"]
external window: observable('b) => operatorFunction('a, observable('a)) =
  "window";

[@bs.module "rxjs/operators"]
external windowCount:
  (int, ~startWindowEvery: int=?, unit) =>
  operatorFunction('a, observable('a)) =
  "windowCount";

/* 'c not used */
[@bs.module "rxjs/operators"]
external windowToggle:
  (observable('b), 'b => observable('c)) =>
  operatorFunction('a, observable('a)) =
  "windowToggle";

[@bs.module "rxjs/operators"]
external windowTime: int => operatorFunction('a, observable('a)) =
  "windowTime";

[@bs.module "rxjs/operators"]
external windowTimeS:
  (float, scheduler) => operatorFunction('a, observable('a)) =
  "windowTime";

[@bs.module "rxjs/operators"]
external windowWhen:
  (unit => observable('b)) => operatorFunction('a, observable('a)) =
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
  operatorFunction('a, 'a) =
  "tap";

[@bs.module "rxjs/operators"]
external tapWithObserver: observer('a) => operatorFunction('a, 'a) = "tap";

/* TODO Notification */
/* dematerialize skipped, Notification impl required */

[@bs.module "rxjs/operators"]
external finalize: (unit => unit) => operatorFunction('a, 'a) = "finalize";

[@bs.module "rxjs/operators"]
external repeat: int => operatorFunction('a, 'a) = "repeat";

[@bs.module "rxjs/operators"]
external timeout:
  ([@bs.unwrap] [ | `Number(float) | `Date(Js.Date.t)]) =>
  operatorFunction('a, 'a) =
  "timeout";

[@bs.module "rxjs/operators"]
external timeoutS:
  ([@bs.unwrap] [ | `Number(float) | `Date(Js.Date.t)], scheduler) =>
  operatorFunction('a, 'a) =
  "timeout";

[@bs.module "rxjs/operators"]
external timeoutWith:
  ([@bs.unwrap] [ | `Number(float) | `Date(Js.Date.t)], observable('a)) =>
  operatorFunction('a, 'a) =
  "timeoutWith";

[@bs.module "rxjs/operators"]
external timeoutWithS:
  (
    [@bs.unwrap] [ | `Number(float) | `Date(Js.Date.t)],
    observable('a),
    scheduler
  ) =>
  operatorFunction('a, 'a) =
  "timeoutWith";

[@bs.module "rxjs/operators"]
external combineAll: unit => operatorFunction(observable('a), array('a)) =
  "combineAll";

[@bs.module "rxjs/operators"]
external defaultIfEmpty: 'a => operatorFunction('a, 'a) = "defaultIfEmpty";

[@bs.module "rxjs/operators"]
external sequenceEqual:
  (observable('a), ~comparator: ('a, 'a) => bool=?, unit) =>
  operatorFunction('a, bool) =
  "sequenceEqual";

[@bs.module "rxjs/operators"]
external multicast:
  (
  [@bs.unwrap]
  [ | `Subject(subject('a)) | `Factory(unit => subject('a))]
  ) =>
  operatorFunction('a, 'a) =
  "multicast";

// TODO possibly not type safe
[@bs.module "rxjs/operators"]
external multicastS:
  (
    [@bs.unwrap] [ | `Subject(subject('a)) | `Factory(unit => subject('a))],
    observable('a) => observable('b)
  ) =>
  operatorFunction('a, 'b) =
  "multicast";

[@bs.module "rxjs/operators"]
external share: unit => operatorFunction('a, 'a) = "share";

[@bs.module "rxjs/operators"]
external shareReplay:
  (
    ~bufferSize: float=?,
    ~windowTime: float=?,
    ~scheduler: scheduler=?,
    unit
  ) =>
  operatorFunction('a, 'a) =
  "shareReplay";

[@bs.module "rxjs/operators"]
external shareReplayC:
  {
    .
    "bufferSize": float,
    "windowTime": float,
    "refCount": bool,
    "scheduler": scheduler,
  } =>
  operatorFunction('a, 'a) =
  "shareReplay";

[@bs.module "rxjs/operators"]
external publish: unit => operatorFunction('a, 'a) = "publish";

[@bs.module "rxjs/operators"]
external publishS: operatorFunction('a, 'b) => operatorFunction('a, 'a) =
  "publish";

// TODO connectable
[@bs.module "rxjs/operators"]
external publishBehavior: 'a => operatorFunction('a, 'a) = "publishBehavior";

// TODO connectable
[@bs.module "rxjs/operators"]
external publishLast: unit => operatorFunction('a, 'a) = "publishLast";

[@bs.module "rxjs/operators"]
external publishReplay:
  (~bufferSize: int=?, ~windowTime: float=?, ~scheduler: scheduler=?, unit) =>
  operatorFunction('a, 'a) =
  "publishReplay";

[@bs.module "rxjs/operators"]
external publishReplayS:
  (
    ~bufferSize: int=?,
    ~windowTime: float=?,
    operatorFunction('a, 'b),
    ~scheduler: scheduler=?,
    unit
  ) =>
  operatorFunction('a, 'b) =
  "publishReplay";

/* 'b not used */
[@bs.module "rxjs/operators"]
external audit: ('a => observable('b)) => operatorFunction('a, 'a) = "audit";

[@bs.module "rxjs/operators"]
external auditP: ('a => Js.Promise.t('b)) => operatorFunction('a, 'a) =
  "audit";

[@bs.module "rxjs/operators"]
external auditTime: float => operatorFunction('a, 'a) = "auditTime";

[@bs.module "rxjs/operators"]
external auditTimeS: (float, RxJs_Scheduler.t) => operatorFunction('a, 'a) =
  "auditTime";

// TODO types OK?
[@bs.module "rxjs/operators"]
external exhaust: unit => operatorFunction(observable('a), 'a) = "exhaust";

[@bs.module "rxjs/operators"]
external exhaustMap:
  (
    'a => observable('b),
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
  operatorFunction('a, 'c) =
  "exhaustMap";

[@bs.module "rxjs/operators"]
external exhaustMapi:
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
  operatorFunction('a, 'c) =
  "exhaustMap";

// TODO check if returns nulls on errors
[@bs.module "rxjs/operators"]
external elementAt:
  (int, ~defaultValue: 'a=?, unit) => operatorFunction('a, 'a) =
  "elementAt";

[@bs.module "rxjs/operators"]
external find_: ('a => bool) => operatorFunction('a, Js.Undefined.t('a)) =
  "find";

[@bs.module "rxjs/operators"]
external findi_:
  (('a, int, observable('a)) => bool) =>
  operatorFunction('a, Js.Undefined.t('a)) =
  "find";

let find = (predicate: 'a => bool) =>
  RxJs_OperatorFunction.make(src =>
    src->RxJs_Observable.pipe2(find_(predicate), map(Js.Undefined.toOption))
  );

let findi = (predicate: ('a, int, observable('a)) => bool) =>
  RxJs_OperatorFunction.make(src =>
    src->RxJs_Observable.pipe2(
      findi_(predicate),
      map(Js.Undefined.toOption),
    )
  );

[@bs.module "rxjs/operators"]
external findIndex: ('a => bool) => operatorFunction('a, int) = "findIndex";

[@bs.module "rxjs/operators"]
external findIndexi:
  (('a, int, observable('a)) => bool) => operatorFunction('a, int) =
  "findIndex";
[@bs.module "rxjs/operators"]
external isEmpty: unit => operatorFunction('a, bool) = "isEmpty";

[@bs.module "rxjs/operators"]
external max: unit => operatorFunction('a, 'a) = "max";

[@bs.module "rxjs/operators"]
external maxC: (('a, 'a) => float) => operatorFunction('a, 'a) = "max";

[@bs.module "rxjs/operators"]
external min: unit => operatorFunction('a, 'a) = "min";

[@bs.module "rxjs/operators"]
external minC: (('a, 'a) => float) => operatorFunction('a, 'a) = "min";

[@bs.module "rxjs/operators"]
external switchAll: unit => operatorFunction(observable('a), 'a) =
  "switchAll";

[@bs.module "rxjs/operators"]
external onErrorResumeNext:
  array(observable('a)) => operatorFunction('a, 'a) =
  "onErrorResumeNext";

[@bs.module "rxjs/operators"]
external refCount: unit => operatorFunction('a, 'a) = "refCount";

[@bs.module "rxjs/operators"]
external throwIfEmpty:
  (~errorFactory: unit => unit=?, unit) => operatorFunction('a, 'a) =
  "throwIfEmpty";

[@bs.module "rxjs/operators"]
external timestamp:
  unit =>
  operatorFunction(
    'a,
    {
      .
      "timestamp": float,
      "value": 'a,
    },
  ) =
  "timestamp";

[@bs.module "rxjs/operators"]
external timestampS:
  scheduler =>
  operatorFunction(
    'a,
    {
      .
      "timestamp": float,
      "value": 'a,
    },
  ) =
  "timestamp";

/* keySelector skipped */
[@bs.module "rxjs/operators"]
external distinctUntilChanged:
  (~compare: ('a, 'a) => bool=?, unit) => operatorFunction('a, 'a) =
  "distinctUntilChanged";
/* distinctUntilKeyChanged skipped  */

[@bs.module "rxjs/operators"]
external observeOn: scheduler => operatorFunction('a, 'a) = "observeOn";

[@bs.module "rxjs/operators"]
external observeOnWithDelay: (scheduler, int) => operatorFunction('a, 'a) =
  "observeOn";

[@bs.module "rxjs/operators"]
external subscribeOn: scheduler => operatorFunction('a, 'a) = "subscribeOn";

[@bs.module "rxjs/operators"]
external subscribeOnWithDelay: (scheduler, int) => operatorFunction('a, 'a) =
  "subscribeOn";

[@bs.module "rxjs/operators"]
external timeInterval:
  unit =>
  operatorFunction(
    'a,
    {
      .
      "value": 'a,
      "interval": float,
    },
  ) =
  "timeInterval";

[@bs.module "rxjs/operators"]
external timeIntervalS:
  scheduler =>
  operatorFunction(
    'a,
    {
      .
      "value": 'a,
      "interval": float,
    },
  ) =
  "timeInterval";
