#include <Foundation/Foundation.h>
#include <CoreServices/CoreServices.h>
#include "prtscn_osx.h"

// CGImageRef转换为NSData
NSData * CGimageRefToNSData(CGImageRef imageRef)
{
	CFMutableDataRef dataRef = CFDataCreateMutable(NULL, 0);
	CGImageDestinationRef destinationRef = CGImageDestinationCreateWithData(dataRef, kUTTypePNG, 1, NULL);
	CGImageDestinationAddImage(destinationRef, imageRef, nil);
	if(!CGImageDestinationFinalize(destinationRef)) {
		NSLog(@"Failed to write Image");
	}
	NSData *data = (NSData *)dataRef;
	CFRelease(dataRef);
	return data;
}

CFDataRef getScreen(const int x, const int y, const int width, const int height)
{	
	CGRect rect = CGRectMake(x, y, width, height);
	CGImageRef imageRef = CGDisplayCreateImageForRect(CGMainDisplayID(), rect);
	CFDataRef rawData = CGDataProviderCopyData(CGImageGetDataProvider(imageRef));
	// NSData * data = CGimageRefToNSData(imageRef);
	// unsigned int length = [data length];
	// NSString *base64Encoded = [data base64EncodedStringWithOptions:0];
	// const char *base64 = [base64Encoded UTF8String];
	// CGImageRelease(imageRef);

	return rawData;
}
