#!/bin/ash
busybox dd if=/dev/block/system of=/usbstick/system.img
busybox dd if=/dev/block/data of=/usbstick/data.img
busybox sleep 5;
busybox reboot;

