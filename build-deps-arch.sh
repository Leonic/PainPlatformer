#!/bin/bash
sudo pacman -Sy sdl2 sdl2-image sdl2-ttf sdl2-gfx rapidjson python3 fmt zlib
cmake -DCMAKE_BUILD_TYPE="Release" -Bbuild .