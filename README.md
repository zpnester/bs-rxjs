
# bs-rxjs

RxJS v6 bindings for BuckleScript

## Example

```reason
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
  });

observable->Observable.subscribe(
  ~next=x => Js.log2("got value", x),
  ~error=err => Js.log2("something wrong occurred", err),
  ~complete=() => Js.log("done"),
  (),
);
```

## Install

```
npm install --save @zpnester/bs-rxjs
```
