#!/bin/sh

RETVAL=0
#HOME_DIR=$(cd `dirname $0`; pwd)
HOME_DIR=/root/dvb/
BIN_DIR=${HOME_DIR}/bin
LIB_DIR=${HOME_DIR}/lib
CONF_DIR=${HOME_DIR}/conf

#LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$LIB_DIR
#export LD_LIBRARY_PATH
#export PATH=.:$PATH

#. $HOME_DIR/functions

killproc()
{
    killall -9 $1
}

config_mira()
{
    echo "config mira"
    echo "BIN_DIR: " ${BIN_DIR}
    echo "LIB_DIR: " ${LIB_DIR}

    ln -s /sbin/ip /bin/ip
	
    rm -r /run/miracle/wifi/*
    rm -r /var/run/wpa_supplicant/*
    rm -r /var/run/miracle/wlan0

    mkdir /var/run/wpa_supplicant
    mkdir -p /run/miracle/wifi

    mv /dev/random /dev/random.bak

    ln -s /dev/urandom /dev/random

    ifconfig wlan0 up
}

unconfig()
{
    echo "un config "
}

start()
{

    echo $"------Start  now......"

    mkdir /var/tmp

    config_mira

    wpa_supplicant -Dnl80211 -c  ${CONF_DIR}/CBoxOne.conf -i wlan0 &

	sleep 1

    ${BIN_DIR}/haier_dhcp &
    
    RETVAL=$?
    return $RETVAL
}

stop()
{
    echo $"------Stop  now......"
    
    echo -n "stop MiraAdapter"
	
    killproc wpa_supplicant
    echo
	
    killproc haier_dhcp
    echo

    unconfig

    echo "OK"
    return $RETVAL
}

case "$1" in
    start)
    start $2
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
