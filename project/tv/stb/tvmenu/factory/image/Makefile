#
##  Makefile
#
include $(PROJECT_CONFIG)

## 子目录
SUBDIRS	= 

## 目标文件
OBJS	+= $(foreach f,$(SUBDIRS),$(f)/o_target.o)
OBJS	+= patvImageSetting.o patvWbAdjust.o patvPqNonlilnear.o patvpictureset.o patvAseSet.o patvBlDimSet.o patvCeSet.o patvGammaSet.o patvDifmSet.o\
			patvFtcSet.o patvNrSet.o patvDeSet.o patvIcmSet.o patvCombSet.o patvCompSet.o
  
## 生成库
O_TARGET	=	o_target.o

## 编译规则
include $(WORKROOT)/project/$(PROJECT)/make/project_rule.mk
