#
##  π§æﬂ¡¥≈‰÷√
#
CC			=	gcc -m32
ASM			=	as -m32
AR			=	ar crs
LD		=	ld -m elf_i386
ARX		=	ar x
RANLIB		=	ranlib

CFLAGS	+=	$(patsubst %,-I%,$(INC_PATHS))
CFLAGS	+=	$(patsubst %,-D%,$(MACROS))

ifeq ($(G_PLATFORM_DEBUG), y)
	CFLAGS	+=	-g -O0
else
	CFLAGS	+=	-O2
endif

CFLAGS	+=	-Wall -fsigned-char -std=gnu99
ifneq ($(CC_DISABLE_WERROR), y)
	CFLAGS	+=  -Werror
endif

%.o: %.c
	@echo " CC $<"
	@$(CC) $(CFLAGS) -c $< -o $@ -MD
	
%.o: %.cpp
	@echo " C++ $<"
	@$(CC) $(CFLAGS) -c $< -o $@ -MD
		
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

ARCH_CLEAN	=	$(RM) $(LIB_FILE) $(SHARED_LIB_FILE)
