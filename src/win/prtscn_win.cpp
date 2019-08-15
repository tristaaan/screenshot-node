#include <iostream>
#include <atlimage.h>
#include "prtscn_win.h"

IData *getScreen(const int x, const int y, const int width, const int height)
{
  HDC hdc = GetDC(NULL);
  int nBitPerPixel = GetDeviceCaps(hdc, BITSPIXEL);
  CImage bmp;
  bmp.Create(width, height, nBitPerPixel);
  BitBlt(bmp.GetDC(), 0, 0, width, height, hdc, 0, 0, SRCCOPY);
  // 释放 DC句柄
  ReleaseDC(NULL, hdc);
  // 释放图片上下文
  bmp.ReleaseDC();

  bmp.Save("C:\\Users\\nashaofu\\Desktop\\Save.png", Gdiplus::ImageFormatBMP);
  signed int length = 0;

  UInt8 *byteData = [];

  IData a = {
      length,
      byteData
  };
  return a;
}