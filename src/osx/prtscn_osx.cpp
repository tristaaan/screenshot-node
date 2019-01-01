#include <CoreGraphics/CoreGraphics.h>
#include "prtscn_osx.h"

CGImageRef getScreen(const int x, const int y, int width, int height)
{
	if (width == 0)
	{
		width = CGDisplayPixelsWide(CGMainDisplayID());
	}
	if (height == 0)
	{
		height = CGDisplayPixelsHigh(CGMainDisplayID());
	}
	CGRect rect = CGRectMake(x, y, width, height);
	CGImageRef image_ref = CGDisplayCreateImageForRect(CGMainDisplayID(), rect);
	CGImageRelease(image_ref);
	return image_ref;
}
