#ifndef PRTSCN_WINDOWS_H_
#define PRTSCN_WINDOWS_H_
#include <iostream>
#include <atlimage.h>

struct IData
{
  unsigned int length;
  uint8_t *byte;
};

IData getScreen(const int, const int, const int, const int);

#endif
