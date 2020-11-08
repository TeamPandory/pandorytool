#!/bin/ash
OTA=$(dirname "$0")
ROOT="$OTA/../"
cd "$OTA"

dd if=/dev/block/zram      of=$OTA/backup/zram.img
dd if=/dev/block/mtdblock0 of=$OTA/backup/mtdblock0.img
dd if=/dev/block/mtdblock1 of=$OTA/backup/mtdblock1.img
dd if=/dev/block/cache     of=$OTA/backup/cache.img
dd if=/dev/block/logo      of=$OTA/backup/logo.img
dd if=/dev/block/recovery  of=$OTA/backup/recovery.img
dd if=/dev/block/misc      of=$OTA/backup/misc.img
dd if=/dev/block/boot      of=$OTA/backup/boot.img
dd if=/dev/block/system    of=$OTA/backup/system.img
dd if=/dev/block/data      of=$OTA/backup/data.img

killall com.moorechip.datarecovery
killall com.moorechip.datamover
killall com.retrostation.datarecovery
killall com.retrostation.datamover

