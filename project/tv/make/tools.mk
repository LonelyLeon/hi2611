#工具链
CC			=	gcc
CPP			=	cpp
ASM			=	as
LIB			=	ar cru
LINK		=	ld
FROMELF		=	objcopy
DUMP		=	objdump -d -h -S
AX			=	ar x

RM			= 	@rm -rvf
MKDIR		= 	@mkdir -vp
CP			= 	@cp -av
PLATFORM_DIR	=	$(WORKROOT)/platform
INC_PATHS	+= $(PLATFORM_DIR)/include

CFLAGS		+= $(patsubst %,-I%,$(INC_PATHS))
CFLAGS		+= $(patsubst %,-D%,$(MACROS))

CPPFLAGS	+= $(patsubst %,-I%,$(INC_PATHS))
CPPFLAGS	+= $(patsubst %,-D%,$(MACROS))

ifeq ($(G_PROJECT_DEBUG), y)
	CFLAGS	+= -D_DEBUG
	CFLAGS	+= -g -O0 -ffreestanding
else
	CFLAGS	+= -DNDEBUG -O2
endif

CFLAGS		+= -std=c9x -Wall -Wno-unused-variable -Wno-unused-but-set-variable -fsigned-char

AFLAGS		+= -xassembler-with-cpp -D__ASSEMBLY__

LDFLAGS		+= 

##公共规则
all: subdirs $(O_TARGET) $(LIB_TARGET) $(EXECUTE_TARGET)

clean:
	$(SPECIAL_CLEAN)
	$(ARCH_CLEAN)
	@$(RM) $(O_TARGET) $(OBJS) $(LIB_TARGET) $(EXT_OBJS) $(EXECUTE_TARGET) *.d *.dpp *.exe
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

%.o: %.c
	@echo " HOSTCC $<"
	@$(CC) $(CFLAGS) -c $< -o $@ -MD

%.o: %.cpp
	@echo " HOSTCC $<"
	@$(CC) $(CFLAGS) -c $< -o $@ -MD
	
%.o: %.s
	@echo " HOSTAS $<"
	@$(CC) $(CFLAGS) $(AFLAGS) -c $< -o $@ -MD

$(O_TARGET): $(OBJS) $(SUB_LIBS)
	@echo " HOSTAR $@"
ifeq (x$(SUB_LIBS), x)
	@$(LINK) -r -o $@ $(OBJS)
else
	$(MKDIR) .objs
	@cd .objs
	@$(foreach(i, SUB_LIBS, \
		$(AX) ../$(i))
	@cd ..
	@$(LINK) -r -o $@ $(OBJS) ./.objs/*.o
	$(RM) .objs
endif

$(LIB_TARGET): $(OBJS) $(SUB_LIBS) $(O_TARGET)
	@echo " HOSTLIB $@"
ifeq (x$(SUB_LIBS), x)
	@$(LIB) $@ $(OBJS) $(O_TARGET)
else
	$(MKDIR) .objs
	@cd .objs
	@$(foreach(i, SUB_LIBS, \
		$(AX) ../$(i))
	@cd ..
	@$(LIB) $@ $(OBJS) $(O_TARGET) ./.objs/*.o
	$(RM) .objs
endif

$(EXECUTE_TARGET): $(OBJS) $(O_TARGET) $(SUB_LIBS)
	@echo " HOSTLD $@"
	@$(CC) -o $@ $(OBJS) $(O_TARGET) $(SUB_LIBS) $(LDFLAGS)
	$(MKDIR) $(OUTPUT_DIR)/bin
	$(CP) $@ $(OUTPUT_DIR)/bin
	
