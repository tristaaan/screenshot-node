const fs = require('fs')
const { getScreenshotSync } = require('./index')

const a = getScreenshotSync(0, 0, 1680, 1050)
console.log(a)
fs.writeFileSync('./a.png', a)