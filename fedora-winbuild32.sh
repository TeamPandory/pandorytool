#!/usr/bin/env bash
mkdir -p build-win32
cd build-win32 || exit;
mingw32-cmake ..
make

if [ -x "$(command -v upx)" ]; then
  upx -9 pandory.exe
fi

cp -Rv controls/ build-win32/;

ZIPFILE="pandory-"$(git rev-parse HEAD)".zip"
rm -f $ZIPFILE;
zip -jv $ZIPFILE pandory.exe ../README.md ../HISTORY.md;
