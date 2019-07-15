#
##  Makefile
#
include $(PROJECT_CONFIG)

## 子目录
SUBDIRS	=

## 目标文件
OBJS	+= $(foreach f,$(SUBDIRS),$(f)/o_target.o)
OBJS	+=  patvBootChannelWin.o patvOrderChannelWin.o patvOrderTimeWin.o patvPopOrderTimeWin.o patvPopPowOffWin.o patvPopPowOnWin.o patvPopSetTimeWin.o patvPowerOffWin.o patvPowerOnWin.o patvSetTimeWin.o

## 生成库
O_TARGET	=	o_target.o

## 编译规则
include $(WORKROOT)/project/$(PROJECT)/make/project_rule.mk
