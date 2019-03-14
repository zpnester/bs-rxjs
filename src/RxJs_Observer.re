open RxJs__;

type t('a) = observer('a);

include ObserverOps({
  type t('a) = observer('a);
});
