type observer('a);
type observable('a);
type connectable_observable('a);
type operator('a, 'b);
type subscription;
type subject('a);
type async_subject('a);
type behavior_subject('a);
type replay_subject('a);
type websocket_subject('a);

module Subscription: {
  type t = subscription;

  let unsubscribe: subscription => unit;
};

module Observer: {
  type t('a) = observer('a);
  [@bs.send] external next: (t('a), 'a) => unit = "";
  [@bs.send] external complete: t('a) => unit = "";
  [@bs.send] external error: (t('a), 'e) => unit = "";
};

module Operator: {type t('a, 'b) = operator('a, 'b);};

module Observable: {
  type t('a) = observable('a);

  let pipe: (t('a), Operator.t('a, 'b)) => observable('b);

  let pipe2:
    (t('a), Operator.t('a, 'b), Operator.t('b, 'c)) => observable('c);
  let pipe3:
    (t('a), Operator.t('a, 'b), Operator.t('b, 'c), Operator.t('c, 'd)) =>
    observable('d);

  let pipe4:
    (
      t('a),
      Operator.t('a, 'b),
      Operator.t('b, 'c),
      Operator.t('c, 'd),
      Operator.t('d, 'e)
    ) =>
    observable('e);

  let pipe5:
    (
      t('a),
      Operator.t('a, 'b),
      Operator.t('b, 'c),
      Operator.t('c, 'd),
      Operator.t('d, 'e),
      Operator.t('e, 'f)
    ) =>
    observable('f);

  let pipe6:
    (
      t('a),
      Operator.t('a, 'b),
      Operator.t('b, 'c),
      Operator.t('c, 'd),
      Operator.t('d, 'e),
      Operator.t('e, 'f),
      Operator.t('f, 'g)
    ) =>
    observable('g);

  let pipe7:
    (
      t('a),
      Operator.t('a, 'b),
      Operator.t('b, 'c),
      Operator.t('c, 'd),
      Operator.t('d, 'e),
      Operator.t('e, 'f),
      Operator.t('f, 'g),
      Operator.t('g, 'h)
    ) =>
    observable('h);

  let pipe8:
    (
      t('a),
      Operator.t('a, 'b),
      Operator.t('b, 'c),
      Operator.t('c, 'd),
      Operator.t('d, 'e),
      Operator.t('e, 'f),
      Operator.t('f, 'g),
      Operator.t('g, 'h),
      Operator.t('h, 'i)
    ) =>
    observable('i);

  let partition:
    (t('a), ('a, int) => bool) => (observable('a), observable('a));

  let subscribe:
    (
      t('a),
      ~next: 'a => unit=?,
      ~error: 'e => unit=?,
      ~complete: unit => unit=?,
      unit
    ) =>
    subscription;

  let create: (observer('a) => unit) => observable('a);

  let of1: 'a => observable('a);
  let of2: ('a, 'a) => observable('a);
  let of3: ('a, 'a, 'a) => observable('a);
  let of4: ('a, 'a, 'a, 'a) => observable('a);

  let race2: (observable('a), observable('a)) => observable('a);
  let race3:
    (observable('a), observable('a), observable('a)) => observable('a);
  let race4:
    (observable('a), observable('a), observable('a), observable('a)) =>
    observable('a);

  let fromArray: array('a) => observable('a);
  let fromPromise: Js.Promise.t('a) => observable('a);
  let fromString: string => observable(string);
  let empty: observable('a);
  let interval: int => observable(int);

  let zip2: (observable('a), observable('b)) => observable(('a, 'b));
  let zip3:
    (observable('a), observable('b), observable('c)) =>
    observable(('a, 'b, 'c));

  let zip4:
    (observable('a), observable('b), observable('c), observable('d)) =>
    observable(('a, 'b, 'c, 'd));

  let timer:
    (
      ~delay: [ | `Int(int) | `Float(float) | `Date(Js.Date.t)]=?,
      ~period: int=?,
      unit
    ) =>
    observable(int);

  let range: (~start: int, ~count: int) => observable(int);

  let fromEvent: (Dom.eventTarget, string) => observable(Dom.event);

  let combineLatest2:
    (observable('a), observable('a)) => observable(array('a));

  let combineLatest3:
    (observable('a), observable('a), observable('a)) =>
    observable(array('a));
  let combineLatest4:
    (observable('a), observable('a), observable('a), observable('a)) =>
    observable(array('a));

  let combineLatestTuple2:
    (observable('a), observable('b)) => observable(('a, 'b));

  let combineLatestTuple3:
    (observable('a), observable('b), observable('c)) =>
    observable(('a, 'b, 'c));

  let combineLatestTuple4:
    (observable('a), observable('b), observable('c), observable('d)) =>
    observable(('a, 'b, 'c, 'd));

  let forkJoin: observable('a) => observable('a);

  let forkJoin2: (observable('a), observable('b)) => observable(('a, 'b));

  let forkJoin3:
    (observable('a), observable('b), observable('c)) =>
    observable(('a, 'b, 'c));

  let forkJoin4:
    (observable('a), observable('b), observable('c), observable('d)) =>
    observable(('a, 'b, 'c, 'd));

  let merge2: (observable('a), observable('a)) => observable('a);
  let merge3:
    (observable('a), observable('a), observable('a)) => observable('a);

  let merge4:
    (observable('a), observable('a), observable('a), observable('a)) =>
    observable('a);

  let throwError: 'e => observable('a);

  let toPromise: observable('a) => Js.Promise.t('a);

  let concat2: (observable('a), observable('a)) => observable('a);

  let concat3:
    (observable('a), observable('a), observable('a)) => observable('a);

  let concat4:
    (observable('a), observable('a), observable('a), observable('a)) =>
    observable('a);

  let iif: (unit => bool, observable('a), observable('a)) => observable('a);
};

module ConnectableObservable: {
  type t('a) = connectable_observable('a);

  let asObservable: t('a) => observable('a);

  let getSubject: t('a) => subject('a);

  let asConnectableObservable:
    observable('a) => option(connectable_observable('a));

  let connect: t('a) => unit;
};

module Operators: {
  let map: (('a, int) => 'b) => operator('a, 'b);

  let mapi: (('a, int) => 'b) => operator('a, 'b);

  let mapTo: 'b => operator('a, 'b);

  let filter: ('a => bool) => operator('a, 'a);

  let merge: observable('a) => operator('a, 'a);

  let mergeAll: (~concurrent: int=?, unit) => operator(observable('a), 'a);

  let concat: observable('a) => operator('a, 'a);

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

  let startWith: 'a => operator('a, 'a);

  let startWith2: ('a, 'a) => operator('a, 'a);

  let startWith3: ('a, 'a, 'a) => operator('a, 'a);

  let startWith4: ('a, 'a, 'a, 'a) => operator('a, 'a);

  let pairwise: unit => operator('a, ('a, 'a));

  let withLatestFrom: observable('b) => operator('a, ('a, 'b));

  let every: ('a => bool) => operator('a, bool);

  let catch: (Js.Json.t => observable('a)) => operator('a, 'a);

  let retry: int => operator('a, 'a);

  let retryWhen:
    (observable(Js.Json.t) => observable('b)) => operator('a, 'a);

  let distinctUntilChanged: unit => operator('a, 'a);

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

  let flatMap: (('a, int) => observable('b)) => operator('a, 'b);

  let concatMapTo: observable('b) => operator('a, 'b);

  let expand: (('a, int) => observable('b)) => operator('a, 'b);

  let groupBy: ('a => 'key) => operator('a, observable('a));

  let toArray: unit => operator('a, array('a));

  let reduce: (('b, 'a, int) => 'b, 'b) => operator('a, 'b);

  let scan: (('b, 'a, int) => 'b, 'b) => operator('a, 'b);

  let pluck: string => operator('a, Js.Json.t);

  let pluck2: (string, string) => operator('a, Js.Json.t);

  let pluck3: (string, string, string) => operator('a, Js.Json.t);

  let pluck4: (string, string, string, string) => operator('a, Js.Json.t);

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
};

module Subject: {
  type t('a) = subject('a);

  let asObservable: t('a) => observable('a);

  let asObserver: t('a) => observer('a);

  [@bs.send] external next: (t('a), 'a) => unit = "";
  [@bs.send] external complete: t('a) => unit = "";
  [@bs.send] external error: (t('a), 'e) => unit = "";

  let make: unit => subject('a);

  let asSubject: observable('a) => option(subject('a));
};

module AsyncSubject: {
  type t('a) = async_subject('a);

  let asObservable: t('a) => observable('a);

  let asObserver: t('a) => observer('a);

  [@bs.send] external next: (t('a), 'a) => unit = "";
  [@bs.send] external complete: t('a) => unit = "";
  [@bs.send] external error: (t('a), 'e) => unit = "";

  let make: unit => async_subject('a);

  let asSubject: t('a) => subject('a);
};

module BehaviorSubject: {
  type t('a) = behavior_subject('a);

  let asObservable: t('a) => observable('a);

  let asObserver: t('a) => observer('a);

  [@bs.send] external next: (t('a), 'a) => unit = "";
  [@bs.send] external complete: t('a) => unit = "";
  [@bs.send] external error: (t('a), 'e) => unit = "";

  let make: 'a => behavior_subject('a);

  let getValue: behavior_subject('a) => 'a;

  let asSubject: t('a) => subject('a);
};

module ReplaySubject: {
  type t('a) = replay_subject('a);

  let asObservable: t('a) => observable('a);

  let asObserver: t('a) => observer('a);

  [@bs.send] external next: (t('a), 'a) => unit = "";
  [@bs.send] external complete: t('a) => unit = "";
  [@bs.send] external error: (t('a), 'e) => unit = "";

  let make:
    (~bufferSize: int=?, ~windowTime: int=?, unit) => replay_subject('a);

    let asSubject: t('a) => subject('a);
};

module WebSocketSubject: {
  type t('a) = websocket_subject('a);

  let asObservable: t('a) => observable('a);

  let asObserver: t('a) => observer('a);

  [@bs.send] external next: (t('a), 'a) => unit = "";
  [@bs.send] external complete: t('a) => unit = "";
  [@bs.send] external error: (t('a), 'e) => unit = "";

  let make: (~url: string) => websocket_subject(Js.Json.t);

  let asSubject: t('a) => subject('a);
};