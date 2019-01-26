{
    "targets": [
        {
            "target_name": "screenshot",
            "include_dirs": [
                "<!@(node -p \"require('node-addon-api').include\")"
            ],
                              "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
                  'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
            "conditions": [
                ['OS=="linux"', {
                    "sources": ["src/linux/screenshot_linux.cpp", "src/linux/prtscn_linux.c"],
                    "link_settings": {
                        "libraries": [
                            "-lX11",
                            "-lpng"
                        ]
                    }
                }],
                ['OS=="mac"', {
                    'xcode_settings': {
                        'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
                        'OTHER_CFLAGS': [
                            '-ObjC++'
                        ]
                    },
                    "sources": ["src/osx/screenshot_osx.cpp", "src/osx/prtscn_osx.m"],
                    "link_settings": {
                        "libraries": [
                            "-framework CoreServices"
                        ]
                    }
                }],
                ['OS=="win"', {
                    "sources": ["src/windows/screenshot_windows.cpp", "src/windows/prtscn_windows.cpp"]
                }]
            ]
        }
    ]
}
