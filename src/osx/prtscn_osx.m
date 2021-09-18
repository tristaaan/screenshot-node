#include <ApplicationServices/ApplicationServices.h>
#include <CoreGraphics/CoreGraphics.h>
#include <CoreServices/CoreServices.h>
#include <ImageIO/ImageIO.h>
#include <Foundation/Foundation.h>
#include <Cocoa/Cocoa.h>
#include "prtscn_osx.h"

struct ns_object_releaser
{
	NSObject* who;
public:
	ns_object_releaser(NSObject* w): who(w) {}
public:
	~ns_object_releaser() { [who dealloc] ; }
};

struct cf_object_releaser
{
	CFTypeRef who;
public:
	cf_object_releaser(CFTypeRef w): who(w) {}
public:
	~cf_object_releaser() { ::CFRelease(who); }
};

bool allocated = false;
UInt8 *data = NULL;

IData getScreen(const int x, const int y, const int width, const int height, const std::string colorSpace)
{
	CGRect rect = CGRectMake(x, y, width, height);

	CFArrayRef window_list = CGWindowListCreate(
		kCGWindowListOptionOnScreenOnly,
    kCGNullWindowID
	);
	struct cf_object_releaser window_list_releaser(window_list);

	// CGImageRef imageRef = CGDisplayCreateImageForRect(CGMainDisplayID(), rect);
	CGImageRef imageRef = CGWindowListCreateImageFromArray(
		rect,
    window_list,
		kCGWindowImageNominalResolution
	);

	NSBitmapImageRep * ns_image = [[NSBitmapImageRep alloc] initWithCGImage: imageRef];
	struct ns_object_releaser ns_image_releaser(ns_image);
	// https://developer.apple.com/documentation/appkit/nscolorspace?language=objc
	NSColorSpace *targetColorSpace;
	if (colorSpace == "srgb") {
		targetColorSpace = [NSColorSpace sRGBColorSpace];
	} else { // else if (colorSpace == 'adobergb')
		targetColorSpace = [NSColorSpace adobeRGB1998ColorSpace];
	}

	const size_t src_width = CGImageGetWidth(imageRef);
	const size_t src_height = CGImageGetHeight(imageRef);
	const CGColorSpaceRef sourceColorSpace = CGImageGetColorSpace(imageRef);

	unsigned int length = src_height * src_width * 4;
	if (!allocated) {
		data = (UInt8 *) malloc(length * sizeof(UInt8));
		allocated = true;
	}

	@autoreleasepool
	{
	size_t i = 0;
	for( size_t y = 0; y < src_height; ++y )
	{
		for( size_t x = 0; x < src_width; ++x, i += 4)
		{
			NSColor * color = [ns_image colorAtX: x y: y];

			CGFloat color_values[4] = {};
			color_values[0] = [color redComponent  ];
			color_values[1] = [color greenComponent];
			color_values[2] = [color blueComponent ];
			color_values[3] = [color alphaComponent];

			CGColorRef cg_color = CGColorCreate(sourceColorSpace, color_values);
			struct cf_object_releaser cg_color_releaser(cg_color);

			NSColor *fixed_color = [[NSColor colorWithCGColor: cg_color]
																colorUsingColorSpace: targetColorSpace];

			data[i + 0] = (UInt8) lroundf([fixed_color redComponent  ] * 255);
			data[i + 1] = (UInt8) lroundf([fixed_color greenComponent] * 255);
			data[i + 2] = (UInt8) lroundf([fixed_color blueComponent ] * 255);
			data[i + 3] = 255;
		}
	}
	}; // autoreleasepool

	CGImageRelease(imageRef);

	IData idd = {
		length,
		data
	};
	return idd;
}
