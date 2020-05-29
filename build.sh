#!/bin/bash
adb shell mount -o rw,remount /system
ndk-build && adb push libs/armeabi-v7a/pandorykey /system/bin/pandorykey && adb shell "logcat -c && logcat | /system/bin/pandorykey"
