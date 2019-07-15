#
##  Makefile
#
include $(PROJECT_CONFIG)

## 子目录
SUBDIRS	=

## 目标文件
OBJS	+= $(foreach f,$(SUBDIRS),$(f)/o_target.o)
OBJS	+= patvPlayerWin.o patvVolume.o patvSetMute.o patvAvSignalSelect.o patvNoSignalWin.o patvPowerOffMsg.o patvEpgWin.o patvSerialShow.o
OBJS	+= patvRadioIconWin.o patvOsdShow.o patvAudioConfig.o
## 生成库
O_TARGET	=	o_target.o

## 编译规则
include $(WORKROOT)/project/$(PROJECT)/make/project_rule.mk
