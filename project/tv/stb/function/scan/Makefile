
#
##  Makefile
#
include $(PROJECT_CONFIG)

## 子目�?
SUBDIRS	= 

## 目标文件
OBJS	+= $(foreach f,$(SUBDIRS),$(f)/o_target.o)
OBJS	+= pScanSort.o pScanOp_dvbc.o pScanOp_dvbt.o pScanOp_atv.o pAtvManualSearch.o
OBJS	+= pScanOp_dvbs.o
## 生成�?
O_TARGET	=	o_target.o

## 编译规则
include $(WORKROOT)/project/$(PROJECT)/make/project_rule.mk