const fs = require('fs')
const screenshot = require('./index')

const t1 = Date.now();
console.log()
for (let i = 0; i < 10; i++) {
  console.log(i)
  screenshot(1260, 0, 1200, 800, base64 => {})
}
console.log('time:', Date.now() - t1)
