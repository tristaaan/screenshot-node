const addon = require('./build/Debug/screenshot')

console.log(
  'This should be eight:',
  addon(3, 5, 4, 5, (...args) => {
    console.log('asdasdas', ...args)
	return 30
  })
)
