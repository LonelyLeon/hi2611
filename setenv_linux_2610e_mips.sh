#
##  ���������ļ�
#
if [ x"$TERM" = x"cygwin" ] || [ x"$OS" = x"Windows_NT" ]; then
## cygwin��Ҫ����win32����, ��Ҫdos��б��Ŀ¼���, ֻ���ֶ��޸���
  export CYGWIN="nodosfilewarning nontsec nosmbntsec"
  WORKROOT=D:/cygwin/home/public_tree
  export GHS_PATH=C:/GHS/mips423
  PATH=$PATH:/cygdrive/c/GHS/mips423
  export GHS_LMHOST="127.0.0.1"
else
  WORKROOT=$PWD
fi

## gcc�������ר��
BR_PATH="/opt/toolchain-2017/"
TOOLCHAIN="${BR_PATH}/usr"
CROSS_COMPILE=/opt/toolchain-2017/usr/bin/mips-linux-gnu-
## linux�����װ·��, �������õ����������ͷ�ļ��Ϳ�
LINUX_SYS_USR_PATH=`${CROSS_COMPILE}gcc -print-sysroot`/usr
#glib
PKG_CONFIG="${toolchain}/bin/pkg-config"
PKG_CONFIG_PATH="`${CROSS_COMPILE}gcc -print-sysroot`/usr/lib/pkgconfig"
PKG_CONFIG_SYSROOT_DIR="`${CROSS_COMPILE}gcc -print-sysroot`"

## linux�ں���·��, ���ڱ����ں�ģ��
LINUX_KERNEL_DIR=/opt/kernel_workspace_tvruanjian/linux-3.16.43
HI_HTK_PATH=$WORKROOT/htk_dfb
## gcc�Ż��ȼ�
OPTIMIZE_LEVEL=s

## ģ�������ļ�
if [ x$1 = x ]; then
  PROJECT=tv
else
  PROJECT=$1
fi

export PLATFORM_CONFIG=$WORKROOT/project/$PROJECT/make/platform_linux_mips.cfg
export PROJECT_CONFIG=$WORKROOT/project/$PROJECT/make/project_tv.cfg
export LOADER_CONFIG=$WORKROOT/project/$PROJECT/make/loader_8.cfg

## ����ģ��
if [ x$2 = x ]; then
  MAKE_MODULES="platform project"
else
  MAKE_MODULES=$2
fi

export OUTPUT_DIR=$WORKROOT/output

export WORKROOT
export PROJECT
export MAKE_MODULES
export PATH
export BR_PATH
export TOOLCHAIN
export CROSS_COMPILE
export LINUX_SYS_USR_PATH
export PKG_CONFIG
export PKG_CONFIG_PATH
export PKG_CONFIG_SYSROOT_DIR
export LINUX_KERNEL_DIR
export OPTIMIZE_LEVEL
export HI_HTK_PATH
echo $WORKROOT
