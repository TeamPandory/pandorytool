#!/bin/bash
export VERSIONCODE="$(git describe --tags --abbrev=0 2>/dev/null || git rev-parse --short HEAD)-$(date +%Y%m%d)"
cp -f build/windows/pandorytool.nsi.in build/windows/pandorytool.nsi
sed -i "s#VERSIONCODE#$VERSIONCODE#g" build/windows/pandorytool.nsi
cp -Rv tool/etc/* dist/
makensis build/windows/pandorytool.nsi
rm -rf dist/*
mv build/windows/PandoryTool-Installer.exe "dist/PandoryTool-Installer-$VERSIONCODE.exe"