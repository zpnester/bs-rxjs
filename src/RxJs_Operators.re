open RxJs__;

[@bs.module "rxjs/_esm2015/operators"]
external map: ('a => 'b) => operatorFunction('a, 'b) = "map";

[@bs.module "rxjs/_esm2015/operators"]
external mapi: (('a, int) => 'b) => operatorFunction('a, 'b) = "map";

[@bs.module "rxjs/_esm2015/operators"]
external mapTo: 'b => operatorFunction('a, 'b) = "mapTo";

[@bs.module "rxjs/_esm2015/operators"]
external filter: ('a => bool) => operatorFunction('a, 'a) = "filter";

[@bs.module "rxjs/_esm2015/operators"]
external filteri: (('a, int) => bool) => operatorFunction('a, 'a) = "filter";

[@bs.module "rxjs/_esm2015/operators"]
external mergeAll1:
  (~concurrent: int) => operatorFunction(observable('a), 'a) =
  "mergeAll";

[@bs.module "rxjs/_esm2015/operators"]
external mergeAll: unit => operatorFunction(observable('a), 'a) = "mergeAll";

[@bs.module "rxjs/_esm2015/operators"]
external concatAll: unit => operatorFunction(observable('a), 'a) =
  "concatAll";

[@bs.module "rxjs/_esm2015/operators"]
external concatAllP: unit => operatorFunction(Js.Promise.t('a), 'a) =
  "concatAll";

/* 'b not used */
[@bs.module "rxjs/_esm2015/operators"]
external debounce: (unit => observable('b)) => operatorFunction('a, 'a) =
  "debounce";

[@bs.module "rxjs/_esm2015/operators"]
external debounceP: (unit => Js.Promise.t('b)) => operatorFunction('a, 'a) =
  "debounce";

[@bs.module "rxjs/_esm2015/operators"]
external debounceTime: float => operatorFunction('a, 'a) = "debounceTime";

[@bs.module "rxjs/_esm2015/operators"]
external debounceTime2: (float, scheduler) => operatorFunction('a, 'a) =
  "debounceTime";

[@bs.module "rxjs/_esm2015/operators"]
external take: int => operatorFunction('a, 'a) = "take";

[@bs.module "rxjs/_esm2015/operators"]
external takeUntil: observable('b) => operatorFunction('a, 'a) = "takeUntil";

[@bs.module "rxjs/_esm2015/operators"]
external takeWhile: ('a => bool) => operatorFunction('a, 'a) = "takeWhile";

[@bs.module "rxjs/_esm2015/operators"]
external takeWhilei: (('a, int) => bool) => operatorFunction('a, 'a) =
  "takeWhile";

[@bs.module "rxjs/_esm2015/operators"]
external delay: float => operatorFunction('a, 'a) = "delay";

[@bs.module "rxjs/_esm2015/operators"]
external delayD: Js.Date.t => operatorFunction('a, 'a) = "delay";

[@bs.module "rxjs/_esm2015/operators"]
external delay2: (float, scheduler) => operatorFunction('a, 'a) = "delay";

[@bs.module "rxjs/_esm2015/operators"]
external delay2D: (Js.Date.t, scheduler) => operatorFunction('a, 'a) =
  "delay";

[@bs.module "rxjs/_esm2015/operators"]
external delayWhen2:
  (('a, int) => observable('z), observable('c)) => operatorFunction('a, 'a) =
  "delayWhen";

[@bs.module "rxjs/_esm2015/operators"]
external delayWhen: (('a, int) => observable('b)) => operatorFunction('a, 'a) =
  "delayWhen";

[@bs.module "rxjs/_esm2015/operators"] [@bs.variadic]
external startWith: array('a) => operatorFunction('a, 'a) = "startWith";

[@bs.module "rxjs/_esm2015/operators"]
external startWith1S: ('a, scheduler) => operatorFunction('a, 'a) =
  "startWith";

[@bs.module "rxjs/_esm2015/operators"]
external startWith2S: ('a, 'a, scheduler) => operatorFunction('a, 'a) =
  "startWith";

[@bs.module "rxjs/_esm2015/operators"]
external startWith3S: ('a, 'a, 'a, scheduler) => operatorFunction('a, 'a) =
  "startWith";

[@bs.module "rxjs/_esm2015/operators"]
external startWith4S: ('a, 'a, 'a, 'a, scheduler) => operatorFunction('a, 'a) =
  "startWith";

[@bs.module "rxjs/_esm2015/operators"] [@bs.variadic]
external endWith: array('a) => operatorFunction('a, 'a) = "endWith";

[@bs.module "rxjs/_esm2015/operators"]
external endWith1S: ('a, scheduler) => operatorFunction('a, 'a) = "endWith";

[@bs.module "rxjs/_esm2015/operators"]
external endWith2S: ('a, 'a, scheduler) => operatorFunction('a, 'a) =
  "endWith";

[@bs.module "rxjs/_esm2015/operators"]
external endWith3S: ('a, 'a, 'a, scheduler) => operatorFunction('a, 'a) =
  "endWith";

[@bs.module "rxjs/_esm2015/operators"]
external endWith4S:
  ('a, 'a, 'a, 'a, scheduler, unit) => operatorFunction('a, 'a) =
  "endWith";

[@bs.module "rxjs/_esm2015/operators"]
external pairwise: unit => operatorFunction('a, ('a, 'a)) = "pairwise";

[@bs.module "rxjs/_esm2015/operators"] [@bs.variadic]
external withLatestFrom:
  array(observable('a)) => operatorFunction('a, array('a)) =
  "withLatestFrom";

[@bs.module "rxjs/_esm2015/operators"]
external withLatestFrom1: observable('b) => operatorFunction('a, ('a, 'b)) =
  "withLatestFrom";

[@bs.module "rxjs/_esm2015/operators"]
external withLatestFrom2:
  (observable('b), observable('c)) => operatorFunction('a, ('a, 'b, 'c)) =
  "withLatestFrom";

[@bs.module "rxjs/_esm2015/operators"]
external withLatestFrom3:
  (observable('b), observable('c), observable('d)) =>
  operatorFunction('a, ('a, 'b, 'c, 'd)) =
  "withLatestFrom";

[@bs.module "rxjs/_esm2015/operators"]
external withLatestFrom4:
  (observable('b), observable('c), observable('d), observable('e)) =>
  operatorFunction('a, ('a, 'b, 'c, 'd, 'e)) =
  "withLatestFrom";

[@bs.module "rxjs/_esm2015/operators"]
external every: ('a => bool) => operatorFunction('a, bool) = "every";

[@bs.module "rxjs/_esm2015/operators"]
external catchError:
  ((Js.Json.t, observable('a)) => observable('a)) =>
  operatorFunction('a, 'a) =
  "catchError";

[@bs.module "rxjs/_esm2015/operators"]
external retry1: int => operatorFunction('a, 'a) = "retry";

[@bs.module "rxjs/_esm2015/operators"]
external retry: unit => operatorFunction('a, 'a) = "retry";

/* 'b not used */
[@bs.module "rxjs/_esm2015/operators"]
external retryWhen:
  (observable(Js.Json.t) => observable('b)) => operatorFunction('a, 'a) =
  "retryWhen";

[@bs.module "rxjs/_esm2015/operators"]
external first2: ('a => bool, 'a) => operatorFunction('a, 'a) = "first";

// 1 here is final arity not original

[@bs.module "rxjs/_esm2015/operators"]
external first1D:
  ([@bs.as {json|null|json}] _, 'a) => operatorFunction('a, 'a) =
  "first";

[@bs.module "rxjs/_esm2015/operators"]
external first1: ('a => bool) => operatorFunction('a, 'a) = "first";

[@bs.module "rxjs/_esm2015/operators"]
external first: unit => operatorFunction('a, 'a) = "first";

[@bs.module "rxjs/_esm2015/operators"]
external firsti2:
  (('a, int, observable('a)) => bool, 'a) => operatorFunction('a, 'a) =
  "first";

// 1 here is final arity not original

[@bs.module "rxjs/_esm2015/operators"]
external firsti1D:
  ([@bs.as {json|null|json}] _, 'a) => operatorFunction('a, 'a) =
  "first";

[@bs.module "rxjs/_esm2015/operators"]
external firsti1:
  (('a, int, observable('a)) => bool) => operatorFunction('a, 'a) =
  "first";

[@bs.module "rxjs/_esm2015/operators"]
external ignoreElements: unit => operatorFunction('a, 'a) = "ignoreElements";

[@bs.module "rxjs/_esm2015/operators"]
external last2: ('a => bool, 'a) => operatorFunction('a, 'a) = "last";

[@bs.module "rxjs/_esm2015/operators"]
external last1: ('a => bool) => operatorFunction('a, 'a) = "last";

// 1 here is final arity not original

[@bs.module "rxjs/_esm2015/operators"]
external last1D: ([@bs.as {json|null|json}] _, 'a) => operatorFunction('a, 'a) =
  "last";

[@bs.module "rxjs/_esm2015/operators"]
external lasti2:
  (('a, int, observable('a)) => bool, 'a) => operatorFunction('a, 'a) =
  "last";

[@bs.module "rxjs/_esm2015/operators"]
external lasti1:
  (('a, int, observable('a)) => bool) => operatorFunction('a, 'a) =
  "last";

// 1 here is final arity not original

[@bs.module "rxjs/_esm2015/operators"]
external lasti1D:
  ([@bs.as {json|null|json}] _, 'a) => operatorFunction('a, 'a) =
  "last";

[@bs.module "rxjs/_esm2015/operators"]
external last: unit => operatorFunction('a, 'a) = "last";

/* 'b not used */
[@bs.module "rxjs/_esm2015/operators"]
external sample: observable('b) => operatorFunction('a, 'a) = "sample";

[@bs.module "rxjs/_esm2015/operators"]
external sampleTime: float => operatorFunction('a, 'a) = "sampleTime";

[@bs.module "rxjs/_esm2015/operators"]
external sampleTime2: (float, scheduler) => operatorFunction('a, 'a) =
  "sampleTime";

[@bs.module "rxjs/_esm2015/operators"]
external single: ('a => bool) => operatorFunction('a, 'a) = "single";

[@bs.module "rxjs/_esm2015/operators"]
external singlei:
  (('a, int, observable('a)) => bool) => operatorFunction('a, 'a) =
  "single";

[@bs.module "rxjs/_esm2015/operators"]
external skip: int => operatorFunction('a, 'a) = "skip";

/* 'b not used */
[@bs.module "rxjs/_esm2015/operators"]
external skipUntil: observable('b) => operatorFunction('a, 'a) = "skipUntil";

[@bs.module "rxjs/_esm2015/operators"]
external skipWhile: ('a => bool) => operatorFunction('a, 'a) = "skipWhile";

[@bs.module "rxjs/_esm2015/operators"]
external skipWhilei: (('a, int) => bool) => operatorFunction('a, 'a) =
  "skipWhile";

type throttleConfig = {
  .
  "leading": bool,
  "trailing": bool,
};

[@bs.module "rxjs/_esm2015/operators"]
external throttle2:
  ('a => observable('b), throttleConfig) => operatorFunction('a, 'a) =
  "throttle";

[@bs.module "rxjs/_esm2015/operators"]
external throttle: ('a => observable('b)) => operatorFunction('a, 'a) =
  "throttle";

[@bs.module "rxjs/_esm2015/operators"]
external throttleP2:
  ('a => Js.Promise.t('b), throttleConfig) => operatorFunction('a, 'a) =
  "throttle";

[@bs.module "rxjs/_esm2015/operators"]
external throttleP: ('a => Js.Promise.t('b)) => operatorFunction('a, 'a) =
  "throttle";

[@bs.module "rxjs/_esm2015/operators"]
external throttleTime3:
  (float, scheduler, throttleConfig) => operatorFunction('a, 'a) =
  "throttleTime";

[@bs.module "rxjs/_esm2015/operators"]
external throttleTime2: (float, scheduler) => operatorFunction('a, 'a) =
  "throttleTime";

[@bs.module "rxjs/_esm2015/operators"]
external throttleTime: float => operatorFunction('a, 'a) = "throttleTime";

[@bs.module "rxjs/_esm2015/operators"]
external buffer: observable('b) => operatorFunction('a, array('a)) =
  "buffer";

[@bs.module "rxjs/_esm2015/operators"]
external bufferCount2:
  (~bufferSize: int, ~startBufferEvery: float) =>
  operatorFunction('a, array('a)) =
  "bufferCount";

[@bs.module "rxjs/_esm2015/operators"]
external bufferCount: int => operatorFunction('a, array('a)) = "bufferCount";

// begin bufferTime

[@bs.module "rxjs/_esm2015/operators"]
external bufferTime4:
  (
    ~bufferTimeSpan: float,
    ~bufferCreationInterval: option(float),
    ~maxBufferSize: int,
    RxJs_Scheduler.t
  ) =>
  operatorFunction('a, array('a)) =
  "bufferTime";

[@bs.module "rxjs/_esm2015/operators"]
external bufferTime3:
  (
    ~bufferTimeSpan: float,
    ~bufferCreationInterval: option(float),
    ~maxBufferSize: int
  ) =>
  operatorFunction('a, array('a)) =
  "bufferTime";

[@bs.module "rxjs/_esm2015/operators"]
external bufferTime3S:
  (
    ~bufferTimeSpan: float,
    ~bufferCreationInterval: option(float),
    scheduler
  ) =>
  operatorFunction('a, array('a)) =
  "bufferTime";

// keep bufferCreationInterval non option here but not in others
[@bs.module "rxjs/_esm2015/operators"]
external bufferTime2:
  (~bufferTimeSpan: float, ~bufferCreationInterval: float) =>
  operatorFunction('a, array('a)) =
  "bufferTime";

[@bs.module "rxjs/_esm2015/operators"]
external bufferTime2S: (float, scheduler) => operatorFunction('a, array('a)) =
  "bufferTime";

[@bs.module "rxjs/_esm2015/operators"]
external bufferTime: float => operatorFunction('a, array('a)) = "bufferTime";

// end of bufferTime

[@bs.module "rxjs/_esm2015/operators"]
external bufferToggle:
  (observable('b), 'b => observable('c)) => operatorFunction('a, array('a)) =
  "bufferToggle";

[@bs.module "rxjs/_esm2015/operators"]
external bufferToggleP:
  (Js.Promise.t('b), 'b => Js.Promise.t('c)) =>
  operatorFunction('a, array('a)) =
  "bufferToggle";

[@bs.module "rxjs/_esm2015/operators"]
external bufferWhen:
  (unit => observable('b)) => operatorFunction('a, array('a)) =
  "bufferWhen";

// resultSelector deprecated
[@bs.module "rxjs/_esm2015/operators"]
external concatMap: ('a => observable('b)) => operatorFunction('a, 'b) =
  "concatMap";

[@bs.module "rxjs/_esm2015/operators"]
external concatMapi:
  (('a, int) => observable('b)) => operatorFunction('a, 'b) =
  "concatMap";

[@bs.module "rxjs/_esm2015/operators"]
external mergeMap2:
  ('a => observable('b), ~concurrent: int) => operatorFunction('a, 'b) =
  "mergeMap";

[@bs.module "rxjs/_esm2015/operators"]
external mergeMap: ('a => observable('b)) => operatorFunction('a, 'b) =
  "mergeMap";

[@bs.module "rxjs/_esm2015/operators"]
external mergeMapi2:
  (('a, int) => observable('b), ~concurrent: int) => operatorFunction('a, 'b) =
  "mergeMap";

[@bs.module "rxjs/_esm2015/operators"]
external mergeMapi: (('a, int) => observable('b)) => operatorFunction('a, 'b) =
  "mergeMap";

// resultSelector is deprecated

[@bs.module "rxjs/_esm2015/operators"]
external flatMap2:
  ('a => observable('b), ~concurrent: int) => operatorFunction('a, 'b) =
  "flatMap";

[@bs.module "rxjs/_esm2015/operators"]
external flatMap: ('a => observable('b)) => operatorFunction('a, 'b) =
  "flatMap";

[@bs.module "rxjs/_esm2015/operators"]
external flatMapi2:
  (('a, int) => observable('b), ~concurrent: int) => operatorFunction('a, 'b) =
  "flatMap";

[@bs.module "rxjs/_esm2015/operators"]
external flatMapi: (('a, int) => observable('b)) => operatorFunction('a, 'b) =
  "flatMap";

[@bs.module "rxjs/_esm2015/operators"]
external concatMapTo: observable('b) => operatorFunction('a, 'b) =
  "concatMapTo";

[@bs.module "rxjs/_esm2015/operators"]
external expand3:
  ('a => observable('b), ~concurrent: int, scheduler) =>
  operatorFunction('a, 'b) =
  "expand";

[@bs.module "rxjs/_esm2015/operators"]
external expand2:
  ('a => observable('b), ~concurrent: int) => operatorFunction('a, 'b) =
  "expand";

[@bs.module "rxjs/_esm2015/operators"]
external expand: ('a => observable('b)) => operatorFunction('a, 'b) =
  "expand";

[@bs.module "rxjs/_esm2015/operators"]
external expandi3:
  (('a, int) => observable('b), ~concurrent: int, scheduler) =>
  operatorFunction('a, 'b) =
  "expand";

[@bs.module "rxjs/_esm2015/operators"]
external expandi2:
  (('a, int) => observable('b), ~concurrent: int) => operatorFunction('a, 'b) =
  "expand";

[@bs.module "rxjs/_esm2015/operators"]
external expandi: (('a, int) => observable('b)) => operatorFunction('a, 'b) =
  "expand";

// todo GroupedObservable

// begin groupBy

// todo rewrite if null won't work (if undefined needed)

[@bs.module "rxjs/_esm2015/operators"]
external groupBy4R:
  (
    'a => 'key,
    'a => 'r,
    observable('r) => observable('z),
    unit => subject('r)
  ) =>
  operatorFunction('a, observable('r)) =
  "groupBy";

[@bs.module "rxjs/_esm2015/operators"]
external groupBy4:
  (
    'a => 'key,
    [@bs.as {json|null|json}] _,
    observable('a) => observable('z),
    unit => subject('a)
  ) =>
  operatorFunction('a, observable('a)) =
  "groupBy";

[@bs.module "rxjs/_esm2015/operators"]
external groupBy3R:
  ('a => 'key, 'a => 'r, observable('r) => observable('z)) =>
  operatorFunction('a, observable('r)) =
  "groupBy";

[@bs.module "rxjs/_esm2015/operators"]
external groupBy3:
  (
    'a => 'key,
    [@bs.as {json|null|json}] _,
    observable('a) => observable('z)
  ) =>
  operatorFunction('a, observable('a)) =
  "groupBy";

[@bs.module "rxjs/_esm2015/operators"]
external groupBy2R:
  ('a => 'key, 'a => 'r) => operatorFunction('a, observable('r)) =
  "groupBy";

[@bs.module "rxjs/_esm2015/operators"]
external groupBy2:
  ('a => 'key, [@bs.as {json|null|json}] _) =>
  operatorFunction('a, observable('a)) =
  "groupBy";

[@bs.module "rxjs/_esm2015/operators"]
external groupBy: ('a => 'key) => operatorFunction('a, observable('a)) =
  "groupBy";

// end of groupBy

[@bs.module "rxjs/_esm2015/operators"]
external toArray: unit => operatorFunction('a, array('a)) = "toArray";

[@bs.module "rxjs/_esm2015/operators"]
external reduce: ('b, 'a => 'b, 'b) => operatorFunction('a, 'b) = "reduce";

[@bs.module "rxjs/_esm2015/operators"]
external reducei: (('b, 'a, int) => 'b, 'b) => operatorFunction('a, 'b) =
  "reduce";

[@bs.module "rxjs/_esm2015/operators"]
external scan: (('b, 'a) => 'b, 'b) => operatorFunction('a, 'b) = "scan";

[@bs.module "rxjs/_esm2015/operators"]
external scani: (('b, 'a, int) => 'b, 'b) => operatorFunction('a, 'b) =
  "scan";

[@bs.module "rxjs/_esm2015/operators"] [@bs.variadic]
external pluck: array(string) => operatorFunction('a, Js.Json.t) = "pluck";

/* result selector is deprecated */
[@bs.module "rxjs/_esm2015/operators"]
external switchMap: ('a => observable('b)) => operatorFunction('a, 'b) =
  "switchMap";

[@bs.module "rxjs/_esm2015/operators"]
external switchMapi:
  (('a, int) => observable('b)) => operatorFunction('a, 'b) =
  "switchMap";

[@bs.module "rxjs/_esm2015/operators"]
external switchMapTo: observable('b) => operatorFunction('a, 'b) =
  "switchMapTo";

[@bs.module "rxjs/_esm2015/operators"]
external window: observable('b) => operatorFunction('a, observable('a)) =
  "window";

[@bs.module "rxjs/_esm2015/operators"]
external windowCount2:
  (~windowSize: int, ~startWindowEvery: int) =>
  operatorFunction('a, observable('a)) =
  "windowCount";

[@bs.module "rxjs/_esm2015/operators"]
external windowCount: int => operatorFunction('a, observable('a)) =
  "windowCount";

[@bs.module "rxjs/_esm2015/operators"]
external windowToggle:
  (observable('b), 'b => observable('z)) =>
  operatorFunction('a, observable('a)) =
  "windowToggle";

[@bs.module "rxjs/_esm2015/operators"]
external windowTime: int => operatorFunction('a, observable('a)) =
  "windowTime";

[@bs.module "rxjs/_esm2015/operators"]
external windowTime2:
  (float, scheduler) => operatorFunction('a, observable('a)) =
  "windowTime";

[@bs.module "rxjs/_esm2015/operators"]
external windowWhen:
  (unit => observable('b)) => operatorFunction('a, observable('a)) =
  "windowWhen";

[@bs.module "rxjs/_esm2015/operators"]
external tap:
  (
    ~next: 'a => unit=?,
    ~error: Js.Json.t => unit=?,
    ~complete: unit => unit=?,
    unit
  ) =>
  operatorFunction('a, 'a) =
  "tap";

[@bs.module "rxjs/_esm2015/operators"]
external tapO: observer('a) => operatorFunction('a, 'a) = "tap";

/* TODO Notification */
/* dematerialize skipped, Notification impl required */

[@bs.module "rxjs/_esm2015/operators"]
external finalize: (unit => unit) => operatorFunction('a, 'a) = "finalize";

[@bs.module "rxjs/_esm2015/operators"]
external repeat: int => operatorFunction('a, 'a) = "repeat";

// begin timeout

// number timeout

[@bs.module "rxjs/_esm2015/operators"]
external timeout: float => operatorFunction('a, 'a) = "timeout";

[@bs.module "rxjs/_esm2015/operators"]
external timeout2: (float, scheduler) => operatorFunction('a, 'a) = "timeout";

// date timeout

[@bs.module "rxjs/_esm2015/operators"]
external timeoutD: Js.Date.t => operatorFunction('a, 'a) = "timeout";

[@bs.module "rxjs/_esm2015/operators"]
external timeoutD2: (Js.Date.t, scheduler) => operatorFunction('a, 'a) =
  "timeout";

// end timeout

[@bs.module "rxjs/_esm2015/operators"]
external timeoutWith: (float, observable('a)) => operatorFunction('a, 'a) =
  "timeoutWith";

[@bs.module "rxjs/_esm2015/operators"]
external timeoutWithD:
  (Js.Date.t, observable('a)) => operatorFunction('a, 'a) =
  "timeoutWith";

[@bs.module "rxjs/_esm2015/operators"]
external timeoutWith3:
  (float, observable('a), scheduler) => operatorFunction('a, 'a) =
  "timeoutWith";

[@bs.module "rxjs/_esm2015/operators"]
external timeoutWithD3:
  (Js.Date.t, observable('a), scheduler) => operatorFunction('a, 'a) =
  "timeoutWith";

[@bs.module "rxjs/_esm2015/operators"]
external combineAll: unit => operatorFunction(observable('a), array('a)) =
  "combineAll";

[@bs.module "rxjs/_esm2015/operators"]
external defaultIfEmpty: 'a => operatorFunction('a, 'a) = "defaultIfEmpty";

[@bs.module "rxjs/_esm2015/operators"]
external sequenceEqual2:
  (observable('a), ('a, 'a) => bool) => operatorFunction('a, bool) =
  "sequenceEqual";

[@bs.module "rxjs/_esm2015/operators"]
external sequenceEqual: observable('a) => operatorFunction('a, bool) =
  "sequenceEqual";

[@bs.module "rxjs/_esm2015/operators"]
external multicast: (unit => subject('a)) => operatorFunction('a, 'a) =
  "multicast";

[@bs.module "rxjs/_esm2015/operators"]
external multicast2:
  (unit => subject('a), observable('a) => observable('r)) =>
  operatorFunction('a, 'r) =
  "multicast";

[@bs.module "rxjs/_esm2015/operators"]
external share: unit => operatorFunction('a, 'a) = "share";

// begin shareReplay
module ShareReplayConfig = {
  type t;

  [@bs.obj]
  external make:
    (
      ~bufferSize: int=?,
      ~windowTime: float=?,
      ~refCount: bool=?,
      ~scheduler: scheduler=?,
      unit
    ) =>
    t =
    "";
};

[@bs.module "rxjs/_esm2015/operators"]
external shareReplay3:
  (~bufferSize: int, ~windowTime: float, scheduler) =>
  operatorFunction('a, 'a) =
  "shareReplay";

[@bs.module "rxjs/_esm2015/operators"]
external shareReplay3C:
  (ShareReplayConfig.t, ~windowTime: float, scheduler) =>
  operatorFunction('a, 'a) =
  "shareReplay";

[@bs.module "rxjs/_esm2015/operators"]
external shareReplay2:
  (~bufferSize: int, ~windowTime: float) => operatorFunction('a, 'a) =
  "shareReplay";

[@bs.module "rxjs/_esm2015/operators"]
external shareReplay2C:
  (ShareReplayConfig.t, ~windowTime: float) => operatorFunction('a, 'a) =
  "shareReplay";

[@bs.module "rxjs/_esm2015/operators"]
external shareReplay1: (~bufferSize: int) => operatorFunction('a, 'a) =
  "shareReplay";

[@bs.module "rxjs/_esm2015/operators"]
external shareReplay: unit => operatorFunction('a, 'a) = "shareReplay";

[@bs.module "rxjs/_esm2015/operators"]
external shareReplay1C: ShareReplayConfig.t => operatorFunction('a, 'a) =
  "shareReplay";

// end of shareReplay

[@bs.module "rxjs/_esm2015/operators"]
external publish:
  unit => unaryFunction(observable('a), connectableObservable('a)) =
  "publish";

[@bs.module "rxjs/_esm2015/operators"]
external publish1: operatorFunction('a, 'b) => operatorFunction('a, 'b) =
  "publish";

[@bs.module "rxjs/_esm2015/operators"]
external publishBehavior:
  'a => unaryFunction(observable('a), connectableObservable('a)) =
  "publishBehavior";

[@bs.module "rxjs/_esm2015/operators"]
external publishLast:
  unit => unaryFunction(observable('a), connectableObservable('a)) =
  "publishLast";

// begin publishReplay

[@bs.module "rxjs/_esm2015/operators"]
external publishReplay3S:
  (~bufferSize: int, ~windowTime: float, scheduler) =>
  operatorFunction('a, 'a) =
  "publishReplay";

[@bs.module "rxjs/_esm2015/operators"]
external publishReplay2:
  (~bufferSize: int, ~windowTime: float) => operatorFunction('a, 'a) =
  "publishReplay";

[@bs.module "rxjs/_esm2015/operators"]
external publishReplay1: (~bufferSize: int) => operatorFunction('a, 'a) =
  "publishReplay";

[@bs.module "rxjs/_esm2015/operators"]
external publishReplay: unit => operatorFunction('a, 'a) = "publishReplay";

[@bs.module "rxjs/_esm2015/operators"]
external publishReplay4:
  (
    ~bufferSize: int,
    ~windowTime: float,
    operatorFunction('a, 'b),
    scheduler
  ) =>
  operatorFunction('a, 'b) =
  "publishReplay";

[@bs.module "rxjs/_esm2015/operators"]
external publishReplay3:
  (~bufferSize: int, ~windowTime: float, operatorFunction('a, 'b)) =>
  operatorFunction('a, 'b) =
  "publishReplay";

// end of publishReplay

/* 'b not used */
[@bs.module "rxjs/_esm2015/operators"]
external audit: ('a => observable('b)) => operatorFunction('a, 'a) = "audit";

[@bs.module "rxjs/_esm2015/operators"]
external auditP: ('a => Js.Promise.t('b)) => operatorFunction('a, 'a) =
  "audit";

[@bs.module "rxjs/_esm2015/operators"]
external auditTime: float => operatorFunction('a, 'a) = "auditTime";

[@bs.module "rxjs/_esm2015/operators"]
external auditTime2: (float, RxJs_Scheduler.t) => operatorFunction('a, 'a) =
  "auditTime";

[@bs.module "rxjs/_esm2015/operators"]
external exhaust: unit => operatorFunction(observable('a), 'a) = "exhaust";

[@bs.module "rxjs/_esm2015/operators"]
external exhaustMap2:
  (
    'a => observable('b),
    (~outerValue: 'a, ~innerValue: 'b, ~outerIndex: int, ~innerIndex: int) =>
    'c
  ) =>
  operatorFunction('a, 'c) =
  "exhaustMap";

external exhaustMap: ('a => observable('b)) => operatorFunction('a, 'c) =
  "exhaustMap";

[@bs.module "rxjs/_esm2015/operators"]
external exhaustMapi2:
  (
    ('a, int) => observable('b),
    (~outerValue: 'a, ~innerValue: 'b, ~outerIndex: int, ~innerIndex: int) =>
    'c
  ) =>
  operatorFunction('a, 'c) =
  "exhaustMap";

[@bs.module "rxjs/_esm2015/operators"]
external exhaustMapi:
  (('a, int) => observable('b)) => operatorFunction('a, 'c) =
  "exhaustMap";

[@bs.module "rxjs/_esm2015/operators"]
external elementAt2: (int, 'a) => operatorFunction('a, 'a) = "elementAt";

[@bs.module "rxjs/_esm2015/operators"]
external elementAt: int => operatorFunction('a, 'a) = "elementAt";

// BS docs: Never, EVER, annotate a value coming from JS as option('a). Always give the concrete, non-polymorphic type.
// 😬

[@bs.module "rxjs/_esm2015/operators"]
external find: ('a => bool) => operatorFunction('a, option('a)) = "find";

[@bs.module "rxjs/_esm2015/operators"]
external findi:
  (('a, int, observable('a)) => bool) => operatorFunction('a, option('a)) =
  "find";

[@bs.module "rxjs/_esm2015/operators"]
external findIndex: ('a => bool) => operatorFunction('a, int) = "findIndex";

[@bs.module "rxjs/_esm2015/operators"]
external findIndexi:
  (('a, int, observable('a)) => bool) => operatorFunction('a, int) =
  "findIndex";
[@bs.module "rxjs/_esm2015/operators"]
external isEmpty: unit => operatorFunction('a, bool) = "isEmpty";

[@bs.module "rxjs/_esm2015/operators"]
external max: unit => operatorFunction('a, 'a) = "max";

[@bs.module "rxjs/_esm2015/operators"]
external max1: (('a, 'a) => float) => operatorFunction('a, 'a) = "max";

[@bs.module "rxjs/_esm2015/operators"]
external min: unit => operatorFunction('a, 'a) = "min";

[@bs.module "rxjs/_esm2015/operators"]
external min1: (('a, 'a) => float) => operatorFunction('a, 'a) = "min";

[@bs.module "rxjs/_esm2015/operators"]
external switchAll: unit => operatorFunction(observable('a), 'a) =
  "switchAll";

[@bs.module "rxjs/_esm2015/operators"]
external onErrorResumeNext:
  array(observable('a)) => operatorFunction('a, 'a) =
  "onErrorResumeNext";

[@bs.module "rxjs/_esm2015/operators"]
external refCount:
  unit => unaryFunction(connectableObservable('a), observable('a)) =
  "refCount";

[@bs.module "rxjs/_esm2015/operators"]
external throwIfEmpty1: (unit => unit) => operatorFunction('a, 'a) =
  "throwIfEmpty";

[@bs.module "rxjs/_esm2015/operators"]
external throwIfEmpty: unit => operatorFunction('a, 'a) = "throwIfEmpty";

[@bs.module "rxjs/_esm2015/operators"]
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

[@bs.module "rxjs/_esm2015/operators"]
external timestamp1:
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

[@bs.module "rxjs/_esm2015/operators"]
external distinctUntilChanged1: (('a, 'a) => bool) => operatorFunction('a, 'a) =
  "distinctUntilChanged";

[@bs.module "rxjs/_esm2015/operators"]
external distinctUntilChanged: unit => operatorFunction('a, 'a) =
  "distinctUntilChanged";

/* distinctUntilKeyChanged skipped  */

[@bs.module "rxjs/_esm2015/operators"]
external observeOn: scheduler => operatorFunction('a, 'a) = "observeOn";

[@bs.module "rxjs/_esm2015/operators"]
external observeOn2: (scheduler, ~delay: float) => operatorFunction('a, 'a) =
  "observeOn";

[@bs.module "rxjs/_esm2015/operators"]
external subscribeOn: scheduler => operatorFunction('a, 'a) = "subscribeOn";

[@bs.module "rxjs/_esm2015/operators"]
external subscribeOn2: (scheduler, ~delay: float) => operatorFunction('a, 'a) =
  "subscribeOn";

[@bs.module "rxjs/_esm2015/operators"]
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

[@bs.module "rxjs/_esm2015/operators"]
external timeInterval1:
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

[@bs.module "rxjs/_esm2015/operators"]
external partition:
  (('a, int) => bool) =>
  unaryFunction(observable('a), (observable('a), observable('a))) =
  "partition";