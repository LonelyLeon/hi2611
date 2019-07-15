#
##  һЩ���Թ��õı����������
#

########Ŀ�����ϵͳ����
##LinuxĿ��ϵͳ
ifeq ($(G_SYSTEM), linux)
	MACROS	+=	D_SYSTEM_LINUX=1
endif

##WIN32Ŀ��ϵͳ
ifeq ($(G_SYSTEM), win32)
	MACROS	+=	D_SYSTEM_WIN32=1
endif

##HROSĿ��ϵͳ
ifeq ($(G_SYSTEM), hros)
	MACROS	+=	D_SYSTEM_HROS=1
endif

########Ŀ��ƽ̨����
##PC����ƽ̨
ifeq ($(G_ARCH), pcemu)
	MACROS	+=	D_ARCH_PCEMU=1
	MACROS	+=	D_ARCH_TYPE_HD=1
endif

##Hi2309ƽ̨
ifeq ($(G_ARCH), hi2309)
	MACROS	+=	D_ARCH_HI2309=1
endif

##Hi2830ƽ̨  
ifeq ($(G_ARCH), hi2830)
	MACROS	+=	D_ARCH_HI2830=1
	MACROS	+=	D_ARCH_TYPE_HD=1
endif

##Hi2830eƽ̨  
ifeq ($(G_ARCH), hi2830e)
	MACROS	+=	D_ARCH_HI2830e=1
	MACROS	+=	D_ARCH_TYPE_HD=1
endif

##Hi2830nƽ̨  
ifeq ($(G_ARCH), hi2830n)
	MACROS	+=	D_ARCH_HI2830n=1
	MACROS	+=	D_ARCH_TYPE_HD=1
endif

##Hi2610dƽ̨  
ifeq ($(G_ARCH), hi2610d)
	MACROS	+=	D_ARCH_HI2610D=1
	MACROS	+=	D_ARCH_TYPE_HD=1
endif

##Hi2610eƽ̨  
ifeq ($(G_ARCH), hi2610e)
	MACROS	+=	D_ARCH_HI2610E=1
	MACROS	+=	D_ARCH_TYPE_HD=1
endif

########����������������
##΢�������
ifeq ($(G_DEVTOOLS), msvc)
	MACROS	+=	D_DEVTOOLS_MSVC=1
endif

##GREEN HILL������, cygwin����
ifeq ($(G_DEVTOOLS), ghs_cyg)
	MACROS	+=	D_DEVTOOLS_GHS=1
endif

##mipsisa32-elf-gcc������, cygwin����
ifeq ($(G_DEVTOOLS), mipsisa32_gcc_cyg)
	MACROS	+=	D_DEVTOOLS_MIPSISA32_GCC=1
endif

##mips-linux-gnu-gcc������, linux����
ifeq ($(G_DEVTOOLS), mipsgnu_gcc_linux)
	MACROS	+=	D_DEVTOOLS_MIPSGNU_GCC=1
endif

##i386-gcc������, linux����
ifeq ($(G_DEVTOOLS), i386_gcc_linux)
	MACROS	+=	D_DEVTOOLS_I386_GCC=1
endif

########Ŀ���β��
ifeq ($(G_ENDIAN), big)
	MACROS	+=	D_BIG_ENDIAN=1
else
	MACROS	+=	D_LITTLE_ENDIAN=1
endif

##e2p��С����
MACROS	+=	D_EEPROM_RECOMMEND_SIZE=$(G_EEPROM_RECOMMEND_SIZE)

#��ʱ��ӡ֧��(y/n)
ifeq ($(G_DEBUG_TIME_RECORD), y)
	MACROS	+=	D_DEBUG_TIME_RECORD=1
endif

########һЩaux����
########���ݿ�����######
MACROS		+= D_DB_SERVICE_NAME_LEN=32		#��Ŀ���Ƴ��ȣ����ֽ�Ϊ��λ
MACROS		+= D_MAX_NV_PART_DATA_CNT=96	#һ�����ݷ����д��ڵı������ݿ�������Ŀ

#���ݿ��Ŀ��ϢԤ����С(�ֽ���)
MACROS		+= D_SRV_RESERVE_SIZE=$(DB_SRV_RESERVE_SIZE)

#���ݿ��Ŀ��Ϣ���Ƿ�֧�ֵ�4·��Ƶ(y/n)
ifeq ($(DB_SRV_SUPPORT_4AUDIO), y)
	MACROS	+=	D_DB_SRV_SUPPORT_4AUDIO=1
endif

#���ݿ�TS Ԥ����С(�ֽ���)
MACROS		+= D_TS_RESERVE_SIZE=$(DB_TS_RESERVE_SIZE)

MACROS		+= D_DB_SATE_NAME_LEN=16		#�������Ƴ��ȣ����ֽ�Ϊ��λ
MACROS		+= D_DB_NETWORK_NAME_LEN=32		#�������Ƴ��ȣ����ֽ�Ϊ��λ
MACROS		+= D_DB_EVENT_DESC_LEN=256
MACROS		+= D_DB_BOUQUET_NAME_LEN=32		#ҵ��Ⱥ���Ƴ��ȣ����ֽ�Ϊ��λ
MACROS		+= D_DB_EVENT_NAME_LEN=50		#ԤԼ��Ŀ���Ƴ��ȣ����ֽ�Ϊ��λ

#�Ƿ�֧��lwip, ֻ��hros��win32����֧��(y/n)
ifeq ($(G_AUX_SUPPORT_LWIP), y)
	MACROS	+=	D_AUX_SUPPORT_LWIP=1
endif

########һЩGUI������
########��ͼ�豸ѡ��
ifeq ($(G_GRAPH_DEVICE), sdl)
	MACROS	+=	D_GRAPH_DEV_SDL=1
endif

ifeq ($(G_GRAPH_DEVICE), hi2309)
	MACROS	+=	D_GRAPH_DEV_HI2309=1
endif

ifeq ($(G_GRAPH_DEVICE), hi2830)
	MACROS	+=	D_GRAPH_DEV_HI2830=1
endif

ifeq ($(G_GRAPH_DEVICE), hi2610d)
	MACROS	+=	D_GRAPH_DEV_HI2610D=1
endif


ifeq ($(G_GRAPH_DEVICE), hi2610e)
	MACROS	+=	D_GRAPH_DEV_HI2610E=1
endif

ifeq ($(G_GRAPH_DEVICE), software)
	MACROS	+=	D_GRAPH_DEV_SOFTWARE=1
endif

##֧�ֻ�������ֱ��
ifeq ($(G_GUI_SUPPORT_LINE), y)
	MACROS	+=	D_GUI_SUPPORT_LINE=1
endif

##֧�ֻ�����
ifeq ($(G_GUI_SUPPORT_ARC), y)
	MACROS	+=	D_GUI_SUPPORT_ARC=1
endif

##֧�ֻ��������
ifeq ($(G_GUI_SUPPORT_FILL_ARC), y)
	MACROS	+=	D_GUI_SUPPORT_FILL_ARC=1
endif

##֧�ֻ���Բ
ifeq ($(G_GUI_SUPPORT_ELLIPSE), y)
	MACROS	+=	D_GUI_SUPPORT_ELLIPSE=1
endif

##֧�ֻ������Բ
ifeq ($(G_GUI_SUPPORT_FILL_ELLIPSE), y)
	MACROS	+=	D_GUI_SUPPORT_FILL_ELLIPSE=1
endif

##֧�ֻ������
ifeq ($(G_GUI_SUPPORT_POLY), y)
	MACROS	+=	D_GUI_SUPPORT_POLY=1
endif

##֧�ֻ��������
ifeq ($(G_GUI_SUPPORT_FILL_POLY), y)
	MACROS	+=	D_GUI_SUPPORT_FILL_POLY=1
endif

##�ɰ�װ���ֿ�������
MACROS	+=	D_GUI_SUPPORT_FONT_CNT=$(G_GUI_SUPPORT_FONT_CNT)

##���PDMA֧��(y/n)
ifeq ($(G_PDMA_BIGENDIAN_PATCH), y)
	MACROS	+=	D_PDMA_BIGENDIAN_PATCH=1
endif

##freetype��ģ����(y/n)
ifeq ($(G_GUI_FREETYPE_CACHE_IMAGE_MODEL), y)
	MACROS	+=	D_GUI_FREETYPE_CACHE_IMAGE_MODEL=1
endif

##����봥����֧��(y/n)
ifeq ($(G_GUI_SUPPORT_MOUSE_TOUCHSCREEN), y)
	MACROS	+=	D_GUI_SUPPORT_MOUSE_TOUCHSCREEN=1
endif

##֧�ֹ������ǰ汾����
ifeq ($(SUPPORT_DIFFER_VER_CONTROL), y)
	MACROS	+=	D_MONITOR_SUPPORT_DIFFER_VER_CONTROL=1
endif


##֧�ֲ��ɼ���ϵͳ�;�����ʾ�����˻����峧��ר�ã���������¹رա�

ifeq ($(HI_P_MINITV_SYSTEM_FILE_SHOW_EN), y)
	MACROS	+=	D_MINITV_SYSTEM_FILE_SHOW_EN=1
endif

##############################################
##                                 					##
##		          ����Ƶ�������              ##
## 	   (������Ӧ΢�룬���ٴ���ռ�)     ##
##                                 					##
##############################################
#��Ƶ��ʽ֧��(ALL ���� MPEG2 AC3 AAC MP3 WMA AMR DTS DRA WAV PCM ADPCM INTERPHONE���)
ifdef G_AUDIO_SUPPORT_CODEC
	MACROS	+=	$(patsubst %,D_AUDIO_SUPPORT_CODEC_%,$(G_AUDIO_SUPPORT_CODEC))
else
	MACROS	+=	D_AUDIO_SUPPORT_CODEC_ALL=1
endif

##����ƽ���Ƿ�֧�ָ���
ifeq ($(G_AUDIO_SUPPORT_BALANCE), y)
	MACROS	+=	D_AUDIO_SUPPORT_BALANCE=1
endif

##############################################
##                                 					##
##		          ͼƬ�����������            ##
## 	(����֧�ֵ�ͼƬ��ʽ GIF JPEG PNG BMP)   ##
##                                 					##
##############################################
##֧��ͼ������ʽ(ALL ���� GIF JPEG PNG BMP���)
ifdef G_SUPPORT_IMAGE_TYPE
	MACROS	+=	$(patsubst %,D_SUPPORT_IMAGE_%,$(G_SUPPORT_IMAGE_TYPE))
else
	MACROS	+=	D_SUPPORT_IMAGE_ALL=1
endif

##�Ƿ�ʹ����jpeg����ģ��
ifeq ($(G_SYS_JPEG_NEW), y)
	MACROS	+=	D_JPEG_DEV=1
	ifeq ($(G_SUPPORT_PROGRESSIVE),y)
	 MACROS	+=	D_JPEG_SUPPORT_PROGRESSIVE=1
	endif
endif


##############################################
##                                 					##
##		          CA�����������              ##
## 	   (�����Ŀ��ʹ��ca�����ٴ���ռ�)     ##
##                                 					##
##############################################
#ϵͳ�Ƿ�֧��ca����(y/n)
ifdef G_SYS_SUPPORT_CA
	ifeq ($(G_SYS_SUPPORT_CA), y)
		MACROS	+=	D_SYS_SUPPORT_CA=1
		ifdef G_SYS_SUPPORT_CA_TYPE
			MACROS	+=	D_SYS_SUPPORT_CA_TYPE=$(G_SYS_SUPPORT_CA_TYPE)
		endif
	endif
else
	MACROS	+=	D_SYS_SUPPORT_CA=1
	ifdef G_SYS_SUPPORT_CA_TYPE
		MACROS	+=	D_SYS_SUPPORT_CA_TYPE=$(G_SYS_SUPPORT_CA_TYPE)
	endif
endif

#�Ƿ�֧��NDSICAM (y/n)
ifeq ($(G_SUPPORT_NDS_ICAM), y)
		MACROS	+=	D_SUPPORT_NDS_ICAM=1
endif	
	
#�Ƿ�֧��NDSCAHDI���� (y/n)
ifeq ($(G_SUPPORT_NDSCAHDI), y)
	MACROS	+=	D_SUPPORT_NDSCAHDI=1
	ifeq ($(G_NDSCAHDI_VERIFIER), y)
		MACROS	+=	D_NDSCAHDI_VERIFIER=1
	endif
endif

##############################################
##                                 					##
##		     ��дOTP�����������              ##
##   (ĳЩ��Ŀ��ʹ�ô����ã����ٴ���ռ�)   ##
##                                 					##
##############################################
#ϵͳ�Ƿ�֧�ֳ�����дotp����(y/n)
ifdef G_SYS_SUPPORT_OTP
	ifeq ($(G_SYS_SUPPORT_OTP), y)
		MACROS	+=	D_SYS_SUPPORT_OTP=1
	endif
else
##  	MACROS	+=	D_SYS_SUPPORT_OTP=1
endif


##############################################
##                                 					##
##		   ����ɽ����ԿOTP����д����          ##
##    ��G_SYS_SUPPORT_OTP = yʱ�����       ##
##    ��Ҫ��д-Nsd��Կʱ���򿪴˺궨��      ##
##############################################
#�Ƿ���д����-Nsd��Կ����(y/n)
ifdef G_SYS_SUPPORT_OTP_ABV_NSD
	ifeq ($(G_SYS_SUPPORT_OTP_ABV_NSD), y)
		MACROS	+=	D_SYS_SUPPORT_OTP_ABV_NSD=1
	endif
endif

##############################################
##                                 					##
##		       �ַ�����ת���������           ##
## 	  (�������ã�����ת��ӳ�����ռ�ռ�)    ##
##                                 					##
##############################################

#֧�������ַ�����ת��(y/n)
ifdef G_CC_SUPPORT_CHINESE
	ifeq ($(G_CC_SUPPORT_CHINESE), y)
		MACROS	+=	D_CC_SUPPORT_CHINESE=1
	endif
else
	MACROS	+=	D_CC_SUPPORT_CHINESE=1
endif

#����GBK/GB2312�ַ�����ת��(GB2312/GBK)
ifeq ($(G_CC_SUPPORT_GB2312_GBK), GBK)
	MACROS	+=	D_CC_SUPPORT_GBK=1
else
	MACROS	+=	D_CC_SUPPORT_GB2312=1
endif

#֧������big5ת��GBK/GB2312�ַ�����ת��(y/n)
ifdef G_CC_SUPPORT_CHINESE
ifeq ($(G_CC_SUPPORT_BIG5), y)
	MACROS	+=	D_CC_SUPPORT_BIG5=1
endif
else
	MACROS	+=	D_CC_SUPPORT_BIG5=1
endif

#####################################
##                                 ##
##       ��PLL1Ƶ������        	   ##
##                                 ##
#####################################
#�Ƿ�ı�PLL1Ƶ��(y/n)
ifeq ($(G_SWITCH_PLL1_FREQ_OPEN), y)
MACROS		+= D_SWITCH_PLL1_FREQ_OPEN=$(G_SWITCH_PLL1_FREQ_OPEN)
endif

ifdef G_MEDIA_SUPPORT_OLD_FFMPEG
ifeq ($(G_MEDIA_SUPPORT_OLD_FFMPEG), y)
MACROS		+= D_MEDIA_SUPPORT_OLD_FFMPEG
endif
else
	MACROS		+= D_MEDIA_SUPPORT_OLD_FFMPEG
endif

ifeq ($(G_MEDIA_SUPPORT_NEW_FFMPEG), y)
MACROS		+= D_MEDIA_SUPPORT_NEW_FFMPEG

NEW_FFMPEG_DIR:=$(WORKROOT)/platform/common_app/media/ffmpeg-3.4
endif

ifeq ($(G_MEDIA_DEBUG), y)
MACROS		+= D_MEDIA_DEBUG
endif

ifeq ($(G_MEDIA_SUPPORT_NEW_FFMPEG), y)
ifeq ($(G_ONLY_USE_NEW_FFMPEG), y)
MACROS		+= D_ONLY_USE_NEW_FFMPEG
endif
endif


#####################################
##                                 ##
##    	  �Ƿ�֧��liulink Client    ##
##                                 ##
#####################################


ifeq ($(G_TV_LIULINK_SOURCE), y)
	MACROS	+=	D_TV_LIULINK_SOURCE=1
	MACROS	+=	D_PLATFORM_PRINT_BUF_SIZE=$(G_PLATFORM_PRINT_BUF_SIZE)
endif

ifeq ($(G_TV_LIULINK_SOURCE), y)
	ifeq ($(G_TV_LIULINK_SOURCE_DYNAMIC), y)
		MACROS	+=	D_TV_LIULINK_SOURCE_DYNAMIC=1
	endif
endif

#### dlna
ifeq ($(G_HI_DLNA_LIB), y)
	MACROS	+=	D_HI_DLNA_LIB=1
endif

#### miracast
ifeq ($(G_HAIER_MIRACAST), y)
	MACROS	+=	D_HAIER_MIRACAST=1
endif
