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

// CGImageRef转换为NSData
NSData * CGimageRefToNSData(CGImageRef imageRef)
{
	CFMutableDataRef dataRef = CFDataCreateMutable(NULL, 0);
	CGImageDestinationRef destinationRef = CGImageDestinationCreateWithData(dataRef, kUTTypePNG, 1, NULL);
	CGImageDestinationAddImage(destinationRef, imageRef, nil);
	CGImageDestinationFinalize(destinationRef);
	NSData *data = [NSData dataWithData:(NSData *)dataRef];
	CFRelease(destinationRef);
	CFRelease(dataRef);
	return data;
}

IData getScreen(const int x, const int y, const int width, const int height)
{
	CGRect rect = CGRectMake(x, y, width, height);
	CGImageRef imageRef = CGDisplayCreateImageForRect(CGMainDisplayID(), rect);

	NSBitmapImageRep * ns_image = [[NSBitmapImageRep alloc] initWithCGImage: imageRef];
	struct ns_object_releaser ns_image_releaser(ns_image);
	NSColorSpace *ns_cs_sRGB = [NSColorSpace sRGBColorSpace];

	const size_t src_width = CGImageGetWidth(imageRef);
	const size_t src_height = CGImageGetHeight(imageRef);
	const CGColorSpaceRef src_colorspace = CGImageGetColorSpace(imageRef);

	unsigned int length = src_height * src_width * 4;
	if (!allocated) {
		data = (UInt8 *) malloc(length * sizeof(UInt8));
		allocated = true;
	}

	@autoreleasepool
	{
	NSBitmapImageRep * ns_image_sRGB = [ns_image \
		bitmapImageRepByConvertingToColorSpace: ns_cs_sRGB
		renderingIntent: NSColorRenderingIntentDefault];

	size_t i = 0;
	for( size_t y = 0; y < src_height; ++y )
	{
		for( size_t x = 0; x < src_width; ++x, i += 4)
		{
			NSColor * color = [ns_image_sRGB colorAtX: x y: y];

			CGFloat color_values[4] = {};
			color_values[0] = [color redComponent  ];
			color_values[1] = [color greenComponent];
			color_values[2] = [color blueComponent ];
			color_values[3] = [color alphaComponent];

			CGColorRef cg_color = CGColorCreate(src_colorspace, color_values);
			struct cf_object_releaser cg_color_releaser(cg_color);

			NSColor *fixed_color = [[NSColor colorWithCGColor: cg_color]
																colorUsingColorSpace: ns_cs_sRGB];

			data[i + 0] = (UInt8) ([fixed_color redComponent  ] * 255);
			data[i + 1] = (UInt8) ([fixed_color greenComponent] * 255);
			data[i + 2] = (UInt8) ([fixed_color blueComponent ] * 255);
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
