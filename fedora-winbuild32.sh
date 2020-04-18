#!/usr/bin/env bash
mkdir -p build-win32
cd build-win32 || exit;
mingw32-cmake ..
make

if [ -x "$(command -v upx)" ]; then
  upx -9 pandory.exe
fi

rm -rf sticks;
mkdir sticks;
cd sticks;
wget https://github.com/emuchicken/pandorytool/archive/stick-jailbreak.tar.gz;
wget https://github.com/emuchicken/pandorytool/archive/stick-backup.tar.gz;
cd ..;

rm -rf controls.tar.gz;
rm -rf controls;
rm -rf pandorytool-controls;
wget https://github.com/emuchicken/pandorytool/archive/controls.tar.gz;
tar xvf controls.tar.gz;
mv pandorytool-controls/ controls/;

cp ../*.md .;

ZIPFILE="pandory-"$(git rev-parse HEAD)".zip"
rm -f $ZIPFILE;
zip -v -r $ZIPFILE pandory.exe controls/ sticks/ *.md;
