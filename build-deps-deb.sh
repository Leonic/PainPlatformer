#!/bin/bash
sudo apt update
sudo apt install -y libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-gfx-dev rapidjson-dev zlib1g-dev python3-dev libfmt-dev
cmake -DCMAKE_BUILD_TYPE="Release" -Bbuild .