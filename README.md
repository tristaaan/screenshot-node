# screenshot-node fork
Changes on this fork:
- The captured region is stored in memory and returned in a `Uint8Array` via the method `getScreenshotSync(x, y, width, height, colorSpace)`.
- `colorSpace` paramter returns color in sRGB or Adobe RGB on Windows and Mac.

Caveats of this fork:
- Completely untested on Linux
- Minimally tested on Windows 10, it was developed with the intention of only capturing a small region of the screen (under 30x30 pixels )and the Windows methods used here may be inefficient on larger areas.

Original README included below

---
# screenshot-node [![npm](https://img.shields.io/npm/dt/screenshot-node.svg?style=flat-square)](https://www.npmjs.com/package/screenshot-node)
Takes a screenshot of selected area and saves it to disk.

# Linux, OS X and Windows all supported now.

## Instalation
```sh
$ npm install screenshot-node
```
# Methods
call the module
```javascript
var screenshot = require('screenshot-node');
```
### screenshot.saveScreenshot(x, y, width, height, path, callback)

#### x, y
##### Must be whole numbers.
The x and y coordinates for the top left corner of the picture.

#### width, height
##### Must be whole numbers.
The width and height of the screenshot in pixels.
##### Set width and height as 0 to take a fullscreen screenshot

#### path
##### Must be a string
The path including name of the file you want the screenshot to be saved as.

#### callback(err)
A string with error message. Null if there are no error.

#### example
Takes a screenshot from top left corner that have a width and height of 100. Saves it in the current directory with the name "image.png".
```javascript
screenshot.saveScreenshot(0, 0, 100, 100, "image.png", (err) => {
    if(err) console.log(err);
}
```
