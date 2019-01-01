#ifndef PRTSCN_OSX_H_
#define PRTSCN_OSX_H_
#include <ApplicationServices/ApplicationServices.h>
#include <CoreGraphics/CoreGraphics.h>
#include <CoreServices/CoreServices.h>
#include <ImageIO/ImageIO.h>
#include <Foundation/Foundation.h>
#include "prtscn_osx.h"

CGImageRef getScreen(const int, const int, int, int);

#endif
