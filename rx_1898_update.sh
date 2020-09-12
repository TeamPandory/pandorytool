#!/bin/sh
cd "$sdpath"
am broadcast -a com.trimui.RX_UPDATE_INFO --es info "Pandory! - Backing up now..."
dd if=/dev/block/mmcblk0 of="$sdpath/backup.img"
am broadcast -a com.trimui.RX_UPDATE_INFO --es info "Finished. Goodbye!"
killall sh

