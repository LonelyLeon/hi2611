#
##  Makefile
#
include $(PROJECT_CONFIG)

## 子目录
SUBDIRS	= file2c LZSS SetFileData MkFile swap_u32 SetFileTime GetFileData

## 目标文件
OBJS	+= $(foreach f,$(SUBDIRS),$(f)/o_target.o)
OBJS	+= 

## 编译规则
include $(WORKROOT)/project/$(PROJECT)/make/tools.mk
