type observer('a);
type observable('a);
type connectableObservable('a);
type unaryFunction('a, 'b) = 'a => 'b;
type operatorFunction('a, 'b) =
  unaryFunction(observable('a), observable('b));
type subscription;
type subject('a);
type asyncSubject('a);
type behaviorSubject('a);
type replaySubject('a);
type websocketSubject('a);

type scheduler;

module type TypeImpl = {type t('a);};

module MakeObserver = (M: TypeImpl) => {
  external asObserver: M.t('a) => observer('a) = "%identity";
};

module MakeObservable = (M: TypeImpl) => {
  external asObservable: M.t('a) => observable('a) = "%identity";
};

module MakeSubject = (M: TypeImpl) => {
  include MakeObservable(M);
  include MakeObserver(M);

  external asSubject: M.t('a) => subject('a) = "%identity";
};

module MakePipeable = (M: TypeImpl) => {
  [@bs.send]
  external pipe1: (M.t('a), unaryFunction(M.t('a), 'b)) => 'b = "pipe";

  [@bs.send]
  external pipe2:
    (M.t('a), unaryFunction(M.t('a), 'b), unaryFunction('b, 'c)) => 'c =
    "pipe";

  [@bs.send]
  external pipe3:
    (
      M.t('a),
      unaryFunction(M.t('a), 'b),
      unaryFunction('b, 'c),
      unaryFunction('c, 'd)
    ) =>
    'd =
    "pipe";

  [@bs.send]
  external pipe4:
    (
      M.t('a),
      unaryFunction(M.t('a), 'b),
      unaryFunction('b, 'c),
      unaryFunction('c, 'd),
      unaryFunction('d, 'e)
    ) =>
    'e =
    "pipe";

  [@bs.send]
  external pipe5:
    (
      M.t('a),
      unaryFunction(M.t('a), 'b),
      unaryFunction('b, 'c),
      unaryFunction('c, 'd),
      unaryFunction('d, 'e),
      unaryFunction('e, 'f)
    ) =>
    'f =
    "pipe";

  [@bs.send]
  external pipe6:
    (
      M.t('a),
      unaryFunction('a, 'b),
      unaryFunction('b, 'c),
      unaryFunction('c, 'd),
      unaryFunction('d, 'e),
      unaryFunction('e, 'f),
      unaryFunction('f, 'g)
    ) =>
    'g =
    "pipe";

  [@bs.send]
  external pipe7:
    (
      M.t('a),
      unaryFunction(M.t('a), 'b),
      unaryFunction('b, 'c),
      unaryFunction('c, 'd),
      unaryFunction('d, 'e),
      unaryFunction('e, 'f),
      unaryFunction('f, 'g),
      unaryFunction('g, 'h)
    ) =>
    'h =
    "pipe";

  [@bs.send]
  external pipe8:
    (
      M.t('a),
      unaryFunction(M.t('a), 'b),
      unaryFunction('b, 'c),
      unaryFunction('c, 'd),
      unaryFunction('d, 'e),
      unaryFunction('e, 'f),
      unaryFunction('f, 'g),
      unaryFunction('g, 'h),
      unaryFunction('h, 'i)
    ) =>
    'i =
    "pipe";
};