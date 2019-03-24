#include <iostream>
#include <atlimage.h>

BYTE *getScreen(const int x, const int y, const int width, const int height)
{
	HDC hdc = GetDC(NULL);
	HDC hDest = CreateCompatibleDC(hdc); // create a device context to use yourself
	HBITMAP hbDesktop = CreateCompatibleBitmap(hdc, width, height);
	SelectObject(hDest, hbDesktop);
	BitBlt(hDest, 0, 0, width, height, hdc, x, y, SRCCOPY);
	CImage bmp;
	bmp.Attach(hbDesktop, CImage::DIBOR_DEFAULT);
  ReleaseDC(NULL, hDest);

	// 释放图片上下文
	// bmp.ReleaseDC();
	// BYTE *a = (BYTE *)bmp.GetBits();
	// std::cout << sizeof(a) << std::endl;
	// bmp.Save("C:\\Users\\nashaofu\\Desktop\\Save.png", );
  bmp.Save("C:\\Users\\nashaofu\\Desktop\\Save.png");
  BYTE * k;

	return k;
}