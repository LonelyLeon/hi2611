#
##  工程配置文件
#
if [ x"$TERM" = x"cygwin" ] || [ x"$OS" = x"Windows_NT" ]; then
## cygwin下要兼容win32程序, 需要dos正斜杠目录风格, 只能手动修改了
  export CYGWIN="nodosfilewarning nontsec nosmbntsec"
  WORKROOT=D:/cygwin/home/public_tree
  export GHS_PATH=C:/GHS/mips423
  PATH=$PATH:/cygdrive/c/GHS/mips423
  export GHS_LMHOST="127.0.0.1"
else
  WORKROOT=$PWD
fi

## gcc交叉编译专用
BR_PATH="/opt/toolchain-2017/"
TOOLCHAIN="${BR_PATH}/usr"
CROSS_COMPILE=/opt/toolchain-2017/usr/bin/mips-linux-gnu-
## linux软件安装路径, 用于引用第三方软件的头文件和库
LINUX_SYS_USR_PATH=`${CROSS_COMPILE}gcc -print-sysroot`/usr
#glib
PKG_CONFIG="${toolchain}/bin/pkg-config"
PKG_CONFIG_PATH="`${CROSS_COMPILE}gcc -print-sysroot`/usr/lib/pkgconfig"
PKG_CONFIG_SYSROOT_DIR="`${CROSS_COMPILE}gcc -print-sysroot`"

## linux内核树路径, 用于编译内核模块
LINUX_KERNEL_DIR=/opt/kernel_workspace_tvruanjian/linux-3.16.43
HI_HTK_PATH=$WORKROOT/htk_dfb
## gcc优化等级
OPTIMIZE_LEVEL=s

## 模块配置文件
if [ x$1 = x ]; then
  PROJECT=tv
else
  PROJECT=$1
fi

export PLATFORM_CONFIG=$WORKROOT/project/$PROJECT/make/platform_linux_mips.cfg
export PROJECT_CONFIG=$WORKROOT/project/$PROJECT/make/project_tv.cfg
export LOADER_CONFIG=$WORKROOT/project/$PROJECT/make/loader_8.cfg

## 编译模块
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
