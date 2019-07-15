#
##  编译规则配置
#

PLATFORM_DIR	=	$(WORKROOT)/platform

RM	= @rm -rvf
MKDIR	= @mkdir -vp
CP	= @cp -av

INC_PATHS	+=	$(PLATFORM_DIR)/include ./

#####################################宏配置#######################################
##GAMATEST选项
ifeq ($(G_PLATFORM_GAMATEST), y)
	MACROS	+=	D_GAMA_TEST=1
endif
##DEBUG选项
ifeq ($(G_PLATFORM_DEBUG), y)
	MACROS	+=	D_DEBUG=1
endif

MACROS	+=	D_PLATFORM_PRINT_BUF_SIZE=$(G_PLATFORM_PRINT_BUF_SIZE)

include $(PLATFORM_DIR)/make/platform_cfg.mk

###################################### 编译规则################################################
ALL_DEF: all
-include  *.d

##选择工具链
ifeq ($(G_DEVTOOLS), msvc)
	include $(PLATFORM_DIR)/make/win32_msvc_cygwin.mk
endif

ifeq ($(G_DEVTOOLS), ghs_cyg)
	include $(PLATFORM_DIR)/make/rtos_ghs_cygwin.mk
endif

ifeq ($(G_DEVTOOLS), mipsisa32_gcc_cyg)
	include $(PLATFORM_DIR)/make/rtos_mipsisa32gcc_cygwin.mk
endif

ifeq ($(G_DEVTOOLS), mipsgnu_gcc_linux)
	include $(PLATFORM_DIR)/make/linux_mipsgnugcc_i386.mk
endif

ifeq ($(G_DEVTOOLS), i386_gcc_linux)
	include $(PLATFORM_DIR)/make/linux_gcc_i386.mk
endif

##公共规则
all: subdirs $(O_TARGET) $(LIB_TARGET)



clean:$(USER_CLEAN_OBJ)
	$(ARCH_CLEAN)
	$(SUB_CLEAN)
	@$(RM) $(O_TARGET) $(OBJS) $(LIB_TARGET) $(EXT_OBJS) *.d *.dpp
	@(for i in $(SUBDIRS); do\
		$(MAKE) -C $$i clean;\
		rc=$$?;\
		if [ $$rc -ne 0 ]; then exit $$rc; fi;\
	done)

subdirs:
	@(for i in $(SUBDIRS); do\
		make -C $$i;\
		rc=$$?;\
		if [ $$rc -ne 0 ]; then exit $$rc; fi;\
	done)

.PHONY: clean subdirs
