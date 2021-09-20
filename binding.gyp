{
    "targets": [
        {
            "target_name": "screenshot",
            "include_dirs": ["<!@(node -p \"require('node-addon-api').include\")"],
            "cflags!": ["-fno-exceptions"],
            "cflags_cc!": ["-fno-exceptions"],
            "defines": ["NAPI_DISABLE_CPP_EXCEPTIONS"],
            "conditions": [
                [
                    "OS==\"linux\"",
                    {
                        "sources": ["src/linux/screenshot_linux.cpp", "src/linux/prtscn_linux.c"],
                        "link_settings": {
                            "libraries": ["-lX11", "-lpng"]
                        }
                    }
                ],
                [
                    "OS==\"mac\"",
                    {
                        "xcode_settings": {
                            "GCC_ENABLE_CPP_EXCEPTIONS": "YES",
                            "OTHER_CFLAGS": ["-ObjC++", "-stdlib=libc++"]
                        },
                        "sources": ["src/osx/screenshot_osx.cpp", "src/osx/prtscn_osx.m"],
                        "link_settings": {
                            "libraries": ["-framework CoreServices"]
                        }
                    }
                ],
                [
                    "OS==\"win\"",
                    {
                        "msvs_settings": {
                            "VCCLCompilerTool": {
                                "ExceptionHandling": 1
                            }
                        },
                        "sources": ["src/win/screenshot_win.cpp", "src/win/prtscn_win.cpp"],
                        "libraries": [
                            "<(module_root_dir)/../Little-CMS/bin/lcms2.lib",
                            # "<(module_root_dir)/../Little-CMS/Lib/MS/lcms2_static.lib"
                        ],
                        "include_dirs": [
                            "<(module_root_dir)/../Little-CMS/include"
                        ],
                        "copies": [
                            {
                                "destination": "<(module_root_dir)/build/Release",
                                "files": [
                                    "<(module_root_dir)/../Little-CMS/bin/lcms2.dll"
                                ]
                            }
                        ]
                    }
                ]
            ]
        }
    ]
}
