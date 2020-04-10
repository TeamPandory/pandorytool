#!/system/bin/sh

while true; do

if [ -f "/storage/external_storage/sda1/pandory.sh" ]; then 
	busybox ash /storage/external_storage/sda1/pandory.sh; 
	exit 0;
fi


if [ -f "/storage/external_storage/sdb1/pandory.sh" ]; then 
	busybox ash /storage/external_storage/sdb1/pandory.sh; 
	exit 0;
fi


if [ -f "/storage/external_storage/sda/pandory.sh" ]; then 
	busybox ash /storage/external_storage/sda/pandory.sh; 
	exit 0;
fi


if [ -f "/storage/external_storage/sdb/pandory.sh" ]; then 
	busybox ash /storage/external_storage/sdb/pandory.sh; 
	exit 0;
fi

busybox sleep 5; 
done
