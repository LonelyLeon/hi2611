
#
##  Makefile
#
include $(PROJECT_CONFIG)

## 子目�?
SUBDIRS	= 

ifeq ($(G_SYSTEM), win32)
	INC_PATHS	+=	$(WORKROOT)/platform/board/win32 $(WORKROOT)/platform/board/win32/SDL
endif

## 目标文件
OBJS	+= $(foreach f,$(SUBDIRS),$(f)/o_target.o)
OBJS	+= pCustomConfig.o

## 生成�?
O_TARGET	=	o_target.o

SOURCES	=	DEFAULT_SW_bin.c \
		P_BOARD_HIC_2610E_DTMB_DVBC_bin.c

FILE2C = $(WORKROOT)/output/bin/file2c

all: $(SOURCES) $(O_TARGET)

DEFAULT_SW_bin.c: SW_DEFAULT.bin
	$(FILE2C) -c $< DEFAULT_SW_BIN > $@

P_BOARD_HIC_2610E_DTMB_DVBC_bin.c: HW_BOARD_HIC_2610E_DTMB_DVBC.bin
	$(FILE2C) -c $< DEFAULT_HW_BIN > $@

SPECIAL_CLEAN	=	rm -rvf *_bin.c

## 编译规则
include $(WORKROOT)/project/$(PROJECT)/make/project_rule.mk

all:
	$(MKDIR) $(OUTPUT_DIR)/bin
	$(CP) *.bin $(OUTPUT_DIR)/bin
