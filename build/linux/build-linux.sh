#!/bin/bash
cp -f build/linux/com.teampandory.pandorytool.yaml.in build/linux/com.teampandory.pandorytool.yaml
sed -i "s#REPLACE_SCRAPE_USERNAME#$SCRAPE_USERNAME#g" build/linux/com.teampandory.pandorytool.yaml
sed -i "s#REPLACE_SCRAPE_PASSWORD#$SCRAPE_PASSWORD#g" build/linux/com.teampandory.pandorytool.yaml
sed -i "s#REPLACE_SCRAPE_URL#$SCRAPE_URL#g" build/linux/com.teampandory.pandorytool.yaml

flatpak-builder --repo=repo --install --user --force-clean build-dir build/linux/com.teampandory.pandorytool.yaml
flatpak build-bundle repo pandorytool.flatpak com.teampandory.pandorytool

export VERSIONCODE="$(git describe --tags --abbrev=0 2>/dev/null || git rev-parse --short HEAD)-$(date +%Y%m%d)"
export TARGET="PandoryTool-$VERSIONCODE"
mkdir -p "dist/$TARGET/"


cp -Rv tool/etc/* "dist/$TARGET"
rm -rf "dist/$TARGET/*.bat"
mv pandorytool.flatpak "dist/$TARGET/PandoryTool-Installer-$VERSIONCODE.flatpak"
pushd dist
tar czf "../PandoryTool-$VERSIONCODE.tgz" "$TARGET"
popd
rm -rf "dist/$TARGET/*"
mv "PandoryTool-$VERSIONCODE.tgz" dist/