#!/usr/bin/env bash
mkdir -p build
cd build || exit;
cmake -G "MinGW Makefiles" -DCMAKE_SH="CMAKE_SH-NOTFOUND" ..
cmake --build .

if [ -x "$(command -v upx)" ]; then
  upx -9 pandory.exe
fi