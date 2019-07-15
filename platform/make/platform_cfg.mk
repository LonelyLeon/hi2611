#
##  一些可以共用的编译规则配置
#

########目标操作系统配置
##Linux目标系统
ifeq ($(G_SYSTEM), linux)
	MACROS	+=	D_SYSTEM_LINUX=1
endif

##WIN32目标系统
ifeq ($(G_SYSTEM), win32)
	MACROS	+=	D_SYSTEM_WIN32=1
endif

##HROS目标系统
ifeq ($(G_SYSTEM), hros)
	MACROS	+=	D_SYSTEM_HROS=1
endif

########目标平台配置
##PC虚拟平台
ifeq ($(G_ARCH), pcemu)
	MACROS	+=	D_ARCH_PCEMU=1
	MACROS	+=	D_ARCH_TYPE_HD=1
endif

##Hi2309平台
ifeq ($(G_ARCH), hi2309)
	MACROS	+=	D_ARCH_HI2309=1
endif

##Hi2830平台  
ifeq ($(G_ARCH), hi2830)
	MACROS	+=	D_ARCH_HI2830=1
	MACROS	+=	D_ARCH_TYPE_HD=1
endif

##Hi2830e平台  
ifeq ($(G_ARCH), hi2830e)
	MACROS	+=	D_ARCH_HI2830e=1
	MACROS	+=	D_ARCH_TYPE_HD=1
endif

##Hi2830n平台  
ifeq ($(G_ARCH), hi2830n)
	MACROS	+=	D_ARCH_HI2830n=1
	MACROS	+=	D_ARCH_TYPE_HD=1
endif

##Hi2610d平台  
ifeq ($(G_ARCH), hi2610d)
	MACROS	+=	D_ARCH_HI2610D=1
	MACROS	+=	D_ARCH_TYPE_HD=1
endif

##Hi2610e平台  
ifeq ($(G_ARCH), hi2610e)
	MACROS	+=	D_ARCH_HI2610E=1
	MACROS	+=	D_ARCH_TYPE_HD=1
endif

########主机开发环境配置
##微软编译器
ifeq ($(G_DEVTOOLS), msvc)
	MACROS	+=	D_DEVTOOLS_MSVC=1
endif

##GREEN HILL编译器, cygwin环境
ifeq ($(G_DEVTOOLS), ghs_cyg)
	MACROS	+=	D_DEVTOOLS_GHS=1
endif

##mipsisa32-elf-gcc编译器, cygwin环境
ifeq ($(G_DEVTOOLS), mipsisa32_gcc_cyg)
	MACROS	+=	D_DEVTOOLS_MIPSISA32_GCC=1
endif

##mips-linux-gnu-gcc编译器, linux环境
ifeq ($(G_DEVTOOLS), mipsgnu_gcc_linux)
	MACROS	+=	D_DEVTOOLS_MIPSGNU_GCC=1
endif

##i386-gcc编译器, linux环境
ifeq ($(G_DEVTOOLS), i386_gcc_linux)
	MACROS	+=	D_DEVTOOLS_I386_GCC=1
endif

########目标机尾端
ifeq ($(G_ENDIAN), big)
	MACROS	+=	D_BIG_ENDIAN=1
else
	MACROS	+=	D_LITTLE_ENDIAN=1
endif

##e2p大小配置
MACROS	+=	D_EEPROM_RECOMMEND_SIZE=$(G_EEPROM_RECOMMEND_SIZE)

#计时打印支持(y/n)
ifeq ($(G_DEBUG_TIME_RECORD), y)
	MACROS	+=	D_DEBUG_TIME_RECORD=1
endif

########一些aux配置
########数据库配置######
MACROS		+= D_DB_SERVICE_NAME_LEN=32		#节目名称长度，以字节为单位
MACROS		+= D_MAX_NV_PART_DATA_CNT=96	#一个数据分区中存在的表、域、数据块的最大数目

#数据库节目信息预留大小(字节数)
MACROS		+= D_SRV_RESERVE_SIZE=$(DB_SRV_RESERVE_SIZE)

#数据库节目信息里是否支持的4路音频(y/n)
ifeq ($(DB_SRV_SUPPORT_4AUDIO), y)
	MACROS	+=	D_DB_SRV_SUPPORT_4AUDIO=1
endif

#数据库TS 预留大小(字节数)
MACROS		+= D_TS_RESERVE_SIZE=$(DB_TS_RESERVE_SIZE)

MACROS		+= D_DB_SATE_NAME_LEN=16		#卫星名称长度，以字节为单位
MACROS		+= D_DB_NETWORK_NAME_LEN=32		#网络名称长度，以字节为单位
MACROS		+= D_DB_EVENT_DESC_LEN=256
MACROS		+= D_DB_BOUQUET_NAME_LEN=32		#业务群名称长度，以字节为单位
MACROS		+= D_DB_EVENT_NAME_LEN=50		#预约节目名称长度，以字节为单位

#是否支持lwip, 只有hros和win32可以支持(y/n)
ifeq ($(G_AUX_SUPPORT_LWIP), y)
	MACROS	+=	D_AUX_SUPPORT_LWIP=1
endif

########一些GUI的配置
########绘图设备选择
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

##支持画非正交直线
ifeq ($(G_GUI_SUPPORT_LINE), y)
	MACROS	+=	D_GUI_SUPPORT_LINE=1
endif

##支持画弧线
ifeq ($(G_GUI_SUPPORT_ARC), y)
	MACROS	+=	D_GUI_SUPPORT_ARC=1
endif

##支持画填充扇形
ifeq ($(G_GUI_SUPPORT_FILL_ARC), y)
	MACROS	+=	D_GUI_SUPPORT_FILL_ARC=1
endif

##支持画椭圆
ifeq ($(G_GUI_SUPPORT_ELLIPSE), y)
	MACROS	+=	D_GUI_SUPPORT_ELLIPSE=1
endif

##支持画填充椭圆
ifeq ($(G_GUI_SUPPORT_FILL_ELLIPSE), y)
	MACROS	+=	D_GUI_SUPPORT_FILL_ELLIPSE=1
endif

##支持画多边形
ifeq ($(G_GUI_SUPPORT_POLY), y)
	MACROS	+=	D_GUI_SUPPORT_POLY=1
endif

##支持画填充多边形
ifeq ($(G_GUI_SUPPORT_FILL_POLY), y)
	MACROS	+=	D_GUI_SUPPORT_FILL_POLY=1
endif

##可安装的字库的最大数
MACROS	+=	D_GUI_SUPPORT_FONT_CNT=$(G_GUI_SUPPORT_FONT_CNT)

##大端PDMA支持(y/n)
ifeq ($(G_PDMA_BIGENDIAN_PATCH), y)
	MACROS	+=	D_PDMA_BIGENDIAN_PATCH=1
endif

##freetype字模缓冲(y/n)
ifeq ($(G_GUI_FREETYPE_CACHE_IMAGE_MODEL), y)
	MACROS	+=	D_GUI_FREETYPE_CACHE_IMAGE_MODEL=1
endif

##鼠标与触摸屏支持(y/n)
ifeq ($(G_GUI_SUPPORT_MOUSE_TOUCHSCREEN), y)
	MACROS	+=	D_GUI_SUPPORT_MOUSE_TOUCHSCREEN=1
endif

##支持过滤器非版本控制
ifeq ($(SUPPORT_DIFFER_VER_CONTROL), y)
	MACROS	+=	D_MONITOR_SUPPORT_DIFFER_VER_CONTROL=1
endif


##支持不可见的系统和卷标的显示，老人机三峰厂家专用，其他情况下关闭。

ifeq ($(HI_P_MINITV_SYSTEM_FILE_SHOW_EN), y)
	MACROS	+=	D_MINITV_SYSTEM_FILE_SHOW_EN=1
endif

##############################################
##                                 					##
##		          音视频相关配置              ##
## 	   (减少相应微码，减少代码空间)     ##
##                                 					##
##############################################
#音频格式支持(ALL 或者 MPEG2 AC3 AAC MP3 WMA AMR DTS DRA WAV PCM ADPCM INTERPHONE组合)
ifdef G_AUDIO_SUPPORT_CODEC
	MACROS	+=	$(patsubst %,D_AUDIO_SUPPORT_CODEC_%,$(G_AUDIO_SUPPORT_CODEC))
else
	MACROS	+=	D_AUDIO_SUPPORT_CODEC_ALL=1
endif

##音量平衡是否支持负数
ifeq ($(G_AUDIO_SUPPORT_BALANCE), y)
	MACROS	+=	D_AUDIO_SUPPORT_BALANCE=1
endif

##############################################
##                                 					##
##		          图片解码相关配置            ##
## 	(配置支持的图片格式 GIF JPEG PNG BMP)   ##
##                                 					##
##############################################
##支持图像解码格式(ALL 或是 GIF JPEG PNG BMP组合)
ifdef G_SUPPORT_IMAGE_TYPE
	MACROS	+=	$(patsubst %,D_SUPPORT_IMAGE_%,$(G_SUPPORT_IMAGE_TYPE))
else
	MACROS	+=	D_SUPPORT_IMAGE_ALL=1
endif

##是否使用新jpeg解码模块
ifeq ($(G_SYS_JPEG_NEW), y)
	MACROS	+=	D_JPEG_DEV=1
	ifeq ($(G_SUPPORT_PROGRESSIVE),y)
	 MACROS	+=	D_JPEG_SUPPORT_PROGRESSIVE=1
	endif
endif


##############################################
##                                 					##
##		          CA功能相关配置              ##
## 	   (免费项目不使用ca，减少代码空间)     ##
##                                 					##
##############################################
#系统是否支持ca功能(y/n)
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

#是否支持NDSICAM (y/n)
ifeq ($(G_SUPPORT_NDS_ICAM), y)
		MACROS	+=	D_SUPPORT_NDS_ICAM=1
endif	
	
#是否支持NDSCAHDI测试 (y/n)
ifeq ($(G_SUPPORT_NDSCAHDI), y)
	MACROS	+=	D_SUPPORT_NDSCAHDI=1
	ifeq ($(G_NDSCAHDI_VERIFIER), y)
		MACROS	+=	D_NDSCAHDI_VERIFIER=1
	endif
endif

##############################################
##                                 					##
##		     烧写OTP功能相关配置              ##
##   (某些项目不使用此配置，减少代码空间)   ##
##                                 					##
##############################################
#系统是否支持程序烧写otp功能(y/n)
ifdef G_SYS_SUPPORT_OTP
	ifeq ($(G_SYS_SUPPORT_OTP), y)
		MACROS	+=	D_SYS_SUPPORT_OTP=1
	endif
else
##  	MACROS	+=	D_SYS_SUPPORT_OTP=1
endif


##############################################
##                                 					##
##		   联广山东密钥OTP的烧写配置          ##
##    当G_SYS_SUPPORT_OTP = y时，如果       ##
##    需要烧写-Nsd密钥时，打开此宏定义      ##
##############################################
#是否烧写联广-Nsd密钥功能(y/n)
ifdef G_SYS_SUPPORT_OTP_ABV_NSD
	ifeq ($(G_SYS_SUPPORT_OTP_ABV_NSD), y)
		MACROS	+=	D_SYS_SUPPORT_OTP_ABV_NSD=1
	endif
endif

##############################################
##                                 					##
##		       字符编码转换相关配置           ##
## 	  (合理配置，减少转换映射表所占空间)    ##
##                                 					##
##############################################

#支持中文字符编码转换(y/n)
ifdef G_CC_SUPPORT_CHINESE
	ifeq ($(G_CC_SUPPORT_CHINESE), y)
		MACROS	+=	D_CC_SUPPORT_CHINESE=1
	endif
else
	MACROS	+=	D_CC_SUPPORT_CHINESE=1
endif

#中文GBK/GB2312字符编码转换(GB2312/GBK)
ifeq ($(G_CC_SUPPORT_GB2312_GBK), GBK)
	MACROS	+=	D_CC_SUPPORT_GBK=1
else
	MACROS	+=	D_CC_SUPPORT_GB2312=1
endif

#支持中文big5转到GBK/GB2312字符编码转换(y/n)
ifdef G_CC_SUPPORT_CHINESE
ifeq ($(G_CC_SUPPORT_BIG5), y)
	MACROS	+=	D_CC_SUPPORT_BIG5=1
endif
else
	MACROS	+=	D_CC_SUPPORT_BIG5=1
endif

#####################################
##                                 ##
##       切PLL1频率配置        	   ##
##                                 ##
#####################################
#是否改变PLL1频率(y/n)
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
##    	  是否支持liulink Client    ##
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
