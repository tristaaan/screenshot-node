const addon = require('./build/Debug/screenshot')

console.log(
  'This should be eight:',
  addon(1, 2, 3, 4, (...args) => {
    console.log('asdasdas', ...args)
    return 30
  })
)
