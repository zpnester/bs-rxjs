const path = require("path");
const isProd = process.env.NODE_ENV === "production";
const mode = isProd ? "production" : "development";

const buildRoot = path.join(__dirname, "build");


module.exports = {
                   mode,
                   target: "node",
                   // target: "web",
                   entry: "./test/WebpackTest.bs.js",
                   output: {
                     path: buildRoot,
                     filename: "main.js"
                   },
                   plugins: [],
                   devtool: "none"
                 };