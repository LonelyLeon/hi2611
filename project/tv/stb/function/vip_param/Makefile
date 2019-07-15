
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
OBJS	+= pvip_param.o ppanelset.o pvip_backlight.o pcolorset.o ppanel.o pNT35510.o


## 生成�?
O_TARGET	=	o_target.o

## 编译规则
include $(WORKROOT)/project/$(PROJECT)/make/project_rule.mk