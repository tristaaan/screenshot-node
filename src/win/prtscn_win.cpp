#include <iostream>
#include <atlimage.h>
#include "lcms2.h"
#include "prtscn_win.h"

cmsHPROFILE hInProfile = cmsCreate_sRGBProfile();
cmsHPROFILE hOutProfile = NULL;
cmsHTRANSFORM hTransform = NULL;

IData getScreen(const int x, const int y, const int width, const int height, const std::string colorSpace)
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

  if (!hOutProfile)
  {
    hOutProfile = cmsOpenProfileFromFile("C:/Windows/System32/spool/drivers/color/AdobeRGB1998.icc", "r");
  }

  if (!hTransform) {
    hTransform = cmsCreateTransform(hInProfile,
                                    TYPE_RGBA_8,
                                    hOutProfile,
                                    TYPE_RGBA_8,
                                    INTENT_PERCEPTUAL,
                                    cmsFLAGS_LOWRESPRECALC);
  }

  unsigned int length = width * height * 4;
  uint8_t *byteData = (uint8_t *) malloc(length);
  uint8_t *ptr;
  int i = 0;
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++, i += 4) {
      ptr = (uint8_t *) bmp.GetPixelAddress(x, y);
      byteData[i] = ptr[2];
      byteData[i + 1] = ptr[1];
      byteData[i + 2] = ptr[0];
      byteData[i + 3] = 255;
    }
  }


  IData a;
  if (colorSpace == "srgb") {
    a = {
      length,
      byteData
    };
  } else { // else if (colorSpace == 'adobergb) {
    uint8_t *newByteData = (uint8_t *)malloc(length);
    cmsDoTransform(
      hTransform,
      byteData,
      newByteData,
      length / 4 // number of pixels to be transformed
    );
    a = {
      length,
      newByteData
    };
    free(byteData);
    // cmsDeleteTransform(hTransform);
  }

  return a;
}