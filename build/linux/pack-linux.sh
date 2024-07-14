#!/bin/bash
find .
DEST="$(pwd)/dist"
APPDIR="$(pwd)/build/linux/AppImage"
mv "$DEST/pandorytool" "$APPDIR/usr/bin/"
mv "$DEST"/* "$APPDIR/usr/lib/"
ARCH=x86_64 appimagetool "$APPDIR"
mv *.AppImage "$DEST/"