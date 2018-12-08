/*

  https://webpack.js.org/guides/environment-variables/
  https://webpack.js.org/api/cli/#environment-options
  https://webpack.js.org/configuration/configuration-types/#exporting-a-function

  */
const path = require("path")
const HtmlWebpackPlugin = require("html-webpack-plugin")
const MiniCssExtractPlugin = require("mini-css-extract-plugin")
const outputDir = path.join(__dirname, "dist/")

module.exports = function(env, argv) {
  return {
    entry: {
      Index: './src/Index.bs.js',
    },
    mode: env.production ? 'production' : 'development' /* --env.production */,
    output: {
      path: outputDir,
      publicPath: outputDir,
      filename: '[name].js'
    },
    module: {
      rules: [
        {
          test: /\.css$/,
          use: [
            env.production ? MiniCssExtractPlugin.loader : 'style-loader',
            'css-loader'
          ],
        },
      ]
    },
    plugins: [
      new HtmlWebpackPlugin({
        template: "src/index.html",
        favicon: "src/favicon.ico",
        inject: false
      }),
      new MiniCssExtractPlugin({
        filename: 'styles.css',
        chunkFilename: "[id].css"
      })
    ],
    devServer: {
      compress: true,
      publicPath: '/',
      contentBase: outputDir,
      watchContentBase: true,
      port: env.PORT || 8000,
      historyApiFallback: true
    }
  }
}
