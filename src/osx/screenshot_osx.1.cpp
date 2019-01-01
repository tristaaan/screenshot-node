#include <node_api.h>
#include "prtscn_osx.h"
#include <iostream>

napi_value Screenshot(napi_env env, napi_callback_info info)
{
  napi_status status;

  size_t argc = 5;
  napi_value args[5];
  status = napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
  assert(status == napi_ok);
  if (argc < 5)
  {
    napi_throw_type_error(env, nullptr, "Wrong number of arguments");
    return nullptr;
  }

  napi_valuetype args0type;
  status = napi_typeof(env, args[0], &args0type);
  assert(status == napi_ok);

  napi_valuetype args1type;
  status = napi_typeof(env, args[1], &args1type);
  assert(status == napi_ok);

  napi_valuetype args2type;
  status = napi_typeof(env, args[2], &args2type);
  assert(status == napi_ok);

  napi_valuetype args3type;
  status = napi_typeof(env, args[3], &args3type);
  assert(status == napi_ok);

  napi_valuetype args4type;
  status = napi_typeof(env, args[4], &args4type);
  assert(status == napi_ok);

  if (args0type != napi_number || args1type != napi_number || args2type != napi_number || args3type != napi_number || args4type != napi_function)
  {
    napi_throw_type_error(env, nullptr, "Wrong arguments");
    return nullptr;
  }

  int x;
  status = napi_get_value_int32(env, args[0], &x);
  assert(status == napi_ok);

  int y;
  status = napi_get_value_int32(env, args[1], &y);
  assert(status == napi_ok);

  int width;
  status = napi_get_value_int32(env, args[2], &width);
  assert(status == napi_ok);

  int height;
  status = napi_get_value_int32(env, args[3], &height);
  assert(status == napi_ok);

  napi_value global;
  status = napi_get_global(env, &global);
  assert(status == napi_ok);

  napi_value argv[2];
  CGImageRef image_ref = getScreen(x, y, width, height);

  status = napi_call_function(env, global, args[4], 1, argv, nullptr);
  assert(status == napi_ok);

  std::cout<< image_ref << std::endl;
  return nullptr;
}

napi_value Init(napi_env env, napi_value exports)
{
  napi_status status = napi_create_function(env, nullptr, NAPI_AUTO_LENGTH, Screenshot, nullptr, &exports);
  assert(status == napi_ok);
  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
