open RxJs__;

type t('a, 'b) = operator('a, 'b);

let make: (observable('a) => observable('b)) => operator('a, 'b);
