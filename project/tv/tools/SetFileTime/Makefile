#
##  Makefile
#
include $(PROJECT_CONFIG)

## 子目录
SUBDIRS	= 

## 目标文件
OBJS	+= $(foreach f,$(SUBDIRS),$(f)/o_target.o)
OBJS	+= SetFileTime.o

EXECUTE_TARGET	= SetFileTime

## 编译规则
include $(WORKROOT)/project/$(PROJECT)/make/tools.mk
