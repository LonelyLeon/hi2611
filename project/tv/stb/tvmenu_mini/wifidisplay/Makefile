#
##  Makefile
#
include $(PROJECT_CONFIG)

## 子目录
SUBDIRS	=

## 目标文件
OBJS	+= $(foreach f,$(SUBDIRS),$(f)/o_target.o)
OBJS	+=  patvZhilianTvWin.o patvwifisetting.o patvTextInputWin.o  patvWifiDetailInfo.o patvZhilianMainMenu.o #patvZhilianMenuWin.o


## 生成库
O_TARGET	=	o_target.o

## 编译规则
include $(WORKROOT)/project/$(PROJECT)/make/project_rule.mk
