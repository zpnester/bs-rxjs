function expectToEqual(a, b) {
    let expect = require("expect");
    expect(a).toEqual(b);
}

function expectToBe(a, b) {
    let expect = require("expect");
    expect(a).toBe(b);
}

module.exports.expectToEqual = expectToEqual;
module.exports.expectToBe = expectToBe;