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

module Subscription = {
  type t = subscription;

  [@bs.send] external unsubscribe: subscription => unit = "";
};

module type TypeImpl = {type t('a);};

module ObserverOps = (M: TypeImpl) => {
  [@bs.send] external next: (M.t('a), 'a) => unit = "";
  [@bs.send] external complete: M.t('a) => unit = "";
  [@bs.send] external error: (M.t('a), 'e) => unit = "";
};

module MakeObserver = (M: TypeImpl) => {
  external asObserver: M.t('a) => observer('a) = "%identity";
};

module Observer = {
  type t('a) = observer('a);

  include ObserverOps({
    type t('a) = observer('a);
  });
};

module Operator = {
  type t('a, 'b) = operator('a, 'b);

  external make: (observable('a) => observable('b)) => operator('a, 'b) =
    "%identity";
};

module MakeObservable = (M: TypeImpl) => {
  external asObservable: M.t('a) => observable('a) = "%identity";
};

module ObservableOps = (M: TypeImpl) => {
  [@bs.send]
  external pipe: (M.t('a), Operator.t('a, 'b)) => observable('b) = "pipe";

  [@bs.send]
  external pipe2:
    (M.t('a), Operator.t('a, 'b), Operator.t('b, 'c)) => observable('c) =
    "pipe";
  [@bs.send]
  external pipe3:
    (
      M.t('a),
      Operator.t('a, 'b),
      Operator.t('b, 'c),
      Operator.t('c, 'd)
    ) =>
    observable('d) =
    "pipe";

  [@bs.send]
  external pipe4:
    (
      M.t('a),
      Operator.t('a, 'b),
      Operator.t('b, 'c),
      Operator.t('c, 'd),
      Operator.t('d, 'e)
    ) =>
    observable('e) =
    "pipe";

  [@bs.send]
  external pipe5:
    (
      M.t('a),
      Operator.t('a, 'b),
      Operator.t('b, 'c),
      Operator.t('c, 'd),
      Operator.t('d, 'e),
      Operator.t('e, 'f)
    ) =>
    observable('f) =
    "pipe";

  [@bs.send]
  external pipe6:
    (
      M.t('a),
      Operator.t('a, 'b),
      Operator.t('b, 'c),
      Operator.t('c, 'd),
      Operator.t('d, 'e),
      Operator.t('e, 'f),
      Operator.t('f, 'g)
    ) =>
    observable('g) =
    "pipe";

  [@bs.send]
  external pipe7:
    (
      M.t('a),
      Operator.t('a, 'b),
      Operator.t('b, 'c),
      Operator.t('c, 'd),
      Operator.t('d, 'e),
      Operator.t('e, 'f),
      Operator.t('f, 'g),
      Operator.t('g, 'h)
    ) =>
    observable('h) =
    "pipe";

  [@bs.send]
  external pipe8:
    (
      M.t('a),
      Operator.t('a, 'b),
      Operator.t('b, 'c),
      Operator.t('c, 'd),
      Operator.t('d, 'e),
      Operator.t('e, 'f),
      Operator.t('f, 'g),
      Operator.t('g, 'h),
      Operator.t('h, 'i)
    ) =>
    observable('i) =
    "pipe";

  type partition__('a);
  [@bs.module "rxjs/operators"]
  external partition__: (('a, int) => bool) => partition__('a) = "partition";

  [@bs.send]
  external pipePartition__:
    (M.t('a), partition__('a)) => (observable('a), observable('a)) =
    "pipe";

  /* 'thisArg' param skipped */
  let partition =
      (self: M.t('a), predicate: ('a, int) => bool)
      : (observable('a), observable('a)) =>
    self->pipePartition__(partition__(predicate));

  type subscribe_params('a) = {
    .
    "next": Js.Nullable.t('a => unit),
    "error": Js.Nullable.t(Js.Json.t => unit),
    "complete": Js.Nullable.t(unit => unit),
  };

  [@bs.send]
  external subscribe_: (M.t('a), subscribe_params('a)) => subscription =
    "subscribe";

  let subscribe =
      (
        self: M.t('a),
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
  external subscribeObserver_: (M.t('a), observer('a)) => subscription =
    "subscribe";

  let subscribeObserver = (self: M.t('a), observer: observer('a)) =>
    subscribeObserver_(self, observer);
};

module Observable = {
  type t('a) = observable('a);

  include ObservableOps({
    type t('a) = observable('a);
  });

  [@bs.module "rxjs"] [@bs.scope "Observable"]
  external create: (observer('a) => unit) => observable('a) =
    "create";

  [@bs.module "rxjs"] [@bs.scope "Observable"]
  external createWithTeardown: (observer('a) => (unit => unit)) => observable('a) =
    "create";


  /*[@bs.module "rxjs"] external of1: 'a => observable('a) = "of";
  [@bs.module "rxjs"] external of2: ('a, 'a) => observable('a) = "of";
  [@bs.module "rxjs"] external of3: ('a, 'a, 'a) => observable('a) = "of";
  [@bs.module "rxjs"] external of4: ('a, 'a, 'a, 'a) => observable('a) = "of";
*/

  [@bs.module "rxjs"] [@bs.variadic]
  external of_: array('a) => observable('a) = "of";

  /*[@bs.module "rxjs"]
  external race2: (observable('a), observable('a)) => observable('a) =
    "race";
  [@bs.module "rxjs"]
  external race3:
    (observable('a), observable('a), observable('a)) => observable('a) =
    "race";
  [@bs.module "rxjs"]
  external race4:
    (observable('a), observable('a), observable('a), observable('a)) =>
    observable('a) =
    "race";*/

  [@bs.module "rxjs"] [@bs.variadic]
  external race:
    array(observable('a)) =>
    observable('a) =
    "race";

  [@bs.module "rxjs"]
  external fromArray: array('a) => observable('a) = "from";
  [@bs.module "rxjs"]
  external fromPromise: Js.Promise.t('a) => observable('a) = "from";
  /* emit string as a sequence */
  [@bs.module "rxjs"]
  external fromString: string => observable(string) = "from";
  /* empty is deprecated in favor of using EMPTY constant */
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
  external zip: array(observable('a)) => observable(array('a)) =
    "zip";

  [@bs.module "rxjs"]
  external timer_:
    (
      ~delay: [@bs.unwrap] [ | `Int(int) | `Float(float) | `Date(Js.Date.t)]
                =?,
      ~period: int=?,
      unit
    ) =>
    observable(int) =
    "timer";

  let timer =
      (
        ~delay: option([ | `Int(int) | `Float(float) | `Date(Js.Date.t)])=?,
        ~period: option(int)=?,
        (),
      ) =>
    timer_(~delay?, ~period?, ());

  [@bs.module "rxjs"]
  external range: (~start: int, ~count: int) => observable(int) = "range";

  [@bs.module "rxjs"]
  external fromEvent: (Dom.eventTarget, string) => observable(Dom.event) =
    "fromEvent";

  [@bs.module "rxjs"] [@bs.variadic]
  external combineLatest:
    array(observable('a)) => observable(array('a)) =
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
  external forkJoin: array(observable('a)) => observable(array('a)) = "forkJoin";

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
  external merge: array(observable('a)) => observable('a) =
    "merge";  

 /* [@bs.module "rxjs"]
  external merge2: (observable('a), observable('a)) => observable('a) =
    "merge";
  [@bs.module "rxjs"]
  external merge3:
    (observable('a), observable('a), observable('a)) => observable('a) =
    "merge";

  [@bs.module "rxjs"]
  external merge4:
    (observable('a), observable('a), observable('a), observable('a)) =>
    observable('a) =
    "merge";*/

  [@bs.module "rxjs"]
  external throwError: 'e => observable('a) = "throwError";

  [@bs.send]
  external toPromise: observable('a) => Js.Promise.t('a) = "toPromise";

  [@bs.module "rxjs"] [@bs.variadic]
  external concat: array(observable('a)) => observable('a) =
    "concat";

 /* [@bs.module "rxjs"]
  external concat2: (observable('a), observable('a)) => observable('a) =
    "concat";

  [@bs.module "rxjs"]
  external concat3:
    (observable('a), observable('a), observable('a)) => observable('a) =
    "concat";

  [@bs.module "rxjs"]
  external concat4:
    (observable('a), observable('a), observable('a), observable('a)) =>
    observable('a) =
    "concat";*/

  [@bs.module "rxjs"]
  external iif:
    (unit => bool, observable('a), observable('a)) => observable('a) =
    "iif";
};

module ConnectableObservable = {
  type t('a) = connectable_observable('a);
  include MakeObservable({
    type t('a) = connectable_observable('a);
  });

  [@bs.send] external getSubject: t('a) => subject('a) = "getSubject";

  [@bs.val] [@bs.module "rxjs"]
  external connectableObservableCtor: Js.Json.t = "ConnectableObservable";

  external oAsJson__: observable('a) => Js.Json.t = "%identity";
  external coFromJsonUnsafe__: Js.Json.t => connectable_observable('a) =
    "%identity";

  /* instanceof won't work, pipe returns observable with connect method, not real instance of ConnectableObservable */
  let asConnectableObservable_:
    (Js.Json.t, Js.Json.t) => Js.Nullable.t(Js.Json.t) = [%raw
    {|
  function(o, c) {
    if (o.connect && o.getSubject) {
      return o;
    } else {
      return null;
    }
  }
  |}
  ];

  let asConnectableObservable:
    observable('a) => option(connectable_observable('a)) =
    obs =>
      asConnectableObservable_(oAsJson__(obs), connectableObservableCtor)
      ->Js.Nullable.toOption
      ->Belt.Option.map(coFromJsonUnsafe__);

  [@bs.send] external connect: t('a) => subscription = "connect";
};

module Operators = {
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
  external mergeAll:
    (~concurrent: int=?, unit) => operator(observable('a), 'a) =
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
  external debounce: (unit => observable('b)) => operator('a, 'a) =
    "debounce";

  [@bs.module "rxjs/operators"]
  external debounceTime: int => operator('a, 'a) = "debounceTime";

  [@bs.module "rxjs/operators"]
  external take: int => operator('a, 'a) = "take";

  [@bs.module "rxjs/operators"]
  external takeUntil: observable('b) => operator('a, 'a) = "takeUntil";

  [@bs.module "rxjs/operators"]
  external takeWhile: ('a => bool) => operator('a, 'a) = "takeWhile";

  [@bs.module "rxjs/operators"]
  external delay_:
    ([@bs.unwrap] [ | `Int(int) | `Float(float) | `Date(Js.Date.t)]) =>
    operator('a, 'a) =
    "delay";

  let delay = (d: [ | `Int(int) | `Float(float) | `Date(Js.Date.t)]) =>
    delay_(d);

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

  /*[@bs.module "rxjs/operators"]
  external startWith: 'a => operator('a, 'a) = "startWith";

  [@bs.module "rxjs/operators"]
  external startWith2: ('a, 'a) => operator('a, 'a) = "startWith";

  [@bs.module "rxjs/operators"]
  external startWith3: ('a, 'a, 'a) => operator('a, 'a) = "startWith";

  [@bs.module "rxjs/operators"]
  external startWith4: ('a, 'a, 'a, 'a) => operator('a, 'a) = "startWith";
*/
  [@bs.module "rxjs/operators"] [@bs.variadic]
  external endWith: array('a) => operator('a, 'a) = "endWith";
/*
  [@bs.module "rxjs/operators"]
  external endWith: 'a => operator('a, 'a) = "endWith";

  [@bs.module "rxjs/operators"]
  external endWith2: ('a, 'a) => operator('a, 'a) = "endWith";

  [@bs.module "rxjs/operators"]
  external endWith3: ('a, 'a, 'a) => operator('a, 'a) = "endWith";

  [@bs.module "rxjs/operators"]
  external endWith4: ('a, 'a, 'a, 'a) => operator('a, 'a) = "endWith";
*/
  [@bs.module "rxjs/operators"]
  external pairwise: unit => operator('a, ('a, 'a)) = "pairwise";

   [@bs.module "rxjs/operators"] [@bs.variadic]
  external withLatestFromMany: array(observable('a)) => operator('a, array('a)) =
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

  [@bs.module "rxjs/operators"]
  external skip: int => operator('a, 'a) = "skip";

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
  external concatMap: ('a => observable('b)) => operator('a, 'b) =
    "concatMap";

  [@bs.module "rxjs/operators"]
  external mergeMap: ('a => observable('b)) => operator('a, 'b) = "mergeMap";

  /* TODO result selector */
  [@bs.module "rxjs/operators"]
  external flatMap: ('a => observable('b)) => operator('a, 'b) =
    "flatMap";

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

  /*[@bs.module "rxjs/operators"]
  external pluck2: (string, string) => operator('a, Js.Json.t) = "pluck";

  [@bs.module "rxjs/operators"]
  external pluck3: (string, string, string) => operator('a, Js.Json.t) =
    "pluck";

  [@bs.module "rxjs/operators"]
  external pluck4: (string, string, string, string) => operator('a, Js.Json.t) =
    "pluck";*/

  /* TODO result selector */
  [@bs.module "rxjs/operators"]
  external switchMap: (('a, int) => observable('b)) => operator('a, 'b) =
    "switchMap";

  [@bs.module "rxjs/operators"]
  external window: observable('b) => operator('a, observable('a)) =
    "window";

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
  external timeout_:
    ([@bs.unwrap] [ | `Int(int) | `Float(float) | `Date(Js.Date.t)]) =>
    operator('a, 'a) =
    "timeout";

  let timeout = (due: [ | `Int(int) | `Float(float) | `Date(Js.Date.t)]) =>
    timeout_(due);

  [@bs.module "rxjs/operators"]
  external timeoutWith_:
    (
      [@bs.unwrap] [ | `Int(int) | `Float(float) | `Date(Js.Date.t)],
      observable('a)
    ) =>
    operator('a, 'a) =
    "timeoutWith";

  let timeoutWith =
      (
        due: [ | `Int(int) | `Float(float) | `Date(Js.Date.t)],
        withObservable: observable('a),
      ) =>
    timeoutWith_(due, withObservable);

  [@bs.module "rxjs/operators"]
  external combineAll: unit => operator(observable('a), array('a)) =
    "combineAll";

  [@bs.module "rxjs/operators"]
  external defaultIfEmpty: 'a => operator('a, 'a) = "defaultIfEmpty";

  [@bs.module "rxjs/operators"]
  external sequenceEqual: observable('a) => operator('a, bool) =
    "sequenceEqual";

  [@bs.module "rxjs/operators"]
  external multicast_:
    (
    [@bs.unwrap]
    [ | `Subject(subject('a)) | `Factory(unit => subject('a))]
    ) =>
    operator('a, 'a) =
    "multicast";

  let multicast =
      (s: [ | `Subject(subject('a)) | `Factory(unit => subject('a))]) =>
    multicast_(s);

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
    Operator.make(src =>
      src->Observable.pipe2(find_(predicate), map(Js.Undefined.toOption))
    );

  [@bs.module "rxjs/operators"]
  external findIndex:
    (('a, int, observable('a)) => bool) => operator('a, int) =
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
};

module MakeSubject = (M: TypeImpl) => {
  include MakeObservable(M);
  include MakeObserver(M);

  external asSubject: M.t('a) => subject('a) = "%identity";
};

module Subject = {
  type t('a) = subject('a);

  /* do not include MakeSubject, duplicate include MakeObservable+MakeObserver */
  include MakeObservable({
    type t('a) = subject('a);
  });
  include MakeObserver({
    type t('a) = subject('a);
  });

  [@bs.module "rxjs"] [@bs.new]
  external make: unit => subject('a) = "Subject";

  external observableToJson__: observable('a) => Js.Json.t = "%identity";
  external subjectFromJsonUnsafe__: Js.Json.t => subject('a) = "%identity";

  [@bs.val] [@bs.module "rxjs"] external subjectCtor: Js.Json.t = "Subject";

  let asSubject_: (Js.Json.t, Js.Json.t) => Js.Nullable.t(Js.Json.t) = [%raw
    {|
  function(o, c) {
    if (o instanceof c) {
      return o;
    } else {
      return null;
    }
  }
  |}
  ];

  let asSubject: observable('a) => option(subject('a)) =
    obs =>
      asSubject_(observableToJson__(obs), subjectCtor)
      ->Js.Nullable.toOption
      ->Belt.Option.map(subjectFromJsonUnsafe__);
};

module AsyncSubject = {
  type t('a) = async_subject('a);

  include MakeSubject({
    type t('a) = async_subject('a);
  });

  [@bs.module "rxjs"] [@bs.new]
  external make: unit => async_subject('a) = "AsyncSubject";
};

module BehaviorSubject = {
  type t('a) = behavior_subject('a);

  include MakeSubject({
    type t('a) = behavior_subject('a);
  });

  [@bs.module "rxjs"] [@bs.new]
  external make: 'a => behavior_subject('a) = "BehaviorSubject";

  /* safe to call unless FFI'd BehaviorSubject from JS */
  [@bs.send] external getValue: behavior_subject('a) => 'a = "getValue";
};

module ReplaySubject = {
  type t('a) = replay_subject('a);
  include MakeSubject({
    type t('a) = replay_subject('a);
  });

  [@bs.module "rxjs"] [@bs.new]
  external make:
    (~bufferSize: int=?, ~windowTime: int=?, unit) => replay_subject('a) =
    "ReplaySubject";
};

module WebSocketSubject = {
  type t('a) = websocket_subject('a);

  include MakeSubject({
    type t('a) = websocket_subject('a);
  });

  [@bs.module "rxjs/websocket"] [@bs.new]
  external make: (~url: string) => websocket_subject(Js.Json.t) =
    "WebSocketSubject";
};