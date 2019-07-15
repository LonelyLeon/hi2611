#
##  Makefile
#
include $(PROJECT_CONFIG)

## 子目录
SUBDIRS	= 

## 目标文件
OBJS	+= $(foreach f,$(SUBDIRS),$(f)/o_target.o)
OBJS	+= swap_u32.o

EXECUTE_TARGET	= swap_u32

## 编译规则
include $(WORKROOT)/project/$(PROJECT)/make/tools.mk
