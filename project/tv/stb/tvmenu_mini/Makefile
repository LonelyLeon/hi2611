#
##  Makefile
#
include $(PROJECT_CONFIG)

## 子目录
SUBDIRS	= resource stbmenu playwin image voice function time tunning adjust media msgbox channelman factory

ifeq ($(G_TV_MIRACAST_SOURCE), y)
	SUBDIRS	+= wifidisplay
endif

## 目标文件
OBJS	+= $(foreach f,$(SUBDIRS),$(f)/o_target.o)
OBJS	+= 

## 生成库
O_TARGET	=	o_target.o

## 编译规则
include $(WORKROOT)/project/$(PROJECT)/make/project_rule.mk
