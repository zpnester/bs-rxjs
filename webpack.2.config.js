const path = require("path");
const isProd = process.env.NODE_ENV === "production";
const mode = isProd ? "production" : "development";

const buildRoot = path.join(__dirname, "build");


module.exports = {
  mode,
  target: "node",
  // target: "web",
  entry: "./test/BundleTest.bs.js",
  output: {
    path: buildRoot,
    filename: "bundle.js"
  },
  plugins: [],
  devtool: "none"
};