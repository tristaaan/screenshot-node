#ifndef PRTSCN_OSX_H_
#define PRTSCN_OSX_H_
#include <napi.h>
#include <CoreGraphics/CoreGraphics.h>

Napi::Value getScreen(const int, const int, const int, const int, Napi::Env);

#endif
