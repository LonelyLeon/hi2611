#
##  Makefile
#
include $(PROJECT_CONFIG)

## 子目录
SUBDIRS	= function advertisement

ifeq ($(G_TV_UI_STYLE),MUTICOLOR)
	SUBDIRS	+= tvmenu
endif	

ifeq ($(G_TV_UI_STYLE),BLACK)
	SUBDIRS	+= tvmenu_black
endif	

ifeq ($(G_TV_UI_STYLE),MINI)
	SUBDIRS	+= tvmenu_mini
endif	

ifeq ($(G_TV_SOFT_TYPE), TV_STB)
	SUBDIRS	+= game dvb_databroadcast menu
endif

ifeq ($(G_TV_DLNA_SOURCE), y)
	SUBDIRS	+= dlna
endif

## miracast里自动扫描信道用到ap模式
ifeq ($(G_TV_MIRACAST_SOURCE), y)
	SUBDIRS	+= mira ts2net
endif	

ifeq ($(G_TV_SUPPORT_IPTV), y)
	SUBDIRS	+= iptv
endif

ifeq ($(G_TV_SUPPORT_AIRPLAY), y)
	SUBDIRS	+= airplay
endif

## 目标文件
OBJS	+= $(foreach f,$(SUBDIRS),$(f)/o_target.o)
OBJS	+= stb.o



## 生成库
LIB_TARGET	=	stb

## 编译规则
include $(WORKROOT)/project/$(PROJECT)/make/project_rule.mk
