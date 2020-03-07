#!/usr/bin/env bash
mkdir -p build-win
cd build-win || exit;
mingw64-cmake ..
make

if [ -x "$(command -v upx)" ]; then
  upx -9 pandory.exe
fi

ZIPFILE="pandory-"$(git rev-parse HEAD)".zip"
rm -f $ZIPFILE;
zip -jv $ZIPFILE pandory.exe ../README.md ../HISTORY.md;
