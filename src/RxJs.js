var partition = require("rxjs/operators").partition;

function pipePartition(self, pred) {
    return self.pipe(partition(pred));
}

module.exports.pipePartition = pipePartition;