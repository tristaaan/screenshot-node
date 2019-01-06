const fs = require('fs')
const { getScreenshotSync } = require('./index')


const t1 = Date.now()
console.log()
for (let i = 0; i < 1; i++) {
  console.log(i)
  fs.writeFileSync('./a.png', Buffer.from(getScreenshotSync(0, 0, 1680, 1050), 'base64'))
  fs.writeFileSync('./b.png', Buffer.from(getScreenshotSync(1680, 0, 1920, 1080), 'base64'))
}
console.log('time:', Date.now() - t1)
