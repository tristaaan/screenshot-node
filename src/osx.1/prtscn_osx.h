#ifndef PRTSCN_OSX_H_
#define PRTSCN_OSX_H_
#include <CoreServices/CoreServices.h>

CFDataRef getScreen(const int, const int, const int, const int);

#endif
