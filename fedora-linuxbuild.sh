#!/usr/bin/env bash
mkdir -p build-linux
cd build-linux || exit;
cmake ..
make

cp -Rv ../controls/ ./;
