#!/bin/sh


ap_file="/tmp/rtl_hostapd_2G.conf"
#ap="/root/dvb/network/ap"

killproc()
{
    killall -9 $1
}

start()
{
	mkdir -p /var/lib/dhcp
	touch /var/lib/dhcp/dhcpd.leases

	killproc dhcpd
	killproc hostapd
	killproc wpa_supplicant

	echo "ifconfig wlan0 192.168.191.1 up"
	ifconfig wlan0 192.168.191.1 up
	echo "./hostapd rtl_hostapd_2G.conf -B"
	hostapd $ap_file -B
	echo "dhcpd"
	dhcpd -cf /root/dvb/network/dhcpd.conf
	route del default
	route add default gw 192.168.191.1
}

stop()
{
	route del default
	killproc dhcpd
	killproc hostapd
}

case "$1" in
    start)
    start
    ;;
    stop)
    stop
    ;;

    restart)
    $0 stop
    sleep 1
    $0 start
    ;;

    *)
    echo $"Usage: $0 {start|stop|restart}"
    exit 1
    ;;
esac
exit $RETVAL
