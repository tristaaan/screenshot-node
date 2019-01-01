const screenshot = require('./index');

const a = screenshot(0, 0, 0, 0, (err) => {
	if (err) console.log(err);
})
console.log(a)
