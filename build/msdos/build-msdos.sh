#!/bin/bash
BUILD="$(pwd)/builddir-linux"
DEST="$(pwd)/dist"
LIBS="$DEST/"
rm -rf "$DEST"
mkdir -p "$LIBS"
meson setup --reconfigure -Dstrip=true -Ddebug=false -Doptimization=3 "$BUILD"

meson compile -C "$BUILD"

ldd "$BUILD/tool/pandorytool" | grep "=> /" | awk '{print $3}' | xargs -I '{}' cp -v '{}' "$DEST"
mv "$BUILD/tool/pandorytool" "$DEST"