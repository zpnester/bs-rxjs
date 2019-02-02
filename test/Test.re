open RxJs;
open Observable;
open Js.Promise;
open Operators;
open Observer;
open Expect_;

let o1 = Observable.fromArray([|1, 2, 3, 4, 5, 6|]);
o1
->pipe(toArray())
->subscribe(
    ~next=arr => expectToEqual(arr, [|1, 2, 3, 4, 5, 6|]),
    ~complete=() => Js.log("o1 complete"),
    (),
  );

let o1 = Observable.fromString("HELLO");
o1
->pipe(toArray())
->subscribe(
    ~next=arr => expectToEqual(arr, [|"H", "E", "L", "L", "O"|]),
    (),
  );

let o1 = Observable.fromPromise(resolve("from promise"));
o1->subscribe(~next=x => expectToEqual(x, "from promise"), ());

let o1 = Observable.fromArray([|1, 2, 3|]);
o1
->pipe(mapi((x, i) => (x + 10, i)))
->pipe(toArray())
->subscribe(
    ~next=arr => expectToEqual(arr, [|(11, 0), (12, 1), (13, 2)|]),
    (),
  );

let o1 = Observable.fromArray([|1, 2, 3, 4|]);
o1
->pipe3(map(i => i + 20), filter(i => i mod 2 == 0), toArray())
->subscribe(~next=arr => expectToEqual(arr, [|22, 24|]), ());

let o1 = Observable.fromArray([|resolve("one"), resolve("two")|]);
let o2 = Observable.fromArray([|resolve("three"), resolve("four")|]);
o1
->pipe3(concat(o2), concatAllPromises(), toArray())
->subscribe(
    ~next=arr => expectToEqual(arr, [|"one", "two", "three", "four"|]),
    (),
  );

let s1 = of2("one", "two");
let s2 = of2("three", "four");
let s3 = of2("a", "b");
let s4 = of1("c");

Observable.concat4(s1, s2, s3, s4)
->pipe(toArray())
->subscribe(
    ~next=
      x =>
        expectToEqual(x, [|"one", "two", "three", "four", "a", "b", "c"|]),
    (),
  );

let o1 = Observable.fromArray([|51, 52, 53|]);
let o2 = Observable.fromArray([|"green", "red"|]);
forkJoin2(o1, o2)
->subscribe(
    ~next=
      ((a, b)) => {
        expectToEqual(a, 53);
        expectToEqual(b, "red");
      },
    (),
  );

let o1 = Observable.fromArray([|1, 2, 3, 4|]);
let o2 = Observable.fromArray([|51, 52, 53|]);
merge2(o1, o2)
->pipe(toArray())
->subscribe(
    ~next=arr => expectToEqual(arr, [|1, 2, 3, 4, 51, 52, 53|]),
    (),
  );

let o1 =
  Observable.range(~start=456, ~count=3)->pipe2(pairwise(), toArray());
o1->subscribe(
  ~next=arr => expectToEqual(arr, [|(456, 457), (457, 458)|]),
  (),
);

let o1 = Observable.fromArray([|2, 4|]);
o1
->pipe(every(x => x mod 2 == 0))
->subscribe(~next=x => expectToEqual(x, true), ());

let o1 = Observable.fromArray([|2, 3, 4|]);
o1
->pipe(every(x => x mod 2 == 0))
->subscribe(~next=x => expectToEqual(x, false), ());

let o1 =
  Observable.of1("a")
  ->pipe2(concat(Observable.throwError("oops")), retry(3));
o1->subscribe(
  ~next=x => Js.log(x),
  ~error=e => expectToEqual(e, Js.Json.string("oops")),
  (),
);

o1
->pipe2(
    Operators.catchError(x =>
      of1("caught " ++ x->Js.Json.decodeString->Belt.Option.getExn)
    ),
    toArray(),
  )
->subscribe(
    ~next=arr => expectToEqual(arr, [|"a", "a", "a", "a", "caught oops"|]),
    ~error=_ => failwith("fail"),
    (),
  );

Observable.range(~start=100, ~count=30)
->pipe2(bufferCount(7), first())
->subscribe(
    ~next=arr => expectToEqual(arr, [|100, 101, 102, 103, 104, 105, 106|]),
    (),
  );

of4(5, 6, 7, 8)
->pipe2(concatMap(x => of1(x + 1)), toArray())
->subscribe(~next=arr => expectToEqual(arr, [|6, 7, 8, 9|]), ());

of3(1, 2, 3)
->pipe2(concatMapTo(of1("mappedto")), toArray())
->subscribe(
    ~next=arr => expectToEqual(arr, [|"mappedto", "mappedto", "mappedto"|]),
    (),
  );

of1("hello")
->pipe3(
    expand((x, i) => {
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
->pipe3(groupBy(x => x##age), mergeMap(g => g->pipe(toArray())), toArray())
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

range(~start=1, ~count=10)
->pipe2(
    reduce(
      (acc, v, i) => {
        expectToEqual(i->Js.typeof, "number");
        acc + v;
      },
      0,
    ),
    tap(~next=x => Js.log2("tap", x), ()),
  )
->subscribe(~next=x => expectToEqual(x, 55), ());

range(~start=1, ~count=3)
->pipe(
    reduce(
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
    flatMap((g, i) => {
      expectToEqual(i->Js.typeof, "number");
      g->pipe(
        reduce(
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
  range(~start=10, ~count=10)
  ->partition((x, i) => {
      expectToEqual(i->Js.typeof, "number");
      x mod 2 == 0;
    });
a
->pipe(toArray())
->subscribe(~next=x => expectToEqual(x, [|10, 12, 14, 16, 18|]), ());

b
->pipe(toArray())
->subscribe(~next=x => expectToEqual(x, [|11, 13, 15, 17, 19|]), ());

range(~start=1, ~count=3)
->pipe2(
    scan(
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
      delayWhen(
        (x, i) => {
          expectToEqual(i->Js.typeof, "number");
          Js.log2("delaying", x);
          timer(~delay=`Int(1000), ());
        },
        ~subscriptionDelay=timer(~delay=`Int(0), ()),
        (),
      ),
      finalize(() => Js.log("finally")),
    );
o1->subscribe(~next=x => expectToEqual(x, "delayed"), ());

o1->toPromise |> then_(x => resolve(expectToEqual(x, "delayed")));

of2(2, 3)
->pipe2(repeat(2), toArray())
->subscribe(~next=x => expectToEqual(x, [|2, 3, 2, 3|]), ());

let o1 = ReplaySubject.make(~bufferSize=5, ~windowTime=1000, ());
let o2 = o1->ReplaySubject.asObservable;

let o1 = o1->ReplaySubject.asObserver;
o1->next("a");
o1->next("b");

o1->next("c");
o1->complete;

Js.Global.setTimeout(
  () =>
    o2
    ->pipe(toArray())
    ->subscribe(~next=x => expectToEqual(x, [|"a", "b", "c"|]), ())
    |> ignore,
  500,
);

Observable.empty->subscribe(
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

let o1 = timer(~delay=`Int(500), ());
o1->subscribe(~next=x => expectToEqual(x, 0), ());

let o1 =
  of1("A")->pipe(delayWhen((_, _) => timer(~delay=`Int(300), ()), ()));
let o2 =
  of1("B")->pipe(delayWhen((_, _) => timer(~delay=`Int(100), ()), ()));
let o3 = race2(o1, o2);
o3->subscribe(~next=x => expectToEqual(x, "B"), ());

let o1 = of3(3, 4, 5);
let o2 = o1->pipe2(startWith(2), toArray());
o2->subscribe(~next=arr => expectToEqual(arr, [|2, 3, 4, 5|]), ());

let o1 = interval(50)->pipe(take(4));
let o2 = of1(300);
o1
->pipe2(withLatestFrom(o2), toArray())
->subscribe(
    ~next=
      arr =>
        expectToEqual(arr, [|(0, 300), (1, 300), (2, 300), (3, 300)|]),
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
->pipe(toArray())
->subscribe(~next=arr => expectToEqual(arr, [|("a", 2), ("b", 3)|]), ());

let o1 = empty;
o1
->pipe(defaultIfEmpty("qqq"))
->subscribe(~next=x => expectToEqual(x, "qqq"), ());

let o1 = of1("A");
let o2 = of1("B");
iif(() => false, o1, o2)->subscribe(~next=x => expectToEqual(x, "B"), ());

let o1 = fromArray([|4, 5, 6|]);
fromArray([|4, 5, 6|])
->pipe(sequenceEqual(o1))
->subscribe(~next=x => expectToEqual(x, true), ());

Observable.create(obs => {
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
  () => ();
})
->pipe(toArray())
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
let o1 = timer(~delay=`Date(d1), ~period=100, ());
o1
->pipe2(take(3), toArray())
->subscribe(~next=arr => expectToEqual(arr, [|0, 1, 2|]), ());

/* bad test */
let i1 = ref(0);
let o2 =
  Observable.create(obs => {
    if (i1^ == 0) {
      i1 := 1;
      failwith("f");
    } else {
      obs->Observer.next("d");
    };
    () => ();
  });
let o1 = of3("a", "b", "c");
let o3 = of1("e");
concat3(o1, o2, o3)
->pipe2(
    retryWhen(errs => {
      errs->subscribe(~next=x => expectToEqualAny(x, Failure("f")), ())
      |> ignore;

      timer(~delay=`Int(500), ());
    }),
    toArray(),
  )
->subscribe(
    ~next=arr => expectToEqual(arr, [|"a", "b", "c", "a", "b", "c", "d"|]),
    (),
  );

let o1 =
  Observable.create(obs => {
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
    () => ();
  })
  ->pipe2(publish(), refCount());

/* DO NOT DELETE, connect required without refCount */

/* Js.Global.setTimeout(
     () =>
       o1
       ->ConnectableObservable.asConnectableObservable
       ->Belt.Option.getExn
       ->ConnectableObservable.connect,
     500,
   )
   |> ignore; */

o1
->pipe(toArray())
->subscribe(~next=arr => expectToEqual(arr, [|"a", "b", "c", "d"|]), ());

let o1 =
  Observable.create(obs => {
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
    () => ();
  })
  ->pipe(publishBehavior("q"));

Js.Global.setTimeout(
  () => {
    let s =
      o1
      ->ConnectableObservable.asConnectableObservable
      ->Belt.Option.getExn
      ->ConnectableObservable.connect;

    s->Subscription.unsubscribe;
    expectToEqual(s->Js.typeof, "object");
  },
  500,
)
|> ignore;

o1
->pipe(toArray())
->subscribe(
    ~next=arr => expectToEqual(arr, [|"q", "a", "b", "c", "d"|]),
    (),
  );

let o1 =
  Observable.create(obs => {
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
    () => ();
  })
  ->pipe(publishLast());

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
->pipe(toArray())
->subscribe(~next=arr => expectToEqual(arr, [|"d"|]), ());

/* test does not verify that params are working (bufferSize and windowTime) */
let o1 =
  Observable.create(obs => {
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
    () => ();
  })
  ->pipe(publishReplay(~bufferSize=1, ()));

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
->pipe(toArray())
->subscribe(~next=arr => expectToEqual(arr, [|"a", "b", "c", "d"|]), ());

let s1 = Subject.make();

let o1 =
  Observable.create(obs => {
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
    () => ();
  })
  ->pipe(multicast(`Subject(s1)));

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
->pipe(toArray())
->subscribe(~next=arr => expectToEqual(arr, [|"c", "d"|]), ());

let o1 =
  Observable.create(obs => {
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
    () => ();
  })
  ->pipe(share());

o1
->pipe(toArray())
->subscribe(~next=arr => expectToEqual(arr, [|"a", "b", "c", "d"|]), ());

Observable.create(obs => {
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
  () => ();
})
->pipe2(shareReplay(~bufferSize=3, ()), toArray())
->subscribe(~next=arr => expectToEqual(arr, [|"a", "b", "c", "d"|]), ());

/* bad test because of concurrency issues, simplified to checking length */
interval(50)
->pipe3(audit(_ => timer(~delay=`Int(100), ())), take(10), toArray())
->subscribe(~next=arr => expectToEqual(arr->Js.Array.length > 5, true), ());

/* bad test because of concurrency issues, simplified to checking length */
interval(50)
->pipe3(auditTime(100), take(10), toArray())
->subscribe(~next=arr => expectToEqual(arr->Js.Array.length > 5, true), ());

Observable.create(obs => {
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
  () => ();
})
->pipe3(debounce(() => timer(~delay=`Int(100), ())), take(1), toArray())
->subscribe(~next=arr => expectToEqual(arr, [|3|]), ());

Observable.create(obs => {
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
  () => ();
})
->pipe3(debounceTime(100), take(1), toArray())
->subscribe(~next=arr => expectToEqual(arr, [|3|]), ());

fromArray([|1, 1, 2, 2, 3, 1, 2, 3|])
->pipe2(distinctUntilChanged(), toArray())
->subscribe(~next=arr => expectToEqual(arr, [|1, 2, 3, 1, 2, 3|]), ());

of1("a")
->pipe(ignoreElements())
->subscribe(
    ~next=_ => failwith("fail"),
    ~error=_ => failwith("fail"),
    ~complete=() => Js.log("ignoreElements OK"),
    (),
  );

of3("a", "b", "c")
->pipe(last())
->subscribe(~next=x => expectToEqual(x, "c"), ());

/* bad test */
interval(500)
->pipe3(sample(interval(1000)), take(2), toArray())
->subscribe(~next=arr => expectToEqual(arr->Js.Array.length > 0, true), ());

/* bad test */
interval(500)
->pipe3(sampleTime(1000), take(2), toArray())
->subscribe(~next=arr => expectToEqual(arr->Js.Array.length > 0, true), ());

range(~start=1, ~count=20)
->pipe3(single(x => x == 17), map(x => x + 1), toArray())
->subscribe(~next=arr => expectToEqual(arr, [|18|]), ());

range(~start=1, ~count=20)
->pipe2(skip(17), toArray())
->subscribe(~next=arr => expectToEqual(arr, [|18, 19, 20|]), ());

/* bad test */
let o1 = timer(~delay=`Int(1000), ());
interval(500)
->pipe3(skipUntil(o1), take(2), toArray())
->subscribe(~next=arr => expectToEqual(arr->Js.Array.length > 0, true), ());

let o1 = timer(~delay=`Int(1000), ());
interval(600)
->pipe3(takeUntil(o1), take(2), toArray())
->subscribe(~next=arr => expectToEqual(arr, [|0|]), ());

range(~start=1, ~count=20)
->pipe3(skipWhile(x => x < 5), take(2), toArray())
->subscribe(~next=arr => expectToEqual(arr, [|5, 6|]), ());

/* bad test */
range(~start=1, ~count=20)
->pipe3(takeWhile(x => x < 5), take(2), toArray())
->subscribe(~next=arr => expectToEqual(arr->Js.Array.length > 0, true), ());

/* bad test */
timer(~delay=`Int(0), ~period=200, ())
->pipe3(throttle(_ => timer(~delay=`Int(210), ())), take(2), toArray())
->subscribe(~next=arr => expectToEqual(arr->Js.Array.length > 0, true), ());

/* bad test */
timer(~delay=`Int(0), ~period=200, ())
->pipe3(throttlePromise(_ => resolve(210)), take(2), toArray())
->subscribe(~next=arr => expectToEqual(arr, [|0, 1|]), ());

/* bad test */
timer(~delay=`Int(0), ~period=200, ())
->pipe3(throttleTime(210), take(2), toArray())
->subscribe(~next=arr => expectToEqual(arr->Js.Array.length > 0, true), ());

let o1 = timer(~delay=`Int(1000), ());
interval(220)
->pipe(buffer(o1))
->subscribe(~next=arr => expectToEqual(arr, [|0, 1, 2, 3|]), ());

interval(220)
->pipe2(bufferTime(1000, ~bufferCreationInterval=500, ()), take(10))
->subscribe(~next=arr => expectToEqual(arr->Js.Array.length >= 4, true), ());

let o1 =
  Observable.create(obs => {
    let t = interval(100)->subscribe(~next=i => obs->Observer.next(i), ());

    Js.Global.setTimeout(
      () => {
        obs->Observer.complete;
        t->Subscription.unsubscribe;
      },
      1000,
    )
    |> ignore;
    () => ();
  });

o1
->pipe2(
    bufferToggle(
      timer(~delay=`Int(0), ~period=50, ()),
      i => {
        expectToEqual(i->Js.typeof, "number");
        timer(~delay=`Int(500), ());
      },
    ),
    first(),
  )
->subscribe(~next=arr => expectToEqual(arr->Js.Array.length > 0, true), ());

let o1 =
  Observable.create(obs => {
    let t = interval(500)->subscribe(~next=i => obs->Observer.next(i), ());

    Js.Global.setTimeout(
      () => {
        obs->Observer.complete;
        t->Subscription.unsubscribe;
      },
      1000,
    )
    |> ignore;
    () => ();
  });

interval(50)
->pipe3(bufferWhen(() => o1), take(3), toArray())
->subscribe(~next=arr => expectToEqual(arr->Js.Array.length > 0, true), ());

let o1 = of3(1, 2, 3);
let o2 = of2(4, 5);
let o3 = of2(o1, o2);
o3
->pipe2(exhaust(), toArray())
->subscribe(~next=arr => expectToEqual(arr, [|1, 2, 3, 4, 5|]), ());

let o1 = interval(10)->pipe2(map(string_of_int), take(10));
let o2 = interval(10)->pipe2(mapi((i, _) => {"i": i}), take(2));

o1
->pipe(
    exhaustMap(
      (f, i) => {
        Js.log3("f i", f, i);
        expectToEqual(f->Js.typeof, "string");
        expectToEqual(i->Js.typeof, "number");
        o2;
      },
      ~resultSelector=
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
      (),
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
->pipe(pluck4("result", "user", "address", "street"))
->subscribe(~next=x => expectToEqualAny(x, "Roscoe"), ());

o1
->pipe(pluck4("result", "user", "address", "nam"))
->subscribe(~next=x => expectToEqual(x, undef), ());

of2("a", "b")
->pipe2(switchMap((x, i) => of2(x, i->string_of_int)), toArray())
->subscribe(~next=arr => expectToEqual(arr, [|"a", "0", "b", "1"|]), ());

let o1 = interval(50);
let o2 = interval(200);
o1
->pipe4(window(o2), flatMap((x, _) => x), take(10), toArray())
->subscribe(
    ~next=
      arr => {
        expectToEqual(arr->Js.Array.length, 10);
        expectToEqual(arr->Belt.Array.getUnsafe(0), 0);
      },
    (),
  );

let o1 = interval(50);
o1
->pipe2(windowCount(5, ~startWindowEvery=2, ()), take(10))
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

let o1 = interval(50);
o1
->pipe4(windowTime(200), flatMap((x, _) => x), take(10), toArray())
->subscribe(
    ~next=
      arr => {
        expectToEqual(arr->Js.Array.length, 10);
        expectToEqual(arr->Belt.Array.getUnsafe(0), 0);
      },
    (),
  );

let o1 =
  Observable.create(obs => {
    let t = interval(100)->subscribe(~next=i => obs->Observer.next(i), ());

    Js.Global.setTimeout(
      () => {
        obs->Observer.complete;
        t->Subscription.unsubscribe;
      },
      1000,
    )
    |> ignore;
    () => ();
  });

o1
->pipe(
    windowToggle(
      timer(~delay=`Int(50), ()),
      i => {
        expectToEqual(i->Js.typeof, "number");
        timer(~delay=`Int(50), ());
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

interval(20)
->pipe2(windowWhen(() => interval(100)), take(10))
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
->pipe(delay(`Float(10.0)))
->subscribe(~next=x => expectToEqual(x, "del"), ());

/* DO NOT DELETE */
/* throwError(1)
   ->pipe(finalize(() => Js.log("finalize on err")))
   ->subscribe(~next=_ => (), ()); */

of1("a")
->pipe(timeout(`Int(5)))
->subscribe(~next=x => expectToEqual(x, "a"), ());

of2("a", "b")
->pipe(elementAt(1, ()))
->subscribe(~next=x => expectToEqual(x, "b"), ());

of2("a", "b")
->pipe(elementAt(2, ~defaultValue="y", ()))
->subscribe(~next=x => expectToEqual(x, "y"), ());

of2("b", "c")
->pipe3(endWith4("d", "e", "f", "g"), startWith2("_", "a"), toArray())
->subscribe(
    ~next=x => expectToEqual(x, [|"_", "a", "b", "c", "d", "e", "f", "g"|]),
    (),
  );

of3("a", "b", "c")
->pipe(
    find((x, i, o) => {
      expectToEqual(i->Js.typeof, "number");
      expectToEqual(o->Js.typeof, "object");
      x == "b";
    }),
  )
->subscribe(~next=x => expectToEqual(x, Some("b")), ());

of3("a", "b", "c")
->pipe(
    find((_, i, o) => {
      expectToEqual(i->Js.typeof, "number");
      expectToEqual(o->Js.typeof, "object");
      false;
    }),
  )
->subscribe(~next=x => expectToEqual(x, None), ());

of3("a", "b", "c")
->pipe(
    findIndex((x, i, o) => {
      expectToEqual(i->Js.typeof, "number");
      expectToEqual(o->Js.typeof, "object");
      x == "b";
    }),
  )
->subscribe(~next=x => expectToEqual(x, 1), ());

of3("a", "b", "c")
->pipe(
    findIndex((_, i, o) => {
      expectToEqual(i->Js.typeof, "number");
      expectToEqual(o->Js.typeof, "object");
      false;
    }),
  )
->subscribe(~next=x => expectToEqual(x, -1), ());

of1("a")
->pipe(isEmpty())
->subscribe(~next=x => expectToEqual(x, false), ());

empty->pipe(isEmpty())->subscribe(~next=x => expectToEqual(x, true), ());

of3(1, 2, 3)
->pipe(max((a, b) => a - b |> float_of_int))
->subscribe(~next=x => expectToEqual(x, 3), ());

of3(1, 4, 3)
->pipe(max((a, b) => a - b |> float_of_int))
->subscribe(~next=x => expectToEqual(x, 4), ());

of3(1, 4, 3)
->pipe(min((a, b) => a - b |> float_of_int))
->subscribe(~next=x => expectToEqual(x, 1), ());

let o1 = of2("a", "b");
let o2 = of3("c", "d", "e");
of2(o1, o2)
->pipe2(switchAll(), toArray())
->subscribe(~next=x => expectToEqual(x, [|"a", "b", "c", "d", "e"|]), ());

let o1 = of2("a", "b");
let o2: observable(string) = throwError("err");
let o3 = of3("c", "d", "e");
o1
->pipe(onErrorResumeNext([|o2, o3|]))
->pipe(toArray())
->subscribe(~next=x => expectToEqual(x, [|"a", "b", "c", "d", "e"|]), ());

let op1 =
  Operator.make(src =>
    Observable.create(obs => {
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

      () => s->Subscription.unsubscribe;
    })
  );

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
  Observable.create(obs => {
    obs->Observer.next("a");
    () => Js.log("teardown OK");
  });
let s = o1->subscribe();
s->Subscription.unsubscribe;

expectToEqual(
  empty->ConnectableObservable.asConnectableObservable->Belt.Option.isSome,
  false,
);

of2("a", "b")
->pipe2(refCount(), toArray())
->subscribe(~next=x => expectToEqual(x, [|"a", "b"|]), ());

empty
->pipe2(
    throwIfEmpty(~errorFactory=() => failwith("custom err"), ()),
    catchError(err => {
      expectToEqualAny(err, Failure("custom err"));
      of1("x");
    }),
  )
->subscribe(~next=x => expectToEqual(x, "x"), ());

/* empty does not work */
create((_, ()) => ())
->pipe(timeoutWith(`Int(100), of1("a")))
->subscribe(
    ~next=x => expectToEqual(x, "a"),
    ~error=_ => failwith("fail"),
    (),
  );

of1("a")
->pipe(timestamp())
->subscribe(
    ~next=
      x => {
        Js.log(x);
        expectToEqual(x##value, "a");
        expectToEqual(x##timestamp->Js.typeof, "number");
      },
    (),
  );

of6("a", "a", "b", "b", "b", "c")
->pipe2(
    distinctUntilChanged(
      ~compare=
        (a, b) =>
          if (a == "a") {
            false;
          } else {
            a == b;
          },
      (),
    ),
    toArray(),
  )
->subscribe(~next=x => expectToEqual(x, [|"a", "a", "b", "c"|]), ());

/* README */
let observable =
  Observable.create(observer => {
    open Observer;

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

    () => /* teardown logic */ ();
  });

observable->Observable.subscribe(
  ~next=x => Js.log2("got value", x),
  ~error=err => Js.log2("something wrong occurred", err),
  ~complete=() => Js.log("done"),
  (),
);
/* END OF README */