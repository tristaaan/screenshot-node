#include <windows.h>
#include <gdiplus.h>
#include <stdio.h>
#include <iostream>

void getScreen(const int x, const int y, int width, int height)
{
  if (width == 0)
  {
    width = GetSystemMetrics(SM_CXSCREEN);
  }
  if (height == 0)
  {
    height = GetSystemMetrics(SM_CYSCREEN);
  }

  HDC hdc = GetDC(NULL);               // get the desktop device context
  HDC hDest = CreateCompatibleDC(hdc); // create a device context to use yourself

  // create a bitmap
  HBITMAP hbDesktop = CreateCompatibleBitmap(hdc, width, height);

  // use the previously created device context with the bitmap
  SelectObject(hDest, hbDesktop);
  BitBlt(hDest, 0, 0, width, height, hdc, x, y, SRCCOPY);
  // Get the BITMAP from the HBITMAP
  BITMAP bmpScreen;
  // Get the BITMAP from the HBITMAP
  GetObject(hbDesktop, 1024, &bmpScreen);
  // bmpScreen.
  std::cout<<sizeof(BITMAP)<<std::endl;

  // after the recording is done, release the desktop context you got..
  ReleaseDC(NULL, hdc);
  DeleteObject(hbDesktop);

  // ..and delete the context you created
  DeleteDC(hDest);
}
