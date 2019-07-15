#!/bin/sh

#export BR_PATH="/home/opt/buildroot-2017.02.2"
#export TOOLCHAIN="${BR_PATH}/output/host/usr"
export BR_PATH="/opt/toolchain-2017/"
export TOOLCHAIN="${BR_PATH}/usr"
export CROSS="${TOOLCHAIN}/bin/mips-linux-gnu-"

export ARCH="mips"
export CROSS_COMPILE="mips-linux-gnu-"
export SYSROOT="`${CROSS}gcc -print-sysroot`"
export PREFIX="/usr"

export PATH="${TOOLCHAIN}/bin:${PATH}"
export APP_DIR="/mnt/hgfs/linux/code/coder_06_25/coder_06_25"
