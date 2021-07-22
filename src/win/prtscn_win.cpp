#include <iostream>
#include <atlimage.h>
#include "prtscn_win.h"

IData getScreen(const int x, const int y, const int width, const int height)
{
  HDC hdc = GetDC(NULL);
  int nBitPerPixel = GetDeviceCaps(hdc, BITSPIXEL);
  CImage bmp;
  bmp.Create(width, height, nBitPerPixel);
  BitBlt(bmp.GetDC(), 0, 0, width, height, hdc, x, y, SRCCOPY);
  // 释放 DC句柄 // release DC handle
  ReleaseDC(NULL, hdc);
  // 释放图片上下文 // release picture context
  bmp.ReleaseDC();

  unsigned int length = width * height * 4;
  uint8_t *byteData = (uint8_t *) malloc(length);
  uint8_t *ptr;
  int i = 0;
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++, i += 4) {
      ptr = (uint8_t *) bmp.GetPixelAddress(x, y);
      byteData[i] = ptr[0];
      byteData[i + 1] = ptr[1];
      byteData[i + 2] = ptr[2];
      byteData[i + 3] = 255;
    }
  }

  IData a = {
      length,
      byteData
  };
  return a;
}