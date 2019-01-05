#include <CoreGraphics/CoreGraphics.h>
#include <ApplicationServices/ApplicationServices.h>
#include <CoreServices/CoreServices.h>
#include <ImageIO/ImageIO.h>
#include <Foundation/Foundation.h>
#include "prtscn_osx.h"
#include <napi.h>

NSData * CGimageRefToNSData(CGImageRef imageRef)
{
	static NSURL* path = [NSURL fileURLWithPath:[@"./c.png" stringByExpandingTildeInPath]];

	CFMutableDataRef dataRef = CFDataCreateMutable(NULL, 0);
	CGImageDestinationRef destinationRef = CGImageDestinationCreateWithData(dataRef, kUTTypePNG, 1, NULL);
	CGImageDestinationAddImage(destinationRef, imageRef, nil);
	if(!CGImageDestinationFinalize(destinationRef)) {
		NSLog(@"Failed to write Image");
	}
	NSData *data = (NSData *)dataRef;
	// 写入文件到文件夹
	[data writeToURL:path atomically:YES];
	return data;
}

Napi::Value getScreen(const int x, const int y, const int width, const int height, Napi::Env env )
{	
	CGRect rect = CGRectMake(x, y, width, height);
	CGImageRef imageRef = CGDisplayCreateImageForRect(CGMainDisplayID(), rect);
	NSData * data = CGimageRefToNSData(imageRef);
	unsigned int length = [data length];
	Napi::Value buf = Napi::Buffer<NSData *>::New(env, &data, length);
	return buf;
}
