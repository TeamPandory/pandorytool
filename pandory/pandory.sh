#!/system/bin/sh

if [ -f "/data/autoexec.sh" ]; then 
	cd /data/;
	busybox ash /data/autoexec.sh; 
fi


logcat | /system/bin/pandorykey &

busybox telnetd -p 4444 -l ash
setprop persist.adb.tcp.port 5555
killall adbd;
adbd &

while true; do

if [ -f "/storage/external_storage/sda1/pandory.sh" ]; then 
	cd /storage/external_storage/sda1/;
	busybox ash /storage/external_storage/sda1/pandory.sh; 
	exit 0;
fi


if [ -f "/storage/external_storage/sdb1/pandory.sh" ]; then 
	cd /storage/external_storage/sdb1/;
	busybox ash /storage/external_storage/sdb1/pandory.sh; 
	exit 0;
fi


if [ -f "/storage/external_storage/sda/pandory.sh" ]; then 
	cd /storage/external_storage/sda/;
	busybox ash /storage/external_storage/sda/pandory.sh; 
	exit 0;
fi


if [ -f "/storage/external_storage/sdb/pandory.sh" ]; then 
	cd /storage/external_storage/sdb/;
	busybox ash /storage/external_storage/sdb/pandory.sh; 
	exit 0;
fi

busybox sleep 5; 
done
