#!/bin/bash
BUILD="$(pwd)/builddir-win"
DEST="$(pwd)/dist"
LIBS="$DEST/bin/"
rm -rf "$DEST"
mkdir -p "$LIBS"
meson setup --reconfigure --cross-file=build/windows/linux-mingw-w64-64bit.meson -Dstrip=true -Ddebug=false -Doptimization=3 "$BUILD"

meson compile -C "$BUILD"
mv "$BUILD/tool/pandorytool.exe" "$DEST/bin"
mv "$BUILD/stub/pandory.exe" "$DEST"

pushd /usr/x86_64-w64-mingw32/sys-root/mingw/bin/
cp -f libgcc_s_seh-1.dll "$LIBS"
cp -f libwinpthread-1.dll "$LIBS"
cp -f libstdc++-6.dll "$LIBS"
cp -f libarchive-13.dll "$LIBS"
cp -f zlib1.dll "$LIBS"
cp -f libboost_filesystem-mt-x64.dll "$LIBS"
cp -f libcrypto-3-x64.dll "$LIBS"
cp -f libcurl-4.dll "$LIBS"
cp -f libidn2-0.dll "$LIBS"
cp -f libssh2-1.dll "$LIBS"
cp -f libssl-3-x64.dll "$LIBS"
cp -f libcurl-4.dll "$LIBS"
cp -f libtinyxml2.dll "$LIBS"
cp -f libcurlpp.dll "$LIBS"
popd

pushd "$LIBS"
for DLL in *.dll; do
/usr/bin/x86_64-w64-mingw32-strip "$DLL"
done
popd