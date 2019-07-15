#!/bin/sh

usr_cur_dir=${PWD}
usr_tmp_dir=${usr_cur_dir}/ramdisk_setip_tmp
mkdir -p ${usr_tmp_dir}
cp -av ramdisk.gz ${usr_tmp_dir}
cd ${usr_tmp_dir}

gzip -d ramdisk.gz
mkdir -p rootfs
cd rootfs
cpio -ivmd < ../ramdisk
cp -av ${usr_cur_dir}/mira.sh root/dvb
#cp -av ${usr_cur_dir}/wpa_supplicant root/sbin

cp -av ${usr_cur_dir}/udisk_action2 etc/mdev
cp -av ${usr_cur_dir}/8188eu.ko root/dvb/2610
cp -av ${usr_cur_dir}/rtwpriv usr/bin
cp -av ${usr_cur_dir}/mdev.conf etc
cp -av ${usr_cur_dir}/ap/network root/dvb
cp -av ${usr_cur_dir}/ap/hostapd usr/bin
cp -av ${usr_cur_dir}/ap/ap_start.sh root/dvb
mips-linux-gnu-strip --strip-unneeded usr/bin/hostapd
cp -av ${usr_cur_dir}/dhcpd sbin
mips-linux-gnu-strip --strip-unneeded sbin/dhcpd

################iptv#################################################
cp -av ${usr_cur_dir}/zhilian/ln_iptv_fs/lib/* lib 
cp -av ${usr_cur_dir}/zhilian/ln_iptv_fs/usr/* usr/lib 
cp --remove-destination ${usr_cur_dir}/zhilian/iptv_lib/lib/* lib 
cp --remove-destination ${usr_cur_dir}/zhilian/iptv_lib/usr/* usr/lib
#####################################################################

################airplay##############################################
cp -av ${APP_DIR}/output/bin/mdnsd root/dvb/2610
cp -av ${APP_DIR}/output/lib/libbjairplay.so usr/lib
cp -av ${APP_DIR}/output/lib/libdns_sd.so usr/lib 
cp -av ${usr_cur_dir}/airplay/libcrypto.so usr/lib
cp -av ${usr_cur_dir}/airplay/libcrypto.so.1.0.0 usr/lib
cp -av ${usr_cur_dir}/airplay/libssl.so usr/lib
cp -av ${usr_cur_dir}/airplay/libssl.so.1.0.0 usr/lib
mips-linux-gnu-strip --strip-unneeded usr/lib/libbjairplay.so
#####################################################################

cp -av ${usr_cur_dir}/rcS etc/init.d
cp -av ${APP_DIR}/output/lib/libffplay.so usr/lib
cp -av ${APP_DIR}/output/bin/app.elf ${APP_DIR}/output/modules/*.ko root/dvb/2610
mips-linux-gnu-strip --strip-unneeded root/dvb/2610/*.ko usr/lib/libffplay.so
chown root root/dvb/2610/app.elf
chgrp root root/dvb/2610/app.elf
chmod 777 root/dvb/2610/app.elf
cd ..
mkfs.cramfs -v -N little -b 16384 rootfs cramfs.img

mv cramfs.img ${usr_cur_dir}/cramfs.img
cd ${usr_cur_dir}
rm -rf ${usr_tmp_dir}
