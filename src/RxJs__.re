
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

module type TypeImpl = {type t('a);};


module ObserverOps = (M: TypeImpl) => {
  [@bs.send] external next: (M.t('a), 'a) => unit = "";
  [@bs.send] external complete: M.t('a) => unit = "";
  [@bs.send] external error: (M.t('a), 'e) => unit = "";
};


module MakeObserver = (M: TypeImpl) => {
  external asObserver: M.t('a) => observer('a) = "%identity";
};


module MakeObservable = (M: TypeImpl) => {
  external asObservable: M.t('a) => observable('a) = "%identity";
};


module ObservableOps = (M: TypeImpl) => {
  [@bs.send]
  external pipe: (M.t('a), operator('a, 'b)) => observable('b) = "pipe";

  [@bs.send]
  external pipe2:
    (M.t('a), operator('a, 'b), operator('b, 'c)) => observable('c) =
    "pipe";
  [@bs.send]
  external pipe3:
    (
      M.t('a),
      operator('a, 'b),
      operator('b, 'c),
      operator('c, 'd)
    ) =>
    observable('d) =
    "pipe";

  [@bs.send]
  external pipe4:
    (
      M.t('a),
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
      M.t('a),
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
      M.t('a),
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
      M.t('a),
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
      M.t('a),
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

module MakeSubject = (M: TypeImpl) => {
  include MakeObservable(M);
  include MakeObserver(M);

  external asSubject: M.t('a) => subject('a) = "%identity";
};

