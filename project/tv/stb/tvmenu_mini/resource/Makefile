#
##  Makefile
#
include $(PROJECT_CONFIG)

## 子目录
SUBDIRS	=

## 目标文件
OBJS	+=	$(foreach f,$(SUBDIRS),$(f)/o_target.o)
OBJS	+=	atvFormat.o atvImageResource.o  atvpalletes.o atvlanresource.o atvFreeShape.o atvComBineImageResource.o
OBJS	+=	patvGuiResource.o

## 生成目标
O_TARGET	=	o_target.o

## 编译规则
include $(WORKROOT)/project/$(PROJECT)/make/project_rule.mk