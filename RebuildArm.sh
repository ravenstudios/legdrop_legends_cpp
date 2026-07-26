#!/usr/bin/env bash

set -e

rm -rf build

cmake -S . -B build \
    -DCMAKE_BUILD_TYPE=Debug \
    -DCMAKE_OSX_ARCHITECTURES=arm64 \
    -DCMAKE_PREFIX_PATH="/opt/homebrew"

cmake --build build -j"$(sysctl -n hw.ncpu)"