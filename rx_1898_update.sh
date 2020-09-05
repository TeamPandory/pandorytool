#!/bin/sh
cd "$sdpath"
mount -o rw,remount /system
killall pandorykey
rm -f /system/bin/pandoryjailbreak
cp -f pandory/pandoryjailbreak /system/bin/
chmod +x /system/bin/pandoryjailbreak
chown root:shell /system/bin/pandoryjailbreak
/system/bin/pandoryjailbreak

killall sh
