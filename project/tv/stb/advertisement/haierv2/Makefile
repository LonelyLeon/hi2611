#
##  Makefile
#
include $(PROJECT_CONFIG)

## 子目录
SUBDIRS	= 

ifeq ($(G_SYSTEM), win32)
	INC_PATHS	+=	$(WORKROOT)/platform/board/win32 $(WORKROOT)/platform/board/win32/SDL
endif

## 目标文件
OBJS	+= $(foreach f,$(SUBDIRS),$(f)/o_target.o)
OBJS	+= haier_v2_adporting.o  haier_v2_api.o

## 生成库
LIB_TARGET	=	hiadhaierv2

## 编译规则
include $(WORKROOT)/project/$(PROJECT)/make/project_rule.mk
