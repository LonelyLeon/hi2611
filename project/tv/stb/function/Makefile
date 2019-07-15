#
##  Makefile
#
include $(PROJECT_CONFIG)

## 子目录
SUBDIRS	= scan db sdk player stb nvpart-app si custom-config adv-logo sn-burn loader font vip_param media upgrade hp
ifeq ($(G_DBG_DISK_OPEN), y)
SUBDIRS	+= dbg-disk
endif

##多媒体功能是否打开(y/n)
ifeq ($(G_MUTIMEDIA_EN), y)
SUBDIRS	+=  file_scan
endif

##linux平台编译wifi网络相关
ifeq ($(G_SYSTEM), linux)
SUBDIRS	+= network
endif

##linux平台编译vgatohdmi
ifeq ($(G_TV_PEOJECT_TOUYY), y)
SUBDIRS	+= vgatohdmi
endif

## 目标文件
OBJS	+= $(foreach f,$(SUBDIRS),$(f)/o_target.o)
OBJS	+= 

## 生成库
O_TARGET	=	o_target.o

## 编译规则
include $(WORKROOT)/project/$(PROJECT)/make/project_rule.mk