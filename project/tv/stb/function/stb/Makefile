
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
OBJS	+= pStbControl.o pEpgControl.o pComboKey.o pStbFunctions.o

ifeq ($(G_TV_LIULINK_SOURCE), y)
INC_PATHS	+=	$(WORKROOT)/project/$(PROJECT)/stb/liulinkclient

OBJS +=$(WORKROOT)/project/$(PROJECT)/stb/liulinkclient/liulinkclient_load.o
endif


## 生成�?
O_TARGET	=	o_target.o

## 编译规则
include $(WORKROOT)/project/$(PROJECT)/make/project_rule.mk