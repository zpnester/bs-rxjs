
var rxjs = require("rxjs")
var operators = require("rxjs/operators");
var Observable = rxjs.Observable;
var groupBy = operators.groupBy;
var concat = operators.concat;
var flatMap = operators.flatMap;
var flatMap = operators.flatMap;
var partition = operators.partition;
var map = operators.map;
var of = rxjs.of;
var interval = rxjs.interval;
var take = operators.take;
var Subject = rxjs.Subject;
var ReplaySubject = rxjs.ReplaySubject;

var combineAll = operators.combineAll;
var withLatestFrom = operators.withLatestFrom;
var pairwise = operators.pairwise;


// var o1 = of(1, 2, 3)
// o1 = o1.lift(map(x => x + 300))

// console.log(o1);

// o1.subscribe({
//     next: x => {
//         console.log("x", x);
//     }
// })


var op1 = src => {
    var s = new ReplaySubject();
    
    src.subscribe({
        next: x => {
            console.log("xxx", x);
            s.next(x + "!");
        }
    });
    
    return s;
};

of("a").pipe(op1).subscribe({
    next: x => console.log("yyy", x)
})

console.log("DONE")

