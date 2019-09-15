open RxJs;
open Observable;
open Js.Promise;
open Operators;
open Observer;
open Expect_;
open Belt;

let of1 = a => of_([|a|]);
let of2 = (a, b) => of_([|a, b|]);
let of3 = (a, b, c) => of_([|a, b, c|]);
let of4 = (a, b, c, d) => of_([|a, b, c, d|]);

let o1 = fromArray([|1, 2, 3, 4, 5, 6|]);
o1
->pipe1(toArray())
->subscribe(
    ~next=arr => expectToEqual(arr, [|1, 2, 3, 4, 5, 6|]),
    ~complete=() => Js.log("o1 complete"),
    (),
  );

let o1 = fromString("HELLO");
o1
->pipe1(toArray())
->subscribe(
    ~next=arr => expectToEqual(arr, [|"H", "E", "L", "L", "O"|]),
    (),
  );

let o1 = fromString2("HELLO", asyncScheduler);
o1
->pipe1(toArray())
->subscribe(
    ~next=arr => expectToEqual(arr, [|"H", "E", "L", "L", "O"|]),
    (),
  );

let o1 = fromString2("HELLO", asyncScheduler);
o1
->Observable.pipe3(toArray(), tap(), tap())
// observeOnWithDelay(asyncScheduler, 100),
// subscribeOnWithDelay(queueScheduler, 100),
->subscribe(
    ~next=arr => expectToEqual(arr, [|"H", "E", "L", "L", "O"|]),
    (),
  );

let o1 = fromPromise(resolve("from promise"));
o1->subscribe(~next=x => expectToEqual(x, "from promise"), ());

let o1 = fromArray([|1, 2, 3|]);
o1
->pipe1(mapi((x, i) => (x + 10, i)))
->pipe1(toArray())
->subscribe(
    ~next=arr => expectToEqual(arr, [|(11, 0), (12, 1), (13, 2)|]),
    (),
  );

let o1 = fromArray([|1, 2, 3, 4|]);
o1
->pipe3(
    map(i => i + 20),
    filteri((x, i) => {
      expectToEqual(i->Js.typeof, "number");
      x mod 2 == 0;
    }),
    toArray(),
  )
->subscribe(~next=arr => expectToEqual(arr, [|22, 24|]), ());

let o1 = fromArray([|resolve("one"), resolve("two")|]);
let o2 = fromArray([|resolve("three"), resolve("four")|]);
concat([|o1, o2|])
->pipe2(concatAllP(), toArray())
->subscribe(
    ~next=arr => expectToEqual(arr, [|"one", "two", "three", "four"|]),
    (),
  );

let o1 = of_([|"one", "two"|]);
let o2 = of_([|"three", "four"|]);
concat([|o1, o2|])
->pipe1(toArray())
->subscribe(
    ~next=arr => expectToEqual(arr, [|"one", "two", "three", "four"|]),
    (),
  );

let o1 = of_([|"one", "two"|]);
let o2 = of_([|"three", "four"|]);
concat2S(o1, o2, asyncScheduler)
->pipe1(toArray())
->subscribe(
    ~next=arr => expectToEqual(arr, [|"one", "two", "three", "four"|]),
    (),
  );

let o1 = of_([|"one", "two"|]);
let o2 = of_([|"three", "four"|]);
concat2S(o1, o2, asyncScheduler)
->pipe1(toArray())
->subscribe(
    ~next=arr => expectToEqual(arr, [|"one", "two", "three", "four"|]),
    (),
  );

let s1 = of_([|"one", "two"|]);
let s2 = of_([|"three", "four"|]);
let s3 = of_([|"a", "b"|]);
let s4 = of_([|"c"|]);

concat([|s1, s2, s3, s4|])
->pipe1(toArray())
->subscribe(
    ~next=
      x =>
        expectToEqual(x, [|"one", "two", "three", "four", "a", "b", "c"|]),
    (),
  );

let o1 = fromArray([|51, 52, 53|]);
let o2 = fromArray([|"green", "red"|]);
forkJoin2(o1, o2)
->subscribe(
    ~next=
      ((a, b)) => {
        expectToEqual(a, 53);
        expectToEqual(b, "red");
      },
    (),
  );

let o1 = of_([|"A"|]);
forkJoin([|o1|])->subscribe(~next=x => expectToEqual(x, [|"A"|]), ());

let o1 = fromArray([|1, 2, 3, 4|]);
let o2 = fromArray([|51, 52, 53|]);
merge([|o1, o2|])
->pipe1(toArray())
->subscribe(
    ~next=arr => expectToEqual(arr, [|1, 2, 3, 4, 51, 52, 53|]),
    (),
  );

let o1 = fromArray([|1, 2, 3, 4|]);
let o2 = fromArray([|51, 52, 53|]);
merge2CS(o1, o2, 2, asyncScheduler)
->pipe1(toArray())
->subscribe(
    ~next=arr => expectToEqual(arr, [|1, 2, 3, 4, 51, 52, 53|]),
    (),
  );

let o1 = range2(~start=456, ~count=3)->pipe2(pairwise(), toArray());
o1->subscribe(
  ~next=arr => expectToEqual(arr, [|(456, 457), (457, 458)|]),
  (),
);

let o1 = range3(~start=0, ~count=3, asyncScheduler)->pipe1(toArray());
o1->subscribe(~next=arr => expectToEqual(arr, [|0, 1, 2|]), ());

let o1 = fromArray([|2, 4|]);
o1
->pipe1(every(x => x mod 2 == 0))
->subscribe(~next=x => expectToEqual(x, true), ());

let o1 = fromArray([|2, 3, 4|]);
o1
->pipe1(every(x => x mod 2 == 0))
->subscribe(~next=x => expectToEqual(x, false), ());

let o1 = concat([|of1("a"), throwError("oops")|])->pipe1(retry1(3));
o1->subscribe(
  ~next=x => Js.log(x),
  ~error=e => expectToEqual(e, Js.Json.string("oops")),
  (),
);

o1
->pipe2(
    Operators.catchError((x, o) => {
      expectToEqual(o->Js.typeof, "object");
      of_([|"caught " ++ x->Js.Json.decodeString->Belt.Option.getExn|]);
    }),
    toArray(),
  )
->subscribe(
    ~next=arr => expectToEqual(arr, [|"a", "a", "a", "a", "caught oops"|]),
    ~error=_ => failwith("fail"),
    (),
  );

range2(~start=100, ~count=30)
->pipe2(bufferCount(7), first1D([||]))
->subscribe(
    ~next=arr => expectToEqual(arr, [|100, 101, 102, 103, 104, 105, 106|]),
    (),
  );

let o1 = of4(1, 2, 3, 4);
o1
->pipe1(first1(x => x == 3))
->subscribe(~next=x => expectToEqual(x, 3), ());

let o1 = of4(1, 2, 3, 4);
o1
->pipe1(first2(x => x == 5, 6))
->subscribe(~next=x => expectToEqual(x, 6), ());

let o1 = of4(1, 2, 3, 4);
o1
->pipe1(first1(x => x == 5))
->subscribe(
    ~next=x => expectToEqual(x, 6),
    ~error=_ => (),
    //    failwith("should fail")
    (),
  );

of4(5, 6, 7, 8)
->pipe2(concatMap(x => of1(x + 1)), toArray())
->subscribe(~next=arr => expectToEqual(arr, [|6, 7, 8, 9|]), ());

of2("a", "b")
->pipe2(
    concatMapi((x, i) => {
      expectToEqual(i->Js.typeof, "number");
      of1(x ++ x);
    }),
    toArray(),
  )
->subscribe(~next=arr => expectToEqual(arr, [|"aa", "bb"|]), ());

of3(1, 2, 3)
->pipe2(concatMapTo(of1("mappedto")), toArray())
->subscribe(
    ~next=arr => expectToEqual(arr, [|"mappedto", "mappedto", "mappedto"|]),
    (),
  );

of1("hello")
->pipe3(
    expandi((x, i) => {
      expectToEqual(i->Js.typeof, "number");
      of1(x ++ "!");
    }),
    take(3),
    toArray(),
  )
->subscribe(
    ~next=arr => expectToEqual(arr, [|"hello", "hello!", "hello!!"|]),
    (),
  );

of3(
  {"name": "jane", "age": 20},
  {"name": "john", "age": 21},
  {"name": "rick", "age": 20},
)
->pipe3(
    groupBy(x => x##age),
    mergeMapi((g, i) => {
      expectToEqual(i->Js.typeof, "number");
      g->pipe1(toArray());
    }),
    toArray(),
  )
->subscribe(
    ~next=
      arr =>
        expectToEqual(
          arr,
          [|
            [|{"name": "jane", "age": 20}, {"name": "rick", "age": 20}|],
            [|{"name": "john", "age": 21}|],
          |],
        ),
    (),
  );

range2(~start=1, ~count=10)
->pipe2(
    reducei(
      (acc, v, i) => {
        expectToEqual(i->Js.typeof, "number");
        acc + v;
      },
      0,
    ),
    tap(~next=x => Js.log2("tap", x), ()),
  )
->subscribe(~next=x => expectToEqual(x, 55), ());

range2(~start=1, ~count=3)
->pipe1(
    reducei(
      (acc, v, i) => {
        expectToEqual(i->Js.typeof, "number");
        acc ++ "-" ++ string_of_int(v);
      },
      "",
    ),
  )
->subscribe(~next=x => expectToEqual(x, "-1-2-3"), ());

of3(
  {"name": "jane", "age": 20},
  {"name": "john", "age": 22},
  {"name": "rick", "age": 22},
)
->pipe3(
    groupBy(x => x##age),
    flatMapi((g, i) => {
      expectToEqual(i->Js.typeof, "number");
      g->pipe1(
        reducei(
          (acc, cur, i) => {
            expectToEqual(i->Js.typeof, "number");
            acc |> Js.Array.concat([|cur|]);
          },
          [||],
        ),
      );
    }),
    toArray(),
  )
->subscribe(
    ~next=
      arr =>
        expectToEqual(
          arr,
          [|
            [|{"name": "jane", "age": 20}|],
            [|{"name": "john", "age": 22}, {"name": "rick", "age": 22}|],
          |],
        ),
    (),
  );

let (a, b) =
  range2(~start=10, ~count=10)
  ->pipe1(
      partition((x, i) => {
        expectToEqual(i->Js.typeof, "number");
        x mod 2 == 0;
      }),
    );
a
->pipe1(toArray())
->subscribe(~next=x => expectToEqual(x, [|10, 12, 14, 16, 18|]), ());

b
->pipe1(toArray())
->subscribe(~next=x => expectToEqual(x, [|11, 13, 15, 17, 19|]), ());

range2(~start=1, ~count=3)
->pipe2(
    scani(
      (acc, v, i) => {
        expectToEqual(i->Js.typeof, "number");
        acc + v;
      },
      0,
    ),
    toArray(),
  )
->subscribe(~next=x => expectToEqual(x, [|1, 3, 6|]), ());

let o1 =
  of1("delayed")
  ->pipe2(
      delayWhen2(
        (x, i) => {
          expectToEqual(i->Js.typeof, "number");
          Js.log2("delaying", x);
          timer2S(1000.0, asyncScheduler);
        },
        timer(),
      ),
      finalize(() => Js.log("finally")),
    );
o1->subscribe(~next=x => expectToEqual(x, "delayed"), ());

o1->toPromise |> then_(x => resolve(expectToEqual(x, "delayed")));

of2(2, 3)
->pipe2(repeat(2), toArray())
->subscribe(~next=x => expectToEqual(x, [|2, 3, 2, 3|]), ());

let o1 = ReplaySubject.make2(~bufferSize=5, ~windowTime=1000.0);
let o2 = o1->ReplaySubject.asObservable;

let o1 = o1->ReplaySubject.asObserver;
o1->next("a");
o1->next("b");

o1->next("c");
o1->complete;

Js.Global.setTimeout(
  () =>
    o2
    ->pipe1(toArray())
    ->subscribe(~next=x => expectToEqual(x, [|"a", "b", "c"|]), ())
    |> ignore,
  500,
);

empty->subscribe(
  ~next=_ => failwith("fail"),
  ~complete=() => Js.log("empty complete"),
  (),
);

let o1 = of3(1, 2, 3);
let o2 = of2(4, 5);
let o3 = of4(6, 7, 8, 9);
let o4 = of3(o1, o2, o3)->pipe2(combineAll(), take(1));
o4->subscribe(~next=arr => expectToEqual(arr, [|3, 5, 6|]), ());

let o1 = of3(1, 2, 3);
let o2 = of2(4, 5);
let o3 = of2(o1, o2);
o3
->pipe2(mergeAll(), toArray())
->subscribe(~next=arr => expectToEqual(arr, [|1, 2, 3, 4, 5|]), ());

let o1 = timer1(500.0);
o1->subscribe(~next=x => expectToEqual(x, 0), ());

let o1 = of1("A")->pipe1(delayWhen((_, _) => timer1(300.0)));
let o2 = of1("B")->pipe1(delayWhen((_, _) => timer1(100.0)));
let o3 = RxJs.race([|o1, o2|]);
o3->subscribe(~next=x => expectToEqual(x, "B"), ());

let o1 = of3(3, 4, 5);
let o2 = o1->pipe2(startWith([|2|]), toArray());
o2->subscribe(~next=arr => expectToEqual(arr, [|2, 3, 4, 5|]), ());

let o1 = interval(50.0)->pipe1(take(4));
let o2 = of1(300);
o1
->pipe2(withLatestFrom1(o2), toArray())
->subscribe(
    ~next=
      arr =>
        expectToEqual(arr, [|(0, 300), (1, 300), (2, 300), (3, 300)|]),
    (),
  );

let o1 = interval(50.0)->pipe1(take(4));
let o2 = of1(300);
o1
->pipe2(withLatestFrom([|o2|]), toArray())
->subscribe(
    ~next=
      arr =>
        expectToEqual(
          arr,
          [|[|0, 300|], [|1, 300|], [|2, 300|], [|3, 300|]|],
        ),
    (),
  );

let o1 = of2("a", "b");
let o2 = of1(false);
let o3 = of1(123);
let o4 = of1({"x": "y"});
let o5 = of1(17.2);

o1
->pipe2(withLatestFrom4(o2, o3, o4, o5), toArray())
->subscribe(
    ~next=
      arr =>
        expectToEqual(
          arr,
          [|
            ("a", false, 123, {"x": "y"}, 17.2),
            ("b", false, 123, {"x": "y"}, 17.2),
          |],
        ),
    (),
  );

let o1 = of2("a", "b");
let o2 = of3(2, 3, 4);
zip2(o1, o2)
->pipe1(toArray())
->subscribe(~next=arr => expectToEqual(arr, [|("a", 2), ("b", 3)|]), ());

let o1 = of2("a", "b");
let o2 = of3(2, 3, 4);
zip2R(o1, o2, (a, b) => (b, a))
->pipe1(toArray())
->subscribe(~next=arr => expectToEqual(arr, [|(2, "a"), (3, "b")|]), ());

let o1 = of2("a", "b");
let o2 = of3("C", "D", "E");
let o3 = of2("X", "Y");
zip([|o1, o2, o3|])
->pipe2(toArray(), take(2))
->subscribe(
    ~next=
      arr => expectToEqual(arr, [|[|"a", "C", "X"|], [|"b", "D", "Y"|]|]),
    (),
  );

let o1 = empty;
o1
->pipe1(defaultIfEmpty("qqq"))
->subscribe(~next=x => expectToEqual(x, "qqq"), ());

let o1 = of1("A");
let o2 = of1("B");
iif(() => false, ~true_=o1, ~false_=o2)
->subscribe(~next=x => expectToEqual(x, "B"), ());

iifP(() => true, ~true_=resolve("C"), ~false_=resolve(""))
->subscribe(~next=x => expectToEqual(x, "C"), ());

let o1 = fromArray([|4, 5, 6|]);
fromArray([|4, 5, 6|])
->pipe1(sequenceEqual(o1))
->subscribe(~next=x => expectToEqual(x, true), ());

let comparator = (a, b) =>
  if (a == 1) {
    false;
  } else {
    a == b;
  };

let o1 = fromArray([|4, 5, 6|]);
fromArray([|4, 5, 6|])
->pipe1(sequenceEqual2(o1, comparator))
->subscribe(~next=x => expectToEqual(x, true), ());

let o1 = fromArray([|1, 5, 6|]);
fromArray([|1, 5, 6|])
->pipe1(sequenceEqual2(o1, comparator))
->subscribe(~next=x => expectToEqual(x, false), ());

Observable.make(obs => {
  obs->Observer.next("q");
  Js.Global.setTimeout(
    () => {
      obs->Observer.next("a");
      obs->Observer.next("z");
      obs->Observer.complete;
    },
    500,
  )
  |> ignore;
  None;
})
->pipe1(toArray())
->subscribe(~next=arr => expectToEqual(arr, [|"q", "a", "z"|]), ());

let makeEventTarget: unit => (Dom.eventTarget, string => unit) = [%raw
  {|
function(emit) {
  var listeners = [];
  var et = {
    addEventListener: (e, l) => {
      //console.log("addEventListener");
      listeners.push(l);
    },
    removeEventListener: (e, l) => {
      // console.log("removeEventListener");
      var i = listeners.indexOf(l);
      listeners.splice(i, 1);
    }
  };

  var emit = x => {
    //console.log("emit", x);
    listeners.forEach(l => l(x));
  };

  return [ et, emit ];
}
|}
];
let (et1, emit) = makeEventTarget();

let o1 = fromEvent(et1, "any");
o1
->pipe2(take(2), toArray())
->subscribe(~next=arr => expectToEqualAny(arr, [|"T", "Y"|]), ());

emit("T");
Js.Global.setTimeout(() => emit("Y"), 500);

let d1 = Js.Date.now() +. 500.0 |> Js.Date.fromFloat;
let o1 = timerD2(d1, ~period=100.0);
o1
->pipe2(take(3), toArray())
->subscribe(~next=arr => expectToEqual(arr, [|0, 1, 2|]), ());

/* bad test */
let i1 = ref(0);
let o2 =
  Observable.make(obs => {
    if (i1^ == 0) {
      i1 := 1;
      failwith("f");
    } else {
      obs->Observer.next("d");
    };
    None;
  });
let o1 = of3("a", "b", "c");
let o3 = of1("e");
concat([|o1, o2, o3|])
->pipe2(
    retryWhen(errs => {
      errs->subscribe(~next=x => expectToEqualAny(x, Failure("f")), ())
      |> ignore;

      timer1(500.0);
    }),
    toArray(),
  )
->subscribe(
    ~next=arr => expectToEqual(arr, [|"a", "b", "c", "a", "b", "c", "d"|]),
    (),
  );

let o1 =
  Observable.make(obs => {
    obs->Observer.next("a");
    obs->Observer.next("b");

    Js.Global.setTimeout(
      () => {
        obs->Observer.next("c");
        obs->Observer.next("d");
        obs->Observer.complete;
      },
      500,
    )
    |> ignore;
    None;
  })
  ->pipe2(publish(), refCount());

/* DO NOT DELETE, connect required without refCount */

/* Js.Global.setTimeout(
     () =>
       o1
       ->ConnectableasConnectableObservable
       ->Belt.Option.getExn
       ->Connectableconnect,
     500,
   )
   |> ignore; */

o1
->pipe1(toArray())
->subscribe(~next=arr => expectToEqual(arr, [|"a", "b", "c", "d"|]), ());
/////////////////

let o1 =
  Observable.make(obs => {
    obs->Observer.next(1);
    obs->Observer.next(2);

    Js.Global.setTimeout(
      () => {
        obs->Observer.next(3);
        obs->Observer.next(4);
        obs->Observer.complete;
      },
      500,
    )
    |> ignore;
    None;
  })
  ->pipe1(publish1(map(x => string_of_int(x) ++ string_of_int(x))));

o1
->pipe1(toArray())
->subscribe(
    ~next=arr => expectToEqual(arr, [|"11", "22", "33", "44"|]),
    (),
  );

//////////////

let o1 =
  Observable.make(obs => {
    obs->Observer.next("a");
    obs->Observer.next("b");

    Js.Global.setTimeout(
      () => {
        obs->Observer.next("c");
        obs->Observer.next("d");
        obs->Observer.complete;
      },
      500,
    )
    |> ignore;
    None;
  })
  ->pipe1(publishBehavior("q"));

Js.Global.setTimeout(
  () => {
    let s = o1->ConnectableObservable.connect;

    s->Subscription.unsubscribe;
    expectToEqual(s->Js.typeof, "object");
  },
  500,
)
|> ignore;

o1
->ConnectableObservable.asObservable
->pipe1(toArray())
// ->ConnectableObservable.pipe1(toArray())
->subscribe(
    ~next=arr => expectToEqual(arr, [|"q", "a", "b", "c", "d"|]),
    (),
  );

let c = ref(false);

let o1 =
  Observable.make(obs => {
    obs->Observer.next("a");
    obs->Observer.next("b");

    Js.Global.setTimeout(
      () => {
        obs->Observer.next("c");
        obs->Observer.next("d");
        obs->Observer.complete;
      },
      0,
    )
    |> ignore;
    None;
  })
  ->pipe1(publishLast());

Js.Global.setTimeout(() => o1->ConnectableObservable.connect->ignore, 0)
|> ignore;

o1
->ConnectableObservable.asObservable
->pipe1(toArray())
->subscribe(
    ~next=arr => expectToEqual(arr, [|"d"|]),
    ~complete=() => c := true,
    (),
  );

Js.Global.setTimeout(() => expectToEqual(c^, true), 1000) |> ignore;

/* test does not verify that params are working (bufferSize and windowTime) */
let o1 =
  Observable.make(obs => {
    obs->Observer.next("a");
    obs->Observer.next("b");

    Js.Global.setTimeout(
      () => {
        obs->Observer.next("c");
        obs->Observer.next("d");
        obs->Observer.complete;
      },
      500,
    )
    |> ignore;
    None;
  })
  ->pipe1(publishReplay1(~bufferSize=1));

Js.Global.setTimeout(
  () =>
    o1
    ->ConnectableObservable.asConnectableObservable
    ->Belt.Option.getExn
    ->ConnectableObservable.connect
    ->ignore,
  500,
)
|> ignore;

o1
->pipe1(toArray())
->subscribe(~next=arr => expectToEqual(arr, [|"a", "b", "c", "d"|]), ());
////////////////
let s1 = Subject.make();

let o1 =
  Observable.make(obs => {
    obs->Observer.next("a");
    obs->Observer.next("b");

    Js.Global.setTimeout(
      () => {
        obs->Observer.next("c");
        obs->Observer.next("d");
        obs->Observer.complete;
      },
      500,
    )
    |> ignore;
    None;
  })
  ->pipe1(multicast(() => s1));

let co1 =
  o1->ConnectableObservable.asConnectableObservable->Belt.Option.getExn;

co1->ConnectableObservable.connect;

expectToEqual(
  co1
  ->ConnectableObservable.getSubject
  ->Subject.asObservable
  ->Subject.asSubject
  ->Belt.Option.isSome,
  true,
);

o1
->pipe1(toArray())
->subscribe(~next=arr => expectToEqual(arr, [|"c", "d"|]), ());
/////////////////

let s1 = Subject.make();

let o1 =
  Observable.make(obs => {
    obs->Observer.next("a");
    obs->Observer.next("b");

    Js.Global.setTimeout(
      () => {
        obs->Observer.next("c");
        obs->Observer.next("d");
        obs->Observer.complete;
      },
      500,
    )
    |> ignore;
    None;
  })
  ->pipe1(multicast2(() => s1, x => x->pipe1(map(x => x ++ x))));

// not connectable

o1
->pipe1(toArray())
->subscribe(
    ~next=arr => expectToEqual(arr, [|"aa", "bb", "cc", "dd"|]),
    (),
  );
////////////////

let o1 =
  Observable.make(obs => {
    obs->Observer.next("a");
    obs->Observer.next("b");

    Js.Global.setTimeout(
      () => {
        obs->Observer.next("c");
        obs->Observer.next("d");
        obs->Observer.complete;
      },
      500,
    )
    |> ignore;
    None;
  })
  ->pipe1(share());

o1
->pipe1(toArray())
->subscribe(~next=arr => expectToEqual(arr, [|"a", "b", "c", "d"|]), ());

Observable.make(obs => {
  obs->Observer.next("a");
  obs->Observer.next("b");

  Js.Global.setTimeout(
    () => {
      obs->Observer.next("c");
      obs->Observer.next("d");
      obs->Observer.complete;
    },
    500,
  )
  |> ignore;
  None;
})
->pipe2(shareReplay1(~bufferSize=3), toArray())
->subscribe(~next=arr => expectToEqual(arr, [|"a", "b", "c", "d"|]), ());

/* bad test because of concurrency issues, simplified to checking length */
interval(50.0)
->pipe3(audit(_ => timer1(100.0)), take(10), toArray())
->subscribe(~next=arr => expectToEqual(arr->Js.Array.length > 5, true), ());

/* bad test because of concurrency issues, simplified to checking length */
interval(50.0)
->pipe3(auditP(_ => resolve("x")), take(10), toArray())
->subscribe(~next=arr => expectToEqual(arr->Js.Array.length > 5, true), ());

/* bad test because of concurrency issues, simplified to checking length */
interval(50.0)
->pipe3(auditTime2(100.0, asapScheduler), take(10), toArray())
->subscribe(~next=arr => expectToEqual(arr->Js.Array.length > 5, true), ());

Observable.make(obs => {
  obs->Observer.next(1);
  obs->Observer.next(2);
  Js.Global.setTimeout(
    () => {
      obs->Observer.next(3);
      Js.Global.setTimeout(() => obs->Observer.next(4), 150) |> ignore;
    },
    50,
  )
  |> ignore;
  None;
})
->pipe3(debounce(() => timer1(100.0)), take(1), toArray())
->subscribe(~next=arr => expectToEqual(arr, [|3|]), ());

Observable.make(obs => {
  obs->Observer.next(1);
  obs->Observer.next(2);
  Js.Global.setTimeout(
    () => {
      obs->Observer.next(3);
      Js.Global.setTimeout(() => obs->Observer.next(4), 150) |> ignore;
    },
    50,
  )
  |> ignore;
  None;
})
->pipe3(debounceTime2(100.0, asyncScheduler), take(1), toArray())
->subscribe(~next=arr => expectToEqual(arr, [|3|]), ());

fromArray([|1, 1, 2, 2, 3, 1, 2, 3|])
->pipe2(distinctUntilChanged(), toArray())
->subscribe(~next=arr => expectToEqual(arr, [|1, 2, 3, 1, 2, 3|]), ());

of1("a")
->pipe1(ignoreElements())
->subscribe(
    ~next=_ => failwith("fail"),
    ~error=_ => failwith("fail"),
    ~complete=() => Js.log("ignoreElements OK"),
    (),
  );

of3("a", "b", "c")
->pipe1(last1D("d"))
->subscribe(~next=x => expectToEqual(x, "c"), ());

of3("a", "b", "c")
->pipe1(lasti2((x, _, _) => x == "x", "d"))
->subscribe(~next=x => expectToEqual(x, "d"), ());

/* bad test */
interval(500.0)
->pipe3(sample(interval(1000.0)), take(2), toArray())
->subscribe(~next=arr => expectToEqual(arr->Js.Array.length > 0, true), ());

/* bad test */
interval(500.0)
->pipe3(sampleTime2(1000.0, queueScheduler), take(2), toArray())
->subscribe(~next=arr => expectToEqual(arr->Js.Array.length > 0, true), ());

range2(~start=1, ~count=20)
->pipe3(
    singlei((x, i, o) => {
      expectToEqual(i->Js.typeof, "number");
      expectToEqual(o->Js.typeof, "object");
      x == 17;
    }),
    map(x => x + 1),
    toArray(),
  )
->subscribe(~next=arr => expectToEqual(arr, [|18|]), ());

range2(~start=1, ~count=20)
->pipe2(skip(17), toArray())
->subscribe(~next=arr => expectToEqual(arr, [|18, 19, 20|]), ());

/* bad test */
let o1 = timer1(1000.0);
interval(500.0)
->pipe3(skipUntil(o1), take(2), toArray())
->subscribe(~next=arr => expectToEqual(arr->Js.Array.length > 0, true), ());

let o1 = timer1(1000.0);
interval(600.0)
->pipe3(takeUntil(o1), take(2), toArray())
->subscribe(~next=arr => expectToEqual(arr, [|0|]), ());

range2(~start=1, ~count=20)
->pipe3(skipWhile(x => x < 5), take(2), toArray())
->subscribe(~next=arr => expectToEqual(arr, [|5, 6|]), ());

/* bad test */
range2(~start=1, ~count=20)
->pipe3(takeWhile(x => x < 5), take(2), toArray())
->subscribe(~next=arr => expectToEqual(arr->Js.Array.length > 0, true), ());

/* bad test */
timer2(0.0, ~period=200.0)
->pipe3(throttle(_ => timer1(210.0)), take(2), toArray())
->subscribe(~next=arr => expectToEqual(arr->Js.Array.length > 0, true), ());

/* bad test */
timer2(0.0, ~period=200.0)
->pipe3(throttleP(_ => resolve(210)), take(2), toArray())
->subscribe(~next=arr => expectToEqual(arr, [|0, 1|]), ());

/* bad test */
timer2(0.0, ~period=200.0)
->pipe3(
    throttleTime3(
      210.0,
      asyncScheduler,
      {"leading": false, "trailing": true},
    ),
    take(2),
    toArray(),
  )
->subscribe(~next=arr => expectToEqual(arr->Js.Array.length > 0, true), ());

let o1 = timer1(1000.0);
interval(220.0)
->pipe1(buffer(o1))
->subscribe(~next=arr => expectToEqual(arr, [|0, 1, 2, 3|]), ());

interval(220.0)
->pipe2(
    bufferTime4(
      ~bufferTimeSpan=1000.0,
      ~bufferCreationInterval=Some(500.0),
      ~maxBufferSize=2,
      queueScheduler,
    ),
    take(10),
  )
->subscribe(~next=arr => expectToEqual(arr->Js.Array.length == 2, true), ());

let o1 =
  Observable.make(obs => {
    let t =
      interval(100.0)->subscribe(~next=i => obs->Observer.next(i), ());

    Js.Global.setTimeout(
      () => {
        obs->Observer.complete;
        t->Subscription.unsubscribe;
      },
      1000,
    )
    |> ignore;
    None;
  });

o1
->pipe2(
    bufferToggle(
      timer2(0.0, ~period=50.0),
      i => {
        expectToEqual(i->Js.typeof, "number");
        timer1(500.0);
      },
    ),
    first1D([||]),
  )
->subscribe(~next=arr => expectToEqual(arr->Js.Array.length > 0, true), ());

o1
->pipe2(bufferToggleP(resolve("a"), _ => resolve("b")), first1D([||]))
->subscribe(~next=arr => expectToEqual(arr->Js.Array.length > 0, false), ());

let o1 =
  Observable.make(obs => {
    let t =
      interval(500.0)->subscribe(~next=i => obs->Observer.next(i), ());

    Js.Global.setTimeout(
      () => {
        obs->Observer.complete;
        t->Subscription.unsubscribe;
      },
      1000,
    )
    |> ignore;
    None;
  });

interval(50.0)
->pipe3(bufferWhen(() => o1), take(3), toArray())
->subscribe(~next=arr => expectToEqual(arr->Js.Array.length > 0, true), ());

let o1 = of3(1, 2, 3);
let o2 = of2(4, 5);
let o3 = of2(o1, o2);
o3
->pipe2(exhaust(), toArray())
->subscribe(~next=arr => expectToEqual(arr, [|1, 2, 3, 4, 5|]), ());

let o1 = interval(10.0)->pipe2(map(string_of_int), take(10));
let o2 = interval(10.0)->pipe2(mapi((i, _) => {"i": i}), take(2));

o1
->pipe1(
    exhaustMapi2(
      (f, i) => {
        Js.log3("f i", f, i);
        expectToEqual(f->Js.typeof, "string");
        expectToEqual(i->Js.typeof, "number");
        o2;
      },
      (
        ~outerValue: string,
        ~innerValue: {. "i": int},
        ~outerIndex: int,
        ~innerIndex: int,
      ) => {
        Js.log4(outerValue, innerValue, outerIndex, innerIndex);
        expectToEqual(outerValue->Js.typeof, "string");
        expectToEqual(innerValue->Js.typeof, "object");
        expectToEqual(innerValue##i->Js.typeof, "number");
        expectToEqual(outerIndex->Js.typeof, "number");
        expectToEqual(innerIndex->Js.typeof, "number");

        true;
      },
    ),
  )
->subscribe(
    ~next=
      x => {
        Js.log2("next", x);
        expectToEqual(x->Js.typeof, "boolean");
      },
    (),
  );

of2(1, 2)
->pipe2(mapTo("a"), toArray())
->subscribe(~next=arr => expectToEqual(arr, [|"a", "a"|]), ());

let o1 =
  of1({
    "result": {
      "user": {
        "address": {
          "street": "Roscoe",
        },
        "name": "Max",
      },
    },
  });

let undef: Js.Json.t = [%raw "undefined"];

o1
->pipe1(pluck([|"result", "user", "address", "street"|]))
->subscribe(~next=x => expectToEqualAny(x, "Roscoe"), ());

o1
->pipe1(pluck([|"result", "user", "address", "nam"|]))
->subscribe(~next=x => expectToEqual(x, undef), ());

of2("a", "b")
->pipe2(switchMapi((x, i) => of2(x, i->string_of_int)), toArray())
->subscribe(~next=arr => expectToEqual(arr, [|"a", "0", "b", "1"|]), ());

let o2 = of2("c", "d");
of2(3, 4)
->pipe2(switchMapTo(o2), toArray())
->subscribe(~next=arr => expectToEqual(arr, [|"c", "d", "c", "d"|]), ());

let o1 = interval(50.0);
let o2 = interval(200.0);
o1
->pipe4(window(o2), flatMap(x => x), take(10), toArray())
->subscribe(
    ~next=
      arr => {
        expectToEqual(arr->Js.Array.length, 10);
        expectToEqual(arr->Belt.Array.getUnsafe(0), 0);
      },
    (),
  );

let o1 = interval(50.0);
o1
->pipe2(windowCount2(~windowSize=5, ~startWindowEvery=2), take(10))
->subscribe(
    ~next=
      o =>
        o
        ->pipe2(take(10), toArray())
        ->subscribe(
            ~next=
              x => {
                expectToEqual(x->Js.Array.length >= 2, true);
                expectToEqual(x->Js.Array.length <= 5, true);
              },
            (),
          )
        |> ignore,
    (),
  );

let o1 = interval(50.0);
o1
->pipe4(windowTime(200), flatMap(x => x), take(10), toArray())
->subscribe(
    ~next=
      arr => {
        expectToEqual(arr->Js.Array.length, 10);
        expectToEqual(arr->Belt.Array.getUnsafe(0), 0);
      },
    (),
  );

let o1 =
  Observable.make(obs => {
    let t =
      interval(100.0)->subscribe(~next=i => obs->Observer.next(i), ());

    Js.Global.setTimeout(
      () => {
        obs->Observer.complete;
        t->Subscription.unsubscribe;
      },
      1000,
    )
    |> ignore;
    None;
  });

o1
->pipe1(
    windowToggle(
      timer1(50.0),
      i => {
        expectToEqual(i->Js.typeof, "number");
        timer1(50.0);
      },
    ),
  )
->subscribe(
    ~next=
      o =>
        o
        ->pipe2(take(10), toArray())
        ->subscribe(~next=x => expectToEqual(x->Js.Array.isArray, true), ())
        |> ignore,
    (),
  );

interval(20.0)
->pipe2(windowWhen(() => interval(100.0)), take(10))
->subscribe(
    ~next=
      o =>
        o
        ->pipe2(take(10), toArray())
        ->subscribe(~next=x => expectToEqual(x->Js.Array.isArray, true), ())
        |> ignore,
    (),
  );

of1("del")
->pipe1(delay(10.0))
->subscribe(~next=x => expectToEqual(x, "del"), ());

/* DO NOT DELETE */
/* throwError(1)
   ->pipe1(finalize(() => Js.log("finalize on err")))
   ->subscribe(~next=_ => (), ()); */

of1("a")
->pipe1(timeout2(5.0, asyncScheduler))
->subscribe(~next=x => expectToEqual(x, "a"), ());

of2("a", "b")
->pipe1(elementAt(1))
->subscribe(~next=x => expectToEqual(x, "b"), ());

of2("a", "b")
->pipe1(elementAt(2))
->subscribe(
    ~next=x => expectToEqual(x, "y"),
    ~error=_ => Js.log("expected error"),
    (),
  );

of2("a", "b")
->pipe1(elementAt2(2, "y"))
->subscribe(~next=x => expectToEqual(x, "y"), ());

of2("b", "c")
->pipe3(
    endWith([|"d", "e", "f", "g", "z"|]),
    startWith([|"_", "a"|]),
    toArray(),
  )
->subscribe(
    ~next=
      x => expectToEqual(x, [|"_", "a", "b", "c", "d", "e", "f", "g", "z"|]),
    (),
  );

of2("b", "c")
->pipe3(
    endWith4S("d", "e", "f", "g", asyncScheduler, ()),
    startWith2S("_", "a", asyncScheduler),
    toArray(),
  )
->subscribe(
    ~next=x => expectToEqual(x, [|"_", "a", "b", "c", "d", "e", "f", "g"|]),
    (),
  );

of3("a", "b", "c")
->pipe1(
    findi((x, i, o) => {
      expectToEqual(i->Js.typeof, "number");
      expectToEqual(o->Js.typeof, "object");
      x == "b";
    }),
  )
->subscribe(~next=x => expectToEqual(x, Some("b")), ());

of3("a", "b", "c")
->pipe1(
    findi((_, i, o) => {
      expectToEqual(i->Js.typeof, "number");
      expectToEqual(o->Js.typeof, "object");
      false;
    }),
  )
->subscribe(~next=x => expectToEqual(x, None), ());

of3("a", "b", "c")
->pipe1(
    findIndexi((x, i, o) => {
      expectToEqual(i->Js.typeof, "number");
      expectToEqual(o->Js.typeof, "object");
      x == "b";
    }),
  )
->subscribe(~next=x => expectToEqual(x, 1), ());

of3("a", "b", "c")
->pipe1(
    findIndexi((_, i, o) => {
      expectToEqual(i->Js.typeof, "number");
      expectToEqual(o->Js.typeof, "object");
      false;
    }),
  )
->subscribe(~next=x => expectToEqual(x, -1), ());

of1("a")
->pipe1(isEmpty())
->subscribe(~next=x => expectToEqual(x, false), ());

empty->pipe1(isEmpty())->subscribe(~next=x => expectToEqual(x, true), ());

of3(1, 2, 3)
->pipe1(max1((a, b) => a - b |> float_of_int))
->subscribe(~next=x => expectToEqual(x, 3), ());

of3(1, 4, 3)
->pipe1(max1((a, b) => a - b |> float_of_int))
->subscribe(~next=x => expectToEqual(x, 4), ());

of3(1, 4, 3)
->pipe1(min1((a, b) => a - b |> float_of_int))
->subscribe(~next=x => expectToEqual(x, 1), ());

let o1 = of2("a", "b");
let o2 = of3("c", "d", "e");
of2(o1, o2)
->pipe2(switchAll(), toArray())
->subscribe(~next=x => expectToEqual(x, [|"a", "b", "c", "d", "e"|]), ());

let o1 = of2("a", "b");
let o2: Observable.t(string) = throwError("err");
let o3 = of3("c", "d", "e");
o1
->pipe1(onErrorResumeNext([|o2, o3|]))
->pipe1(toArray())
->subscribe(~next=x => expectToEqual(x, [|"a", "b", "c", "d", "e"|]), ());

let op1 = src =>
  Observable.make(obs => {
    let s =
      src->subscribe(
        ~next=
          x => {
            Js.log2("xxxxxxx", x);
            obs->Observer.next(x ++ "!");
          },
        ~error=
          e => {
            Js.log("src err");

            obs->Observer.error(e);
          },
        ~complete=
          () => {
            Js.log("src complete");
            obs->Observer.complete;
          },
        (),
      );

    Some(() => s->Subscription.unsubscribe);
  });

of3("a", "b", "c")
->pipe3(
    op1,
    mapi((x, _) => {
      Js.log(x);
      x ++ x;
    }),
    toArray(),
  )
->subscribe(~next=x => expectToEqual(x, [|"a!a!", "b!b!", "c!c!"|]), ());

let o1 =
  Observable.make(obs => {
    obs->Observer.next("a");
    Some(() => Js.log("teardown OK"));
  });
let s = o1->subscribe();
s->Subscription.unsubscribe;

expectToEqual(
  empty->ConnectableObservable.asConnectableObservable->Belt.Option.isSome,
  false,
);

empty
->pipe2(
    throwIfEmpty1(() => failwith("custom err")),
    catchError((err, _) => {
      expectToEqualAny(err, Failure("custom err"));
      of1("x");
    }),
  )
->subscribe(~next=x => expectToEqual(x, "x"), ());

/* empty does not work */
Observable.make(_ => None)
->pipe1(timeoutWith3(100.0, of1("a"), queueScheduler))
->subscribe(
    ~next=x => expectToEqual(x, "a"),
    ~error=_ => failwith("fail"),
    (),
  );

of1("a")
->pipe1(timestamp1(asapScheduler))
->subscribe(
    ~next=
      x => {
        Js.log(x);
        expectToEqual(x##value, "a");
        expectToEqual(x##timestamp->Js.typeof, "number");
      },
    (),
  );

of_([|"a", "a", "b", "b", "b", "c"|])
->pipe2(
    distinctUntilChanged1((a, b) =>
      if (a == "a") {
        false;
      } else {
        a == b;
      }
    ),
    toArray(),
  )
->subscribe(~next=x => expectToEqual(x, [|"a", "a", "b", "c"|]), ());

/* README */
let observable =
  Observable.make(observer => {
    // open Observer;

    observer->next(1);
    observer->next(2);
    observer->next(3);

    Js.Global.setTimeout(
      () => {
        observer->next(4);
        observer->complete;
      },
      1000,
    )
    |> ignore;
    None;
  });

observable->subscribe(
  ~next=x => Js.log2("got value", x),
  ~error=err => Js.log2("something wrong occurred", err),
  ~complete=() => Js.log("done"),
  (),
);
/* END OF README */

never->subscribe(~next=_ => failwith("fail"), ());

let o1 = Subject.make();
o1
->Subject.asObservable
->pipe2(take(2), toArray())
->subscribe(~next=x => expectToEqual(x, [|"a", "b"|]), ());

of2("a", "b")->subscribeO(o1->Subject.asObserver);

let o1 = of3("a", "b", "c");
let o2 = of2("d", "e");
let o3 = of2("f", "g");
combineLatest([|o1, o2, o3|])
->pipe1(toArray())
->subscribe(
    ~next=x => expectToEqual(x, [|[|"c", "e", "f"|], [|"c", "e", "g"|]|]),
    (),
  );

let o1 = of3("a", "b", "c");
let o2 = of2(5, 6);
combineLatest2R(o1, o2, (a, b) => {"x": a, "y": b})
->pipe2(take(2), toArray())
->subscribe(
    ~next=
      x => expectToEqual(x, [|{"x": "c", "y": 5}, {"x": "c", "y": 6}|]),
    (),
  );

let o1 = of3("a", "b", "c");
let o2 = of2(5, 6);
combineLatest2RS(o1, o2, (a, b) => {"x": a, "y": b}, asyncScheduler)
->pipe2(take(2), toArray())
->subscribe(
    ~next=
      x => expectToEqual(x, [|{"x": "c", "y": 5}, {"x": "c", "y": 6}|]),
    (),
  );

let o1 = of1("a");
let o2 = of1(5);
let o3 = of1(true);
let o4 = of1(5.5);
combineLatest4R(o1, o2, o3, o4, (a, b, c, d) => (a, b, c, d))
->subscribe(~next=x => expectToEqual(x, ("a", 5, true, 5.5)), ());

let o1 = of1("a");
let o2 = of1(5);
let o3 = of1(true);
let o4 = of1(5.5);
combineLatest4S(o1, o2, o3, o4, asyncScheduler)
->subscribe(~next=x => expectToEqual(x, ("a", 5, true, 5.5)), ());

let o1 = of3("a", "b", "c");
let o2 = of2(1, 2);
let o3 = of2(true, false);
combineLatest3(o1, o2, o3)
->pipe1(toArray())
->subscribe(
    ~next=x => expectToEqual(x, [|("c", 2, true), ("c", 2, false)|]),
    (),
  );

open Scheduler;

let isSubscription: RxJs_Subscription.t => bool = [%raw {|
function(s) {
    return s && typeof s.closed === "boolean";
}
|}];
let expectSubscription = s => {
    expectToEqual(s->isSubscription, true);
};

let s1 = asyncScheduler->schedule(() => {
  Js.log("scheduled");
})
|> expectSubscription;




let s1 = asyncScheduler->schedule3(
  state => {
    expectToEqual(state, "some");
    Js.log("scheduled 2");
  },
  ~delay=500.0,
  "some",
);

s1->expectSubscription;
expectToEqual(s1->Subscription.closed, false);


// s1->Subscription.unsubscribe;

expectToEqual(asyncScheduler->now->Js.typeof, "number");

open Subscription;

let s1 = Subscription.empty;
expectToEqual(s1->Subscription.closed, true);
s1->Subscription.unsubscribe;

let s2 = Subscription.make0();
expectToEqual(s2->Subscription.closed, false);

let tearedDown = ref(false);
let tearedDown2 = ref(false);

let s4 = Subscription.make(() => tearedDown2 := true);

let s1 = Subscription.make(() => Js.log("sub unsub"));
let s3 = s1->add(s2);
expectToBe(s2, s3);

s1->add(s4);
s1->remove(s4);

s1->add1(() => tearedDown := true);

expectToEqual(s1->Subscription.closed, false);
s1->Subscription.unsubscribe;
expectToEqual(s1->Subscription.closed, true);
expectToEqual(tearedDown^, true);
expectToEqual(tearedDown2^, false);
expectToEqual(s2->Subscription.closed, true);

let b1 = ref(false);
queueScheduler->schedule(_ => {
    b1 := true
});
expectToEqual(b1^, true);

// queue with delay == async
let b1 = ref(false);
queueScheduler->schedule2(_ => {
    b1 := true
}, ~delay=10.0);

expectToEqual(b1^, false);

// asap is async
let b1 = ref(false);
asapScheduler->schedule2(_ => {
    b1 := true
}, ~delay=0.0);

Js.Global.setTimeout(() => expectToEqual(b1^, true), 100);

pairs2({"hello": "world", "n": 1}, asyncScheduler)
->pipe1(toArray())
->subscribe(
    ~next=
      x => {
        expectToEqualAny(x->Js.Array.unsafe_get(0), ("hello", "world"));
        expectToEqualAny(x->Js.Array.unsafe_get(1), ("n", 1));
      },
    (),
  );

of_([|"a"|])
->pipe1(timeInterval1(asyncScheduler))
->subscribe(
    ~next=
      x => {
        expectToEqual(x##value, "a");
        expectToEqual(x##interval->Js.typeof, "number");
      },
    (),
  );

timer2(0.0, ~period=20.0)
->pipe2(take(5), toArray())
->subscribe(~next=x => expectToEqual(x, [|0, 1, 2, 3, 4|]), ());

let o1 = of2("a", "b");
o1
->pipe1(
    firsti2(
      (x, i, o) => {
        expectToEqual(x->Js.typeof, "string");
        expectToEqual(i->Js.typeof, "number");
        expectToEqual(o->Js.typeof, "object");
        x == "c";
      },
      "z",
    ),
  )
->subscribe(~next=x => expectToEqual(x, "z"), ());

let o1 = of2("a", "b");
o1->pipe1(first1D("z"))->subscribe(~next=x => expectToEqual(x, "a"), ());

let o1 = of1(1);

let a = o1->pipe3(_ => "5", x => x->int_of_string, x => x + x);
expectToEqual(a, 10);

let o1 = of1(10)->Subject.asSubject;
expectToEqual(o1->Option.isSome, false);

let o1: option(Subject.t(int)) =
  ReplaySubject.make(~bufferSize=1)
  ->ReplaySubject.asObservable
  ->Subject.asSubject;
expectToEqual(o1->Option.isSome, true);

let f1 = (_, _, x, _) => x * 3;

let o1 = fromArray([|5|]);
o1
->pipe1(mapi(f1(false, false)))
->subscribe(~next=x => expectToEqual(x, 15), ());