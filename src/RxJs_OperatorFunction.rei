open RxJs__;

type t('a, 'b) = operatorFunction('a, 'b);

external make: (observable('a) => observable('b)) => t('a, 'b) =
  "%identity";
