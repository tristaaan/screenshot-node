#include <napi.h>
#include <iostream>
#include "prtscn_win.h"

Napi::Value getScreenshotSync(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();

  if (info.Length() < 5)
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
  Napi::Function cb = info[4].As<Napi::Function>();

//   IData rawData = getScreen(x, y, width, height);
	std::string* a = getScreen(x, y, width, height);

  std::cout<< a->size() <<std::endl;
  Napi::Value buf = Napi::Buffer<std::string>::New(env, a, a->size());
  cb.Call(env.Global(), {buf});
  return env.Null();
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
  exports.Set(Napi::String::New(env, "getScreenshotSync"), Napi::Function::New(env, getScreenshotSync));
  return exports;
}

NODE_API_MODULE(addon, Init)
