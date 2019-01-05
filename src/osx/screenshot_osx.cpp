#include <napi.h>
#include "prtscn_osx.h"

Napi::Value Screenshot(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();

  if (info.Length() < 5)
  {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsNumber() || !info[1].IsNumber() || !info[2].IsNumber() || !info[3].IsNumber() || !info[4].IsFunction())
  {
    Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  int x = info[0].As<Napi::Number>().Int32Value();
  int y = info[1].As<Napi::Number>().Int32Value();
  int width = info[2].As<Napi::Number>().Int32Value();
  int height = info[3].As<Napi::Number>().Int32Value();

  Napi::Function cb = info[4].As<Napi::Function>();

  Napi::Value buf = getScreen(x, y, width, height, env);

  char *k = "123撒打算";

	Napi::Value buf2 = Napi::Buffer<char>::New(env, k, strlen(k));

  cb.Call(env.Global(), {buf2});

  return env.Null();
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
  return Napi::Function::New(env, Screenshot);
}

NODE_API_MODULE(addon, Init)
