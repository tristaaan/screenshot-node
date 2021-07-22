#include <napi.h>
#include "prtscn_win.h"

Napi::Value getScreenshotSync(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();

  if (info.Length() < 4)
  {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsNumber() || !info[1].IsNumber() || !info[2].IsNumber() || !info[3].IsNumber())
  {
    Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  int x = info[0].As<Napi::Number>().Int32Value();
  int y = info[1].As<Napi::Number>().Int32Value();
  int width = info[2].As<Napi::Number>().Int32Value();
  int height = info[3].As<Napi::Number>().Int32Value();

  IData rawData = getScreen(x, y, width, height);
  Napi::Value buf = Napi::Buffer<uint8_t>::New(env, rawData.byte, rawData.length);
  return buf;
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
  exports.Set(Napi::String::New(env, "getScreenshotSync"), Napi::Function::New(env, getScreenshotSync));
  return exports;
}

NODE_API_MODULE(addon, Init)
