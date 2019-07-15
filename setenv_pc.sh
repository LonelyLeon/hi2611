#
##  ���������ļ�
#

if [ "$TERM" = "cygwin" ]; then
## cygwin��Ҫ����win32����, ��Ҫdos��б��Ŀ¼���, ֻ���ֶ��޸���
  export WORKROOT=E:/public_tree_branch_hd
else
  export WORKROOT=$PWD
fi

## gccר��
CROSS_COMPILE=

## ģ�������ļ�
if [ x$1 = x ]; then
  PROJECT=thai_gmm
else
  PROJECT=$1
fi

export PLATFORM_CONFIG=$WORKROOT/project/$PROJECT/make/platform_pc.cfg
export PROJECT_CONFIG=$WORKROOT/project/$PROJECT/make/project_2830_8_64.cfg
export LOADER_CONFIG=$WORKROOT/project/$PROJECT/make/loader_8.cfg

export FFMAIN_IPADDR="192.168.1.105"

## ����ģ��
if [ x$2 = x ]; then
  MAKE_MODULES="platform project"
else
  MAKE_MODULES=$2
fi

export OUTPUT_DIR=$WORKROOT/output

export PROJECT
export MAKE_MODULES
export PATH
echo $WORKROOT
