function expectToEqual(a, b) {
    let expect = require("expect");
    expect(a).toEqual(b);
}

module.exports.expectToEqual = expectToEqual;