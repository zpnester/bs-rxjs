
open RxJs;
open Observable;
open Operators;

let o1 = fromArray([|1, 2, 3|]);
o1
->pipe1(mapi((x, i) => (x + 10, i)))
->pipe1(toArray())
->subscribe(
    ~next=Js.log,
    (),
  );