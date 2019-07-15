#
##  引用的库文件
#

#################################
##           平台库            ##
#################################
PLATFORM_LIB	=	$(OUTPUT_DIR)/lib/libplatform.a
ifneq ($(G_ARCH), pcemu)
ifneq ($(G_CA_SUPPORT_COS), y)
        PLATFORM_LIB	+=	$(OUTPUT_DIR)/lib/libapi_audio.a  
endif
endif
#################################
##           广告库            ##
#################################
ifeq ($(G_AD_SUPPORT_HIV1), y)
		AD_LIB	=	$(OUTPUT_DIR)/lib/libhiadhaierv1.a
endif

ifeq ($(G_AD_SUPPORT_HIV2), y)
		AD_LIB	=	$(OUTPUT_DIR)/lib/libhiadhaierv2.a
endif

ifeq ($(G_TV_PEOJECT_TOUYY), y)
		AD_LIB	+=	$(OUTPUT_DIR)/lib/lib8786.a
endif

#################################
##           stb库             ##
#################################
STB_LIB				=	$(OUTPUT_DIR)/lib/libstb.a

#################################
##       GUI相关支持库         ##
#################################
ifeq ($(G_SYSTEM), linux)
	LINUX_LIB			+=	-lz -lfreetype -lpng -ljpeg -lpthread -lm -ldbus-1 -ldl
else
	ifeq ($(G_GUI_SUPPORT_FREETYPE), y)
		FREETYPE_LIB	=	$(OUTPUT_DIR)/lib/libfreetype.a
		G_SUPPORT_ZLIB	=	y
	else
		FREETYPE_LIB	=	$(OUTPUT_DIR)/lib/libfreetype_fake.a	
	endif
	
	ifeq ($(G_GUI_SUPPORT_PNG), y)
		PNG_LIB	=	$(OUTPUT_DIR)/lib/libpng.a
		G_SUPPORT_ZLIB	=	y
	else
		PNG_LIB	=	$(OUTPUT_DIR)/lib/libpng_fake.a
	endif
	
	ifeq ($(G_GUI_SUPPORT_JPEG), y)
		JPEG_LIB	=	$(OUTPUT_DIR)/lib/libjpeg.a
	else
		JPEG_LIB	=	$(OUTPUT_DIR)/lib/libjpeg_fake.a
	endif

	ifeq ($(G_SUPPORT_ZLIB), y)
		ZLIB_LIB = $(OUTPUT_DIR)/lib/libz.a
	endif
endif


#################################
##            SPU库             ##
#################################
ifneq ($(G_CA_SUPPORT_ABVCA_UNITY), y)
    #ifneq ($(G_ARCH), pcemu)
        SPU_LIB	=	$(OUTPUT_DIR)/lib/libspu.a
    #endif
endif

#################################
ifeq ($(G_TV_MIRACAST_SOURCE), y)
	STB_LIB += $(OUTPUT_DIR)/lib/libMiraWifi.a $(OUTPUT_DIR)/lib/libACE.a $(OUTPUT_DIR)/lib/libMiraShared.a
endif
ifeq ($(G_TV_DLNA_SOURCE), y)
	STB_LIB += $(OUTPUT_DIR)/lib/libhidlna.a
endif
#################################
SUB_LIBS	+=	$(ZLIB_LIB) \
							$(FREETYPE_LIB) \
							$(PNG_LIB) \
							$(JPEG_LIB) \
							$(CA_LIB) \
							$(PLATFORM_LIB) \
							$(STB_LIB)\
							$(AD_LIB)

ifeq ($(G_MEDIA_SUPPORT_NEW_FFMPEG), y)
LINUX_LIB	+=-lffplay

ifneq ($(BUILD_FFMPEG_STATIC), y)
LINUX_LIB	+=-lavcodec
LINUX_LIB	+=-lavformat
LINUX_LIB	+=-lavutil
endif

ifeq ($(G_TV_SUPPORT_IPTV), y)

htk.dir			:= $(HI_HTK_PATH)

cflags-y			+= -I$(htk.dir)/include
cflags-y			+= -I$(htk.dir)
ldflags-y			+= -L$(htk.dir) -lhtk

pkgs-y				+= libsoup-2.4
pkgs-y				+= pixman-1
pkgs-y				+= json-glib-1.0
pkgs-y				+= directfb

cflags-y			+= $(shell pkg-config --cflags --libs $(pkgs-y))

LINUX_LIB			+= $(cflags-y) $(ldflags-y) $(OUTPUT_DIR)/lib/iptv_v4_1.a
endif

ifeq ($(G_TV_SUPPORT_AIRPLAY), y)
SUB_LIBS	+=	$(OUTPUT_DIR)/lib/libhiairplay.a
LINUX_LIB	+=-lbjairplay -ldns_sd  -lssl -lcrypto
endif


endif



