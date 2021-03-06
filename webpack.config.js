const path = require("path");
const isProd = process.env.NODE_ENV === "production";
const mode = isProd ? "production" : "development";

const buildRoot = path.join(__dirname, "build");


module.exports = {
  mode,
  target: "node",
  // target: "web",
  entry: "./test/Test.bs.js",
  output: {
    path: buildRoot,
    filename: "test.js"
  },
  plugins: [],
  devtool: "none"
};