   {
    "targets": [
      {
        "target_name": "printer",
         "cflags": ["-Wall", "-std=c++11", "-lcups"],
        "sources": [ "main.cpp" ],
        "include_dirs" : [
          "<!@(node -p \"require('node-addon-api').include\")"
        ],
        "defines": [ "NAPI_DISABLE_CPP_EXCEPTIONS" ],
        'conditions': [
        ['OS=="mac"', {
          'xcode_settings': {
            'GCC_ENABLE_CPP_EXCEPTIONS': 'YES'
          }
        }]
      ]
      }
    ]
  }