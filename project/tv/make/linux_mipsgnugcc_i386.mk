#
##  π§æﬂ¡¥≈‰÷√
#
CC			=	$(CROSS_COMPILE)gcc
CXX			=	$(CROSS_COMPILE)c++
ASM			=	$(CROSS_COMPILE)as
AR			=	$(CROSS_COMPILE)ar crs
LD			=	$(CROSS_COMPILE)ld -EL
ARX			=	$(CROSS_COMPILE)ar x
RANLIB	=	$(CROSS_COMPILE)ranlib
STRIP		=	$(CROSS_COMPILE)strip

CFLAGS	+=	$(patsubst %,-I%,$(INC_PATHS))
CFLAGS	+=	$(patsubst %,-D%,$(MACROS))

ifeq ($(G_PLATFORM_DEBUG), y)
	CFLAGS	+=	-g
endif

ifneq ($(OPTIMIZE_LEVEL), 0)
	CFLAGS	+=	-fomit-frame-pointer
endif

CFLAGS	+=	-O$(OPTIMIZE_LEVEL) -EL -G0 -march=mips32r2 -msoft-float -fPIC -Wall -Wno-unused-variable -Wno-unused-but-set-variable -fsigned-char -std=gnu99 \
						-mno-check-zero-division -mno-fp-exceptions
CXXFLAGS	+=	-O$(OPTIMIZE_LEVEL) -EL -G0 -march=mips32r2 -msoft-float -Wall -Wno-unused-variable -Wno-unused-but-set-variable -fsigned-char
						

%.o: %.c
	@echo " CC $<"
	@$(CC) $(CFLAGS) -c $< -o $@ -MD
	
%.o: %.cpp
	@echo " C++ $<"
	@$(CXX) $(CFLAGS) -c $< -o $@ -MD
		
$(O_TARGET): $(OBJS) $(SUB_LIBS)
	@echo " AR $@"
	@if [ -z "$(SUB_LIBS)" ]; then\
		$(LD) -r -o $@ $(OBJS);\
	else\
		$(MKDIR) .objs;\
		cd .objs;\
		for f in $(SUB_LIBS); do $(ARX) ../$$f; done; cd ..;\
		$(LD) -r -o $@ $(OBJS) .objs/*.o;\
		$(RM) .objs;\
	fi

$(BUILT-IN): $(EXT_OBJS)
	@echo " LD $@"
	@$(LD) -r -o $@ $(EXT_OBJS)

LIB_FILE	=	lib$(LIB_TARGET).a
SHARED_LIB_FILE	=	lib$(LIB_TARGET).so

$(LIB_TARGET): $(OBJS) $(SUB_LIBS) $(O_TARGET)
	@echo " LIB $@"
	@if [ -z "$(SUB_LIBS)" ]; then\
		$(AR) $(LIB_FILE) $(OBJS) $(O_TARGET);\
	else\
		$(MKDIR) .objs;\
		cd .objs;\
		for f in $(SUB_LIBS); do $(ARX) ../$$f; done; cd ..;\
		$(AR) $(LIB_FILE) $(OBJS) $(O_TARGET) .objs/*.o;\
		$(RM) .objs;\
	fi
	@$(RANLIB) $(LIB_FILE)
	@$(CC) $(CFLAGS) -shared $(OBJS) $(O_TARGET) -Wl,--start-group $(SUB_LIBS) -Wl,--end-group -o $(SHARED_LIB_FILE)
	$(MKDIR) $(OUTPUT_DIR)/lib
	$(CP) $(LIB_FILE) $(SHARED_LIB_FILE) $(OUTPUT_DIR)/lib
	@chmod 777 $(OUTPUT_DIR)/lib/$(LIB_FILE) $(OUTPUT_DIR)/lib/$(SHARED_LIB_FILE)

MAIN_OBJ:
	@echo " BUILD main"
	@$(CC) $(CFLAGS) $(WORKROOT)/main.c -o$(OUTPUT_DIR)/lib/main.o -c
	
$(EXECUTE_TARGET): $(OBJS) $(SUB_LIBS) $(O_TARGET) MAIN_OBJ
	@echo " LD $@"
	@echo "List of libs:"
	@(for i in $(SUB_LIBS) $(LINUX_LIB); do\
		echo "    $$i";\
	done)
	@$(CXX) -o $@ $(OUTPUT_DIR)/lib/main.o $(OBJS) $(O_TARGET) -L$(LINUX_SYS_USR_PATH)/lib -L$(OUTPUT_DIR)/lib -Wl,--start-group $(SUB_LIBS) -Wl,--end-group -Wl,--gc-sections $(LINUX_LIB) $(CXXFLAGS)
	$(MKDIR) $(OUTPUT_DIR)/bin
	$(CP) $@ $(OUTPUT_DIR)/bin/$@_unstripped.elf
	@$(STRIP) -g --strip-unneeded $(OUTPUT_DIR)/bin/$@_unstripped.elf -o $(OUTPUT_DIR)/bin/$@.elf
	
ARCH_CLEAN	=	$(RM) $(LIB_FILE) $(SHARED_LIB_FILE)
