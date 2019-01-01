#include <ApplicationServices/ApplicationServices.h>
#include <CoreGraphics/CoreGraphics.h>
#include <CoreServices/CoreServices.h>
#include <ImageIO/ImageIO.h>
#include <Foundation/Foundation.h>
#include "prtscn_osx.h"

CGImageRef getScreen(const int x, const int y, int width, int height) {
	if (width == 0) {
		width = (int) CGDisplayPixelsWide(CGMainDisplayID());
	}
	if (height == 0) {
		height = (int) CGDisplayPixelsHigh(CGMainDisplayID());
	}
	CGRect rect = CGRectMake(x, y, width, height);
	CGImageRef image_ref = CGDisplayCreateImageForRect(CGMainDisplayID(), rect);
	CGImageRelease(image_ref);
	return image_ref;
}
