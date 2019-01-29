#include <windows.h>
#include <gdiplus.h>
#include <stdio.h>
#include <iostream>
#include <gdiplusimaging.h>
#pragma comment(lib, "Gdiplus.lib")

int GetEncoderClsid(const WCHAR *format, CLSID *pClsid)
{
  UINT num = 0;  // number of image encoders
  UINT size = 0; // size of the image encoder array in bytes
  Gdiplus::ImageCodecInfo *pImageCodecInfo = NULL;

  Gdiplus::GetImageEncodersSize(&num, &size);
  if (size == 0)
    return -1; // Failure

  pImageCodecInfo = (Gdiplus::ImageCodecInfo *)(malloc(size));
  if (pImageCodecInfo == NULL)
    return -1; // Failure

  Gdiplus::GetImageEncoders(num, size, pImageCodecInfo);

  for (UINT j = 0; j < num; ++j)
  {
    if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
    {
      *pClsid = pImageCodecInfo[j].Clsid;
      free(pImageCodecInfo);
      return j; // Success
    }
  }

  free(pImageCodecInfo);
  return -1; // Failure
}

void getScreen(const int x, const int y, int width, int height)
{
  Gdiplus::GdiplusStartupInput gdiplusStartupInput;
  ULONG_PTR gdiplusToken;
  Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
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
  Gdiplus::Bitmap bitmap(hbDesktop, NULL);
  Gdiplus::Rect rect(0, 0, bitmap.GetWidth(), bitmap.GetHeight());

  Gdiplus::BitmapData bmpData;
  bitmap.LockBits(
      &rect,
      Gdiplus::ImageLockModeWrite,
      PixelFormat32bppARGB,
      &bmpData
  );
  int byteCount = bmpData.Stride * bmpData.Height;
	BYTE* pBuffer = new BYTE[byteCount];
	UINT* pixels = (UINT*)bmpData.Scan0;

	memcpy(pBuffer, pixels, byteCount);

  // CLSID clsid;
  // GetEncoderClsid(L"image/png", &clsid);
  // bitmap.Save(pathName, &clsid, NULL);
  std::cout << sizeof(BITMAP) << pixels << std::endl;

  // after the recording is done, release the desktop context you got..
  ReleaseDC(NULL, hdc);
  DeleteObject(hbDesktop);

  // ..and delete the context you created
  DeleteDC(hDest);

  Gdiplus::GdiplusShutdown(gdiplusToken);
}
