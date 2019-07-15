
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
OBJS	+= pFile_Scan.o

ifeq ($(G_MUTIMEDIA_NOCATALOG),y)
	OBJS	+= TvMediaFileScan.o pMediaScanTask.o 
endif	

## 生成�?
O_TARGET	=	o_target.o

## 编译规则
include $(WORKROOT)/project/$(PROJECT)/make/project_rule.mk