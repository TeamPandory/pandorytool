#!/usr/bin/env bash
mkdir -p build-linux
cd build-linux || exit;
cmake ..
make

if [ -x "$(command -v upx)" ]; then
  upx -9 pandory
fi
