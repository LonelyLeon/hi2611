#
##  Makefile
#
include $(PROJECT_CONFIG)

## 子目录
SUBDIRS	= 

## 目标文件
OBJS	+= airplay_test.o

## 生成库
O_TARGET	=	o_target.o

## 编译规则
include $(WORKROOT)/project/$(PROJECT)/make/project_rule.mk

all:
	$(MKDIR) $(OUTPUT_DIR)/lib
	$(CP) sdk/*.so $(OUTPUT_DIR)/lib/
	$(MKDIR) $(OUTPUT_DIR)/bin
	$(CP) sdk/mdnsd $(OUTPUT_DIR)/bin
	$(CP) hiairplay/*.a $(OUTPUT_DIR)/lib/
	$(CP) hiairplay/*.so $(OUTPUT_DIR)/lib/