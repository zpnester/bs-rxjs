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
