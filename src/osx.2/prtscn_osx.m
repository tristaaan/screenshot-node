#include <ApplicationServices/ApplicationServices.h>
#include <CoreGraphics/CoreGraphics.h>
#include <CoreServices/CoreServices.h>
#include <ImageIO/ImageIO.h>
#include <Foundation/Foundation.h>
#include <Cocoa/Cocoa.h>
#include "prtscn_osx.h"

// CGImageRef转换为NSData
NSData * CGimageRefToNSData(CGImageRef imageRef)
{
	CFMutableDataRef dataRef = CFDataCreateMutable(NULL, 0);
	CGImageDestinationRef destinationRef = CGImageDestinationCreateWithData(dataRef, kUTTypePNG, 1, NULL);
	CGImageDestinationAddImage(destinationRef, imageRef, nil);
	CGImageDestinationFinalize(destinationRef);
	// NSData *data = (NSData *)dataRef;
	NSData *data = [NSData dataWithData:(NSData *)dataRef];
	CFRelease(destinationRef);
	CFRelease(dataRef);
	return data;
}

IData getScreen(const int x, const int y, const int width, const int height)
{	
	CGRect rect = CGRectMake(x, y, width, height);
	CGImageRef imageRef = CGDisplayCreateImageForRect(CGMainDisplayID(), rect);
	CFDataRef rawData = CGDataProviderCopyData(CGImageGetDataProvider(imageRef));

	CFIndex ll = CFDataGetLength(rawData);
	const UInt8 *rawBuffer = CFDataGetBytePtr(rawData);

	NSImage *image = [[NSImage alloc] initWithCGImage:imageRef size:rect.size];
	NSData *imgData = [image TIFFRepresentation];
	unsigned int len = [imgData length];
	NSBitmapImageRep *bitmap = [NSBitmapImageRep imageRepWithData:imgData];
	NSData* newData = [bitmap representationUsingType:NSBMPFileType properties:@{}];
	NSURL * pt1 = [NSURL fileURLWithPath:[@"./b.txt" stringByExpandingTildeInPath]];
	NSURL * pt3= [NSURL fileURLWithPath:[@"./b1.txt" stringByExpandingTildeInPath]];
	[imgData writeToURL:pt3 atomically:YES];

	[newData writeToURL:pt1 atomically:YES];
	
	NSData * data = CGimageRefToNSData(imageRef);
	unsigned int length = [data length];
	NSURL * pt2 = [NSURL fileURLWithPath:[@"./c.txt" stringByExpandingTildeInPath]];
	[data writeToURL:pt2 atomically:YES];

	char *byteData = (char *)malloc(length);
	memcpy(byteData, [data bytes], length);
	CGImageRelease(imageRef);

	IData idd = {
		length,
		byteData
	};
	return idd;
}
