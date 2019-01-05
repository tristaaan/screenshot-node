const addon = require('./build/Debug/screenshot')
const fs = require('fs')

console.log(
  'This should be eight:',
  addon(0, 0, 1000, 800, (a, b) => {
    console.log(a, a.toString())
    if (fs.existsSync('./a.txt')) fs.unlinkSync('./a.txt')
    console.log('length:', a.length)
    fs.writeFileSync('./a.txt', a)
    console.dir(b)
    return 30
  })
)
