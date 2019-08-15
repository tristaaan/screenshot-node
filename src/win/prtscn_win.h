#ifndef PRTSCN_WINDOWS_H_
#define PRTSCN_WINDOWS_H_
#include <iostream>
#include <atlimage.h>

struct IData
{
  unsigned int length;
  UInt8 *byte;
};

IData *getScreen(const int, const int, const int, const int);

#endif
