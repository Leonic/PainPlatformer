#!/bin/bash
sudo pacman -Sy sdl2 sdl2_image sdl2_ttf sdl2_gfx rapidjson python3 fmt zlib
cmake -DCMAKE_BUILD_TYPE="Release" -Bbuild .
