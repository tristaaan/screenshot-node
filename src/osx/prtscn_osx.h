#ifndef PRTSCN_OSX_H_
#define PRTSCN_OSX_H_
#include <Foundation/Foundation.h>
#include <CoreServices/CoreServices.h>
#include <string>

struct IData
{
  unsigned int length;
  UInt8 *byte;
};

IData getScreen(const int, const int, const int, const int, const std::string);

#endif
