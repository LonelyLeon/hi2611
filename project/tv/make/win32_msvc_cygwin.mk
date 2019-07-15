#¹¤¾ßÁ´
MSVCLIBR	= $(MSVC_COMPILE_PATH)/lib
MSVCLINK	= $(MSVC_COMPILE_PATH)/link
MSVCCC 		= $(MSVC_COMPILE_PATH)/cl

INC_PATHS +=	$(CRT_INC_PATH)

CFLAGS		+=	$(patsubst %,-I%,$(INC_PATHS))
CFLAGS		+=	$(patsubst %,-D%,$(MACROS))
CFLAGS		+=	-DWIN32 -D_CONSOLE -D_MBCS -DWIN32_LEAN_AND_MEAN \
							-Od -Gm -EHsc -MTd -W3 -nologo -c -ZI -Zm1000 -Dsnprintf=_snprintf

ifeq ($(G_DEBUG), y)
	CFLAGS	+=	-D_DEBUG
endif

LIB_PATHS += $(PLATFORM_DIR)/board/win32/SDL
LDFLAGS		+= -LIBPATH:$(CRT_LIB_PATH)
LDFLAGS		+= -NOLOGO -DEBUG -SUBSYSTEM:CONSOLE -MACHINE:X86 \
             kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib \
             shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib libSDL.a
LDFLAGS		+= $(patsubst %,-LIBPATH:%,$(LIB_PATHS))

%.o: %.c
	@echo " CC $<"
	@$(MSVCCC) $(CFLAGS) $< -Fo$@ -TC -Fd$@.pdb
	
%.o: %.cpp
	@echo " CC $<"
	@$(MSVCCC) $(CFLAGS) $< -Fo$@ -TP -Fd$@.pdb

%.o: %.asm
	@echo " AS $<"
	@$(MSVCCC) $(CFLAGS) $< -Fo$@ -TC -Fd$@.pdb

$(O_TARGET): $(OBJS) $(SUB_LIBS)
	@echo " AR $@"
	@$(MSVCLIBR) $(OBJS) $(SUB_LIBS) -OUT:$@ -NOLOGO

LIB_FILE	=	lib$(LIB_TARGET).a

$(LIB_TARGET): $(OBJS) $(SUB_LIBS) $(O_TARGET)
	@echo " LIB $@"
	@$(MSVCLIBR) $(OBJS) $(SUB_LIBS) $(O_TARGET) -OUT:$(LIB_FILE) -NOLOGO
	$(MKDIR) $(OUTPUT_DIR)/lib
	$(CP) $(LIB_FILE) $(OUTPUT_DIR)/lib/$(LIB_FILE)
	@chmod 777 $(OUTPUT_DIR)/lib/$(LIB_FILE)

MAIN_OBJ:
	@echo " BUILD main"
	@$(MSVCCC) $(CFLAGS) $(WORKROOT)/main.c -Fo$(OUTPUT_DIR)/lib/main.o -TC -Fdmain.o.pdb
	
$(EXECUTE_TARGET): $(OBJS) $(SUB_LIBS) $(O_TARGET) MAIN_OBJ
	@echo " LD $@"
	@echo "List of libs:"
	@(for i in $(SUB_LIBS); do\
		echo "    $$i";\
	done)
	@$(MSVCLINK) -OUT:$@ $(OUTPUT_DIR)/lib/main.o $(OBJS) $(O_TARGET) $(SUB_LIBS) $(LDFLAGS)
	$(MKDIR) $(OUTPUT_DIR)/bin
	$(CP) $@ $(OUTPUT_DIR)/bin/$@.exe
	@chmod 777 $(OUTPUT_DIR)/bin/$@.exe
	
ARCH_CLEAN	=	$(RM) *.pdb *.idb $(LIB_FILE) *.ilk
