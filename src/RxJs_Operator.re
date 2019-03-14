open RxJs__;

type t('a, 'b) = operator('a, 'b);

external make: (observable('a) => observable('b)) => operator('a, 'b) =
  "%identity";
