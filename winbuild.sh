#!/usr/bin/env bash
mkdir -p build
cd build || exit;
cmake -G "MinGW Makefiles" -DCMAKE_SH="CMAKE_SH-NOTFOUND" ..
cmake --build .