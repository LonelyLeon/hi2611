#
##  Makefile
#
include $(PROJECT_CONFIG)

## 子目录
SUBDIRS	=

## 目标文件
OBJS	+= $(foreach f,$(SUBDIRS),$(f)/o_target.o)
OBJS	+=  patvBgLightWin.o patvDigitalNoiseWin.o patvMenuTimeWin.o\
	patvResetWin.o patvPictureOptimizeWin.o patvMenuLangWin.o patvBlueScreenWin.o

## 生成库
O_TARGET	=	o_target.o

## 编译规则
include $(WORKROOT)/project/$(PROJECT)/make/project_rule.mk
