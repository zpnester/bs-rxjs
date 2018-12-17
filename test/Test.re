open RxJs;
open Observable;
open Js.Promise;
open Operators;

let o1 = Observable.fromArray([|1, 2, 3, 4, 5, 6|]);
o1->subscribe(
  ~next=i => Js.log(i),
  ~complete=() => Js.log("o1 complete"),
  (),
);

let o2 = Observable.fromString("HELLO");
o2->subscribe(~next=x => Js.log(x), ());

let o3 = Observable.fromPromise(resolve("from promise"));
o3->subscribe(~next=x => Js.log(x), ());

let o4 = o1->pipe(map(i => i + 10));
o4->subscribe(~next=x => Js.log(x), ());

let o5 = o1->pipe2(map(i => i + 20), filter(i => i mod 2 == 0));
o5->subscribe(~next=x => Js.log(x), ());

let o6 = Observable.fromArray([|resolve("one"), resolve("two")|]);
let o7 = Observable.fromArray([|resolve("three"), resolve("four")|]);
let o8 = o6->pipe2(concat(o7), concatAllPromises());
o8->subscribe(~next=x => Js.log(x), ());

let o9 = Observable.fromArray([|51, 52, 53|]);
let o10 = Observable.fromArray([|"green", "red"|]);
forkJoin2(o9, o10)->subscribe(~next=((a, b)) => Js.log2(a, b), ());

merge2(o1, o9)->subscribe(~next=x => Js.log(x), ());

let o11 = Observable.range(~start=456, ~count=10)->pipe(pairwise());
o11->subscribe(~next=((x, y)) => Js.log2(x, y), ());

let o12 = Observable.fromArray([|2, 3, 4|])->pipe(every(x => x mod 2 == 0));
o12->subscribe(~next=x => Js.log2("every", x), ());

let o13 =
  Observable.of1("a value")
  ->pipe2(
      concat(Observable.throwError(Js.Json.string("oops"))),
      retry(3),
    );
o13->subscribe(
  ~next=(x: string) => Js.log(x),
  ~error=e => Js.log2("err", e),
  (),
);

o13
->pipe(
    catch(x => of1("caught " ++ x->Js.Json.decodeString->Belt.Option.getExn)),
  )
->subscribe(
    ~next=(x: string) => Js.log(x),
    ~error=e => Js.log2("err", e),
    (),
  );

Observable.range(~start=100, ~count=30)
->pipe(bufferCount(7))
->subscribe(~next=x => Js.log(x), ());

of4(5, 6, 7, 8)
->pipe(concatMap(x => of1(x + 1)))
->subscribe(~next=x => Js.log(x), ());

of4(5, 6, 7, 8)
->pipe(concatMap(x => of1(x - 1)))
->subscribe(~next=x => Js.log(x), ());

of3(1, 2, 3)
->pipe(concatMapTo(of1("mappedto")))
->subscribe(~next=x => Js.log(x), ());

of1("hello")
->pipe2(expand(x => of1(x ++ "!")), take(5))
->subscribe(~next=x => Js.log(x), ());

of3(
  {"name": "jane", "age": 20},
  {"name": "john", "age": 21},
  {"name": "rick", "age": 20},
)
->pipe2(groupBy(x => x##age), mergeMap(g => g->pipe(toArray())))
->subscribe(~next=x => Js.log(x), ());

range(~start=1, ~count=10)
->pipe2(reduce((acc, v) => acc + v, 0), tap(x => Js.log2("tap", x)))
->subscribe(~next=x => Js.log(x), ());

range(~start=1, ~count=10)
->pipe(reduce((acc, v) => acc ++ "-" ++ string_of_int(v), ""))
->subscribe(~next=x => Js.log(x), ());

of3(
  {"name": "jane", "age": 20},
  {"name": "john", "age": 22},
  {"name": "rick", "age": 22},
)
->pipe2(
    groupBy(x => x##age),
    flatMap(g =>
      g->pipe(reduce((acc, cur) => acc |> Js.Array.concat([|cur|]), [||]))
    ),
  )
->subscribe(~next=x => Js.log(x), ());

let (a, b) = range(~start=10, ~count=20)->partition(x => x mod 2 == 0);
a->pipe(toArray())->subscribe(~next=x => Js.log2("a", x), ());
b->pipe(toArray())->subscribe(~next=x => Js.log2("b", x), ());

range(~start=1, ~count=10)
->pipe(scan((acc, v) => acc + v, 0))
->subscribe(~next=x => Js.log2("scan", x), ());

let d =
  of1("delayed")
  ->pipe2(
      delayWhen(x => {
        Js.log2("delaying", x);
        timerDelay(1000);
      }),
      finalize(() => Js.log("finally")),
    );
d->subscribe(~next=x => Js.log(x), ());

d->toPromise |> then_(x => resolve(Js.log2("d promise", x)));

of2(2, 3)->pipe(repeat(2))->subscribe(~next=x => Js.log(x), ());

let rs = ReplaySubject.make(~bufferSize=5, ~windowTime=3000, ());
rs->ReplaySubject.next("a");
rs->ReplaySubject.next("b");
rs->ReplaySubject.next("c");

Js.Global.setTimeout(
  () =>
    rs->ReplaySubject.subscribe(~next=x => Js.log2("rs", x), ()) |> ignore,
  1000,
);

Js.log2("empty obs", Observable.empty);
Observable.empty->subscribe(
  ~next=x => Js.log2("empty", x),
  ~complete=() => Js.log("empty complete"),
  (),
);