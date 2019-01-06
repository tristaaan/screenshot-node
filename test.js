const fs = require('fs')
const screenshot = require('./index')

screenshot(1260, 0, 1200, 800, base64 => {
  console.log(Buffer.from(base64, 'base64'))
  if (fs.existsSync('./a.png')) fs.unlinkSync('./a.png')
  console.log('length:', base64.length)
  fs.writeFileSync('./a.png', Buffer.from(base64, 'base64'))
  return 30
})
