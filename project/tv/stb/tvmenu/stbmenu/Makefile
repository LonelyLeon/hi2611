#
##  Makefile
#
include $(PROJECT_CONFIG)

## 子目录
SUBDIRS	=

## 目标文件
OBJS	+= $(foreach f,$(SUBDIRS),$(f)/o_target.o)
OBJS	+=  patvMainMenu.o pStbAtvMenu.o patvSubMenu.o patvSignalInputShow.o patvSetRegister.o patvCaMainMenu.o pDtmbChanInfoTest.o pDvbcChanInfoTest.o patvModeShow.o

OBJS	+=  patvSignalSelect.o

## 生成库
O_TARGET	=	o_target.o

## 编译规则
include $(WORKROOT)/project/$(PROJECT)/make/project_rule.mk
