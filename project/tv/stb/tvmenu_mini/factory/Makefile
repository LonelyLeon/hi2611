#
##  Makefile
#
include $(PROJECT_CONFIG)

## 子目录
SUBDIRS	= sound general scan test

ifeq ($(G_TV_FC_IMAGE_SOURCE), y)
	SUBDIRS	+= image_new
else
	SUBDIRS	+= image
endif

## 目标文件
OBJS	+= $(foreach f,$(SUBDIRS),$(f)/o_target.o)
OBJS	+= patvFactorySetting.o patvEmcSetting.o patvSoftwareUpdate.o patvTimerReceive.o pAtvDvbcManualScanWindow.o pAtvDtmbManualScanWindow.o #patvSwInformatiion.o 
OBJS	+= patvProgResetWin.o patvfcSelBoxWin.o

ifeq ($(G_TV_FC_IMAGE_SOURCE), y)
	OBJS	+= 
else
	OBJS	+= patvAdcAdjust.o
endif
## 生成库
O_TARGET	=	o_target.o

## 编译规则
include $(WORKROOT)/project/$(PROJECT)/make/project_rule.mk

all:
	$(OUTPUT_DIR)/bin/SetFileTime -f patvFactorySetting.c -m 0
	$(OUTPUT_DIR)/bin/SetFileTime -f patvSoftwareUpdate.c -m 0