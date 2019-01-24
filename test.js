const fs = require('fs')
const { getScreenshotSync } = require('./index')

const log = (...args) => {
  // console.log(..args)
}
const t1 = Date.now()
console.log()
for (let i = 0; i < 10; i++) {
  console.log(i)
  getScreenshotSync(0, 0, 1680, 1050, log)
  // fs.writeFileSync('./a.png', getScreenshotSync(0, 0, 1680, 1050, log))
  // fs.writeFileSync('./b.png', getScreenshotSync(0, 0, 1680, 1050, log))
}
console.log('time:', Date.now() - t1)
