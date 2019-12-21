#!/usr/bin/env bash
mkdir -p winbuild;
cd winbuild || exit;
pwd;
cmake -DCMAKE_TOOLCHAIN_FILE=../mingw64.cmake ..;
make;