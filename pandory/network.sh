#loads up usbnet0 for android w/dhcp and sets up dns for cloudnet 1.1.1.1

sleep 50
netcfg usbnet0 dhcp
netcfg usbnet0 up
setprop net.dns1 1.1.1.1
setprop net.dns2 1.0.0.1
setprop net.usbnet0.dns1 1.1.1.1
setprop net.usbnet0.dns2 1.0.0.1

netcfg ip6tnl0 up
netcfg tunl0 up
netcfg sit0 up
ndc resolver setifdns netusb0 "" 1.1.1.1 1.0.0.1
ndc resolver setdefaultif netusb0