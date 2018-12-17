type error = Js.Json.t;
type observer('a);
type observable('a);
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

module MakeObserver = (M: TypeImpl) => {
  [@bs.send] external next: (M.t('a), 'a) => unit = "";
  [@bs.send] external complete: M.t('a) => unit = "";
  [@bs.send] external error: (M.t('a), error) => unit = "";
};

module Observer =
  MakeObserver({
    type t('a) = observer('a);
  });

module Operator = {
  type t('a, 'b) = operator('a, 'b);
};

module MakeObservable = (M: TypeImpl) => {
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

  [@bs.module "./RxJs.js"]
  external partition__:
    (M.t('a), 'a => bool) => (observable('a), observable('a)) =
    "pipePartition";

  /* contain local import, partition__ should be private */
  let partition = partition__;

  type subscribe_params('a) = {
    .
    "next": Js.Nullable.t('a => unit),
    "error": Js.Nullable.t(error => unit),
    "complete": Js.Nullable.t(unit => unit),
  };

  [@bs.send]
  external subscribe_: (M.t('a), subscribe_params('a)) => subscription =
    "subscribe";

  let subscribe =
      (
        self: M.t('a),
        ~next: option('a => unit)=?,
        ~error: option(error => unit)=?,
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
};

module Observable = {
  type t('a) = observable('a);

  include MakeObservable({
    type t('a) = observable('a);
  });

  [@bs.module "rxjs"] [@bs.scope "Observable"]
  external create: (observer('a) => unit) => observable('a) = "create";

  [@bs.module "rxjs"] external of1: 'a => observable('a) = "of";
  [@bs.module "rxjs"] external of2: ('a, 'a) => observable('a) = "of";
  [@bs.module "rxjs"] external of3: ('a, 'a, 'a) => observable('a) = "of";
  [@bs.module "rxjs"] external of4: ('a, 'a, 'a, 'a) => observable('a) = "of";

  [@bs.module "rxjs"]
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
    "race";

  [@bs.module "rxjs"]
  external fromArray: array('a) => observable('a) = "from";
  [@bs.module "rxjs"]
  external fromPromise: Js.Promise.t('a) => observable('a) = "from";
  /* emit string as a sequence */
  [@bs.module "rxjs"]
  external fromString: string => observable(string) = "from";
  [@bs.module "rxjs"] external empty: observable('a) = "EMPTY";
  [@bs.module "rxjs"] external interval: int => observable(int) = "interval"; /* int */

  [@bs.module "rxjs"]
  external zip2: (observable('a), observable('b)) => observable(('a, 'b)) =
    "zip";
  [@bs.module "rxjs"]
  external zip3:
    (observable('a), observable('b), observable('c)) =>
    observable(('a, 'b, 'c)) =
    "zip";

  external zip4:
    (observable('a), observable('b), observable('c), observable('d)) =>
    observable(('a, 'b, 'c, 'd)) =
    "zip";

  [@bs.module "rxjs"]
  external timer:
    (~initialDelay: int, ~period: int=?, unit) => observable(int) =
    "timer";

  let timerDelay = initialDelay => timer(~initialDelay, ());

  [@bs.module "rxjs"]
  external range: (~start: int, ~count: int) => observable(int) = "range";

  /* fromEvent */

  [@bs.module "rxjs"]
  external combineLatest2:
    (observable('a), observable('a)) => observable(array('a)) =
    "combineLatest";
  [@bs.module "rxjs"]
  external combineLatest3:
    (observable('a), observable('a), observable('a)) =>
    observable(array('a)) =
    "combineLatest";
  [@bs.module "rxjs"]
  external combineLatest4:
    (observable('a), observable('a), observable('a), observable('a)) =>
    observable(array('a)) =
    "combineLatest";

  [@bs.module "rxjs"]
  external combineLatestTuple2:
    (observable('a), observable('b)) => observable(('a, 'b)) =
    "combineLatest";

  [@bs.module "rxjs"]
  external combineLatestTuple3:
    (observable('a), observable('b), observable('c)) =>
    observable(('a, 'b, 'c)) =
    "combineLatest";

  [@bs.module "rxjs"]
  external combineLatestTuple4:
    (observable('a), observable('b), observable('c), observable('d)) =>
    observable(('a, 'b, 'c, 'd)) =
    "combineLatest";

  [@bs.module "rxjs"]
  external forkJoin: observable('a) => observable('a) = "forkJoin";

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

  [@bs.module "rxjs"]
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
    "merge";

  [@bs.module "rxjs"]
  external throwError: error => observable('a) = "throwError";
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
  external concat: observable('a) => operator('a, 'a) = "concat";

  [@bs.module "rxjs/operators"]
  external concatAll: unit => operator(observable('a), 'a) = "concatAll";

  [@bs.module "rxjs/operators"]
  external concatAllPromises: unit => operator(Js.Promise.t('a), 'a) =
    "concatAll";

  /* 'b not used */
  /* func must return obs or specific operator like timer? */
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
  external delay: int => operator('a, 'a) = "delay";

  [@bs.module "rxjs/operators"]
  external delayWhen: ('a => observable('b)) => operator('a, 'a) =
    "delayWhen";

  [@bs.module "rxjs/operators"]
  external startWith: 'a => operator('a, 'a) = "startWith";

  [@bs.module "rxjs/operators"]
  external startWith2: ('a, 'a) => operator('a, 'a) = "startWith";

  [@bs.module "rxjs/operators"]
  external startWith3: ('a, 'a, 'a) => operator('a, 'a) = "startWith";

  [@bs.module "rxjs/operators"]
  external startWith4: ('a, 'a, 'a, 'a) => operator('a, 'a) = "startWith";
  /* combileAll */
  /* mergeAll */

  [@bs.module "rxjs/operators"]
  external pairwise: unit => operator('a, ('a, 'a)) = "pairwise";

  /* withLatestFrom */

  [@bs.module "rxjs/operators"]
  external every: ('a => bool) => operator('a, 'a) = "every";
  /* iif */

  [@bs.module "rxjs/operators"]
  external catch: (error => observable('a)) => operator('a, 'a) =
    "catchError";

  [@bs.module "rxjs/operators"]
  external retry: int => operator('a, 'a) = "retry";

  /* retryWhen */

  /* publish */
  /* multicast */
  /* share */
  /* shareReplay */

  [@bs.module "rxjs/operators"]
  external distinctUntilChanged: unit => operator('a, 'a) =
    "distinctUntilChanged";

  [@bs.module "rxjs/operators"]
  external first: unit => operator('a, 'a) = "first";

  [@bs.module "rxjs/operators"]
  external ignoreElements: unit => operator('a, 'a) = "ignoreElements";

  [@bs.module "rxjs/operators"]
  external last: unit => operator('a, 'a) = "last";

  /* sample */

  [@bs.module "rxjs/operators"]
  external single: ('a => bool) => operator('a, 'a) = "single";

  [@bs.module "rxjs/operators"]
  external skip: int => operator('a, 'a) = "skip";

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
  external throttleTime: float => operator('a, 'a) = "throttleTime";

  /* buffer */

  [@bs.module "rxjs/operators"]
  external bufferCount: int => operator('a, array('a)) = "bufferCount";

  [@bs.module "rxjs/operators"]
  external bufferTime: float => operator('a, array('a)) = "bufferTime";

  [@bs.module "rxjs/operators"]
  external concatMap: ('a => observable('b)) => operator('a, 'b) =
    "concatMap";

  [@bs.module "rxjs/operators"]
  external mergeMap: ('a => observable('b)) => operator('a, 'b) = "mergeMap";

  [@bs.module "rxjs/operators"]
  external flatMap: ('a => observable('b)) => operator('a, 'b) = "flatMap";

  [@bs.module "rxjs/operators"]
  external concatMapTo: observable('b) => operator('a, 'b) = "concatMapTo";

  /* exhaustMap */

  [@bs.module "rxjs/operators"]
  external expand: ('a => observable('b)) => operator('a, 'b) = "expand";

  [@bs.module "rxjs/operators"]
  external groupBy: ('a => 'key) => operator('a, observable('a)) = "groupBy";

  [@bs.module "rxjs/operators"]
  external toArray: unit => operator('a, array('a)) = "toArray";

  [@bs.module "rxjs/operators"]
  external reduce: (('b, 'a) => 'b, 'b) => operator('a, 'b) = "reduce";

  [@bs.module "rxjs/operators"]
  external scan: (('b, 'a) => 'b, 'b) => operator('a, 'b) = "scan";

  /* partition moved to Observable */

  /* pluck */

  /* switchMap */
  /* window */

  [@bs.module "rxjs/operators"]
  external tap: ('a => unit) => operator('a, 'a) = "tap";

  [@bs.module "rxjs/operators"]
  external do_: ('a => unit) => operator('a, 'a) = "do";

  /* dematerialize  */
  /* finally undefined */

  [@bs.module "rxjs/operators"]
  external finalize: (unit => unit) => operator('a, 'a) = "finalize";

  [@bs.module "rxjs/operators"]
  external repeat: int => operator('a, 'a) = "repeat";

  [@bs.module "rxjs/operators"]
  external timeout: int => operator('a, 'a) = "timeout";

  [@bs.send]
  external toPromise: observable('a) => Js.Promise.t('a) = "toPromise";
};

module MakeSubject = (M: TypeImpl) => {
  include MakeObservable(M);
  include MakeObserver(M);

  external asObservable: M.t('a) => observable('a) = "%identity";
  external asObserver: M.t('a) => observer('a) = "%identity";
};

module Subject = {
  type t('a) = subject('a);

  include MakeSubject({
    type t('a) = subject('a);
  });

  [@bs.module "rxjs"] [@bs.new]
  external make: unit => subject('a) = "Subject";
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