#
##  编译规则配置
#

PLATFORM_DIR	=	$(WORKROOT)/platform
PROJECT_DIR	=	$(WORKROOT)/project/$(PROJECT)

RM	= @rm -rvf
MKDIR	= @mkdir -vp
CP	= @cp -av

ifeq ($(G_TV_SUPPORT_IPTV), y)
INC_PATHS	+=	$(PLATFORM_DIR)/include \
				$(PROJECT_DIR)/include \
				/opt/toolchain-2017/usr/mipsel-buildroot-linux-gnu/sysroot/soft-float/el/usr/include/libsoup-2.4 \
				/opt/toolchain-2017/usr/mipsel-buildroot-linux-gnu/sysroot/soft-float/el/usr/include/libxml2 \
				/opt/toolchain-2017/usr/mipsel-buildroot-linux-gnu/sysroot/soft-float/el/usr/include/pixman-1 \
				/opt/toolchain-2017/usr/mipsel-buildroot-linux-gnu/sysroot/soft-float/el/usr/include/json-glib-1.0 \
				/opt/toolchain-2017/usr/mipsel-buildroot-linux-gnu/sysroot/usr/lib/glib-2.0/include \
				/opt/toolchain-2017/usr/mipsel-buildroot-linux-gnu/sysroot/soft-float/el/usr/include/glib-2.0 \
				/opt/toolchain-2017/usr/mipsel-buildroot-linux-gnu/sysroot/soft-float/el/usr/include/glib-2.0/include \
				/opt/toolchain-2017/usr/mipsel-buildroot-linux-gnu/sysroot/soft-float/el/usr/include/directfb \
				${HI_HTK_PATH}/include \
				${HI_HTK_PATH} \
				/opt/toolchain-2017/usr/mipsel-buildroot-linux-gnu/sysroot/soft-float/el/usr/include
else
INC_PATHS	+=	$(PLATFORM_DIR)/include \
							$(PROJECT_DIR)/include
endif

#####################################宏配置#######################################

MACROS	+=	PREFIXCONST=
MACROS	+=	POSTCONST=

##DEBUG选项
ifeq ($(G_PROJECT_DEBUG), y)
	MACROS	+=	D_DEBUG=1
endif

##GAMATEST选项
ifeq ($(G_PLATFORM_GAMATEST), y)
	MACROS	+=	D_GAMA_TEST=1
endif

##DEBUG调试定位串口号(0,1,...)
MACROS	+=	D_DEBUG_TO_UART=$(G_DEBUG_TO_UART)

##DEBUG打印级别(0-4)
MACROS	+=	D_DEBUG_LEVEL=$(G_DEBUG_LEVEL)

##是否启动testtool命令行(y/n)
ifeq ($(G_USE_TESTTOOL), y)
	MACROS	+=	D_USE_TESTTOOL=1
endif

##是否开启烧写序列号(y/n)
ifeq ($(G_BURNER_SERIAL_NUM), y)
	MACROS	+=	D_BURNER_SERIAL_NUM=1
	ifeq ($(G_BURN_SERIAL_NUM_MODE), a)
		MACROS	+=	D_BURN_SN_MODE_A=1
	endif
	ifeq ($(G_BURN_SERIAL_NUM_MODE), b)
		MACROS	+=	D_BURN_SN_MODE_B=1
	endif
	ifeq ($(G_BURN_SERIAL_NUM_MODE), e)
		MACROS	+=	D_BURN_SN_MODE_E=1
	endif
endif

##是否开串口调整白平衡(电视机出厂时使用)(y/n)
ifeq ($(G_COLOUR_SERIAL_EN), y)
	MACROS	+=	D_COLOUR_SERIAL_EN=1
endif

#是否开启江苏项目烧号配置(y/n)
ifeq ($(G_JIANGSU_BURNER_SERIAL_NUM), y)
	MACROS	+=	D_JIANGSU_BURNER_SERIAL_NUM=1
endif

##是否开启烧写OTP功能(y/n)
ifeq ($(G_BURNER_OTP), y)
	MACROS	+=	D_BURNER_OTP=1
	ifeq ($(G_BURN_OTP_MODE), a)
		MACROS	+=	D_BURN_OTP_MODE_A=1
	endif
	ifeq ($(G_BURN_OTP_MODE), b)
		MACROS	+=	D_BURN_OTP_MODE_B=1
	endif
endif

##应用分区在flash里的偏移地址(无配置时的默认值)
MACROS	+=	D_APP_PART_DEFAULT_OFFSET=$(G_APP_PART_DEFAULT_OFFSET)

##包含platform的一些配置
include $(PLATFORM_DIR)/make/platform_cfg.mk

#####################################
##                                 ##
##      config数据块相关配置       ##
##                                 ##
#####################################
#厂家ID(32位)
MACROS	+=	D_MANUFACTORY_ID=$(G_MANUFACTORY_ID)

#硬件ID(8位)
MACROS	+=	D_HARDWARE_ID=$(G_HARDWARE_ID)

#硬件主版本号(8位)
MACROS	+=	D_HARDWARE_MAJOR_VER=$(G_HARDWARE_MAJOR_VER)

#硬件次版本号(16位)
MACROS	+=	D_HARDWARE_MINOR_VER=$(G_HARDWARE_MINOR_VER)

#软件主版本号(8位)
MACROS	+=	D_SOFTWARE_MAJOR_VER=$(G_SOFTWARE_MAJOR_VER)

#软件次版本号(8位)
MACROS	+=	D_SOFTWARE_MINOR_VER=$(G_SOFTWARE_MINOR_VER)

#软件内部版本号(16位)
MACROS	+=	D_SOFTWARE_BUILD_NUM=$(G_SOFTWARE_BUILD_NUM)

#密码位数
#MACROS	+=	D_CONF_PASSWORD_LEN=$(G_CONF_PASSWORD_LEN)

#默认密码
#MACROS	+=	D_CONF_DEF_PASSWORD=$(G_CONF_DEF_PASSWORD)

#超级密码
#MACROS	+=	D_CONF_SUPER_PASSWORD=$(G_CONF_SUPER_PASSWORD)

#config数据在存储表的偏移量
MACROS	+=	D_CONF_OFFSET_IN_TBL=$(G_CONF_OFFSET_IN_TBL)
MACROS	+=	D_TVCONF_OFFSET_IN_TBL=$(G_TVCONF_OFFSET_IN_TBL)

#####################################
##                                 ##
##        硬件资源相关配置         ##
##                                 ##
#####################################
#目标板(HIC_2610D_DVBC/HIC_2610D_DTMB/HIC_2610D_DTMB_DVBC)
ifeq ($(G_BOARD), HIC_2610D_DVBC)
	MACROS	+=	P_BOARD_HIC_2610D_DVBC=1
endif
ifeq ($(G_BOARD), HIC_2610D_DTMB)
	MACROS	+=	P_BOARD_HIC_2610D_DTMB=1
endif
ifeq ($(G_BOARD), HIC_2610D_DTMB_DVBC)
	MACROS	+=	P_BOARD_HIC_2610D_DTMB_DVBC=1
endif

ifeq ($(G_BOARD), HIC_2610E_DTMB_DVBC)
	MACROS	+=	P_BOARD_HIC_2610E_DTMB_DVBC=1
endif


#目标板配置是否使用软件预置(y/n)
ifeq ($(G_BOARD_CONFIG_USE_LOCAL), y)
	MACROS	+=	D_BOARD_CONFIG_USE_LOCAL=1
endif

#Flash map选择(8M/4M/16M)
ifeq ($(G_FLASH_MAP), 8M)
	MACROS	+=	D_FLASH_MAP_8M=1
	MACROS	+=	D_EEPROM_FAKE_BLOCK1=0x000D0000
	MACROS	+=	D_EEPROM_FAKE_BLOCK2=0x000E0000
	MACROS	+=	D_SPECIAL_BLOCK_SIZE=0x10000
endif

ifeq ($(G_FLASH_MAP), 4M)
ifeq ($(G_AD_SUPPORT_DESAI), y)
	MACROS	+=	D_FLASH_MAP_4M=1
endif	
ifneq ($(G_AD_SUPPORT_DESAI), y)
	MACROS	+=	D_FLASH_MAP_4M_2=1
endif
	MACROS	+=	D_EEPROM_FAKE_BLOCK1=0x00090000
	MACROS	+=	D_EEPROM_FAKE_BLOCK2=0x000A0000
	MACROS	+=	D_SPECIAL_BLOCK_SIZE=0x10000
endif

ifeq ($(G_FLASH_MAP), 16M)
	MACROS	+=	D_FLASH_MAP_16M=1
	MACROS	+=	D_EEPROM_FAKE_BLOCK1=0x000D0000
	MACROS	+=	D_EEPROM_FAKE_BLOCK2=0x000E0000
	MACROS	+=	D_SPECIAL_BLOCK_SIZE=0x10000
endif

ifeq ($(G_FLASH_MAP), 32M)
	MACROS	+=	D_FLASH_MAP_32M=1
	MACROS	+=	D_EEPROM_FAKE_BLOCK1=0x000D0000
	MACROS	+=	D_EEPROM_FAKE_BLOCK2=0x000E0000
	MACROS	+=	D_SPECIAL_BLOCK_SIZE=0x10000
endif

ifeq ($(G_FLASH_MAP), 128M)
	MACROS	+=	D_FLASH_MAP_128M=1
	MACROS	+=	D_EEPROM_FAKE_BLOCK1=0x000D0000
	MACROS	+=	D_EEPROM_FAKE_BLOCK2=0x000E0000
	MACROS	+=	D_SPECIAL_BLOCK_SIZE=0x10000
endif

#DDR大小配置(16M/32M/64M)
ifeq ($(G_DDR_SIZE), 16M)
	MACROS	+=	D_DDR_SIZE_16M=1
endif

ifeq ($(G_DDR_SIZE), 32M)
	MACROS	+=	D_DDR_SIZE_32M=1
endif

ifeq ($(G_DDR_SIZE), 64M)
	MACROS	+=	D_DDR_SIZE_64M=1
endif

ifeq ($(G_DDR_SIZE), 128M)
	MACROS	+=	D_DDR_SIZE_128M=1
endif

ifeq ($(G_DDR_SIZE), 256M)
	MACROS	+=	D_DDR_SIZE_256M=1
endif

#内存分区1大小(Byte)
MACROS	+=	D_MEM1_SIZE=$(G_MEM1_SIZE)

#内存分区2大小(Byte)
MACROS	+=	D_MEM2_SIZE=$(G_MEM2_SIZE)

#是否启用网络(y/n)
ifeq ($(G_USE_NETWORK), y)
	MACROS	+=	D_USE_NETWORK=1
endif

#屏幕水平分辨率
MACROS	+=	D_SCREEN_HOR_RESOLUTION=$(G_SCREEN_HOR_RESOLUTION)

#屏幕垂直分辨率
MACROS	+=	D_SCREEN_VER_RESOLUTION=$(G_SCREEN_VER_RESOLUTION)

#屏幕颜色RGB位数
MACROS	+=	D_SCREEN_COLOR_BITS=$(G_SCREEN_COLOR_BITS)

#是否使用后备缓冲区
ifeq ($(G_USE_BACK_BUFFER), y)
	MACROS	+=	D_USE_BACK_BUFFER=1

ifeq ($(G_TV_LIULINK_OSD_PORTRAIT), y)
	#### 竖屏
	
	MACROS	+=	D_TV_LIULINK_OSD_PORTRAIT=1
	
	## 默认向右旋转90
	####MACROS	+=	D_TV_LIULINK_OSD_LEFT=1
	
	MACROS	+=	D_VIRTUAL_SCREEN_W=$(G_SCREEN_VER_RESOLUTION)
	MACROS	+=	D_VIRTUAL_SCREEN_H=$(G_SCREEN_HOR_RESOLUTION)
else
	MACROS	+=	D_VIRTUAL_SCREEN_W=$(G_SCREEN_HOR_RESOLUTION)
	MACROS	+=	D_VIRTUAL_SCREEN_H=$(G_SCREEN_VER_RESOLUTION)
endif

endif

#####################################
##                                 ##
##        GUI资源相关配置          ##
##                                 ##
#####################################
##支持JPEG图像
ifeq ($(G_GUI_SUPPORT_JPEG), y)
	MACROS	+= D_GUI_SUPPORT_JPEG=1
endif

##支持PNG图像
ifeq ($(G_GUI_SUPPORT_PNG), y)
	MACROS	+=	D_GUI_SUPPORT_PNG=1
endif

##支持freetype
ifeq ($(G_GUI_SUPPORT_FREETYPE), y)
	MACROS	+=	D_GUI_SUPPORT_FREETYPE=1
endif

##中文扩展字库GBK
ifeq ($(G_GUI_SUPPORT_GBK), y)
	MACROS	+=	D_GUI_SUPPORT_GBK=1
endif

##支持扬声器开关
ifeq ($(G_GUI_SUPPORT_SPEAKER), y)
	MACROS	+=	D_GUI_SUPPORT_SPEAKER=1
endif
#####################################
##                                 ##
##        CA资源相关配置           ##
##                                 ##
#####################################

#默认ca
MACROS		+= D_CA_SUPPORT_DEF=$(G_CA_SUPPORT_DEF)

#####################################
##                                 ##
##       数据库资源相关配置        ##
##                                 ##
#####################################
ifeq ($(DVB_TYPE), dvbs)	
	MACROS		+= HI_SOFT_TYPE_DVBS=1
	MACROS		+= P_DBASE_DVBS=1			#DVBS数据库
	MACROS		+= P_DB_MAX_ANTE_CNT=20		#天线个数	
	MACROS		+= P_DB_MAX_SAT_CNT=100		#卫星个数
	MACROS		+= P_DB_MAX_TS_CNT=504		#转发器个数
	MACROS		+= P_DB_TEMP_TS_CNT=4		#临时转发器个数
	MACROS		+= P_CHECK_FRE_RANGE=3			#判断是否是同一转发器时，频率的偏差范围
	MACROS		+= P_CHECK_BAUD_RANGE=10		#判断是否是同一转发器时，符号率的偏差范围
	MACROS		+= P_DB_MAX_SRV_CNT=2010		#设置节目数
	MACROS		+= P_DB_TEMP_SRV_CNT=10		#临时节目数
	MACROS		+= P_DB_MAX_NET_CNT=32		#多网络个数
endif

ifeq ($(DVB_TYPE), dtmb)
	MACROS		+= HI_SOFT_TYPE_DTMB=1
	MACROS		+= P_DBASE_DVBT=1			#DVBT数据库
	MACROS		+= P_DB_MAX_ANTE_CNT=0
	MACROS		+= P_DB_MAX_SAT_CNT=0
ifeq ($(G_DDR_SIZE), 64M)
	MACROS		+= P_DB_MAX_TS_CNT=99		#转发器个数	
	MACROS		+= P_DB_TEMP_TS_CNT=4		#临时转发器个数
	MACROS		+= P_DB_MAX_SRV_CNT=299		#设置节目数
else
	MACROS		+= P_DB_MAX_TS_CNT=204		#转发器个数	
	MACROS		+= P_DB_TEMP_TS_CNT=4		#临时转发器个数
	MACROS		+= P_DB_MAX_SRV_CNT=1010		#设置节目数
endif
	MACROS		+= P_DB_TEMP_SRV_CNT=10		#临时节目数
	MACROS		+= P_DB_MAX_NET_CNT=1		#单网络时只有一个
endif

ifeq ($(DVB_TYPE), dvbc)
	MACROS		+= HI_SOFT_TYPE_DVBC=1
	MACROS		+= P_DBASE_DVBC=1			#DVBC数据库
	MACROS		+= P_DB_MAX_ANTE_CNT=0
	MACROS		+= P_DB_MAX_SAT_CNT=0
	MACROS		+= P_DB_MAX_TS_CNT=204		#转发器个数	
	MACROS		+= P_DB_TEMP_TS_CNT=4		#临时转发器个数	
	MACROS		+= P_DB_MAX_SRV_CNT=1010		#设置节目数
	MACROS		+= P_DB_TEMP_SRV_CNT=10		#临时节目数
	MACROS		+= P_DB_MAX_NET_CNT=1		#单网络时只有一个
endif

ifeq ($(DVB_TYPE), dtmb_dvbc)
	MACROS		+= HI_SOFT_TYPE_DTMB_DVBC=1
	MACROS		+= P_DBASE_DVBC=1			#DVBC数据库
	MACROS		+= P_DB_MAX_ANTE_CNT=0
	MACROS		+= P_DB_MAX_SAT_CNT=0
	MACROS		+= P_DB_MAX_TS_CNT=204		#转发器个数	
	MACROS		+= P_DB_TEMP_TS_CNT=4		#临时转发器个数	
	MACROS		+= P_DB_MAX_SRV_CNT=1010		#设置节目数
	MACROS		+= P_DB_TEMP_SRV_CNT=10		#临时节目数
	MACROS		+= P_DB_MAX_NET_CNT=1		#单网络时只有一个
endif
ifeq ($(G_AD_USE_EPG_MEM), y)
					MACROS		+= P_DB_MAX_EVT_CNT=0						#事件个数
					MACROS		+= P_AD_USE_EPG_MEM=1													#由于空间问题，带广告的时候关闭epg
endif	
ifneq ($(G_AD_USE_EPG_MEM), y)
MACROS		+= P_DB_MAX_EVT_CNT=$(G_DB_MAX_EVT_CNT)		#事件个数
endif
MACROS		+= P_DB_MAX_BOUQ_CNT=$(G_DB_MAX_BOUQ_CNT)	#业务群数目

MACROS		+= P_DB_MAX_SUB_CNT=$(G_DB_MAX_SUB_CNT)		#预约节目个数
MACROS		+= P_SUBSCRIBE_TIME=$(G_SUBSCRIBE_TIME) 	#判断定时器是否超时时使用，提前30秒倒计时

MACROS		+= P_NVPART_TAIL_FLAG=$(G_NVPART_TAIL_FLAG)

MACROS		+= P_CONFIG_BLOCK_SIZE=$(G_CONFIG_BLOCK_SIZE)


#####################################
##                                 ##
##       UMT升级相关配置        	 ##
##                                 ##
#####################################
##UMT升级类型
ifeq ($(G_UMT_TYPE), y)
	MACROS	+=	D_UMT_UP_DATA_TYPE=1
endif


#####################################
##                                 ##
##       多媒体相关配置            ##
##                                 ##
#####################################
##pvr功能是否打开(y/n)
ifeq ($(G_PVR_EN),y)
	MACROS		+= HI_P_PVR_EN=1
endif

ifeq ($(G_PVR_EN),n)
	MACROS		+= HI_P_PVR_EN=0
endif

##多媒体功能是否打开(y/n)
ifeq ($(G_MUTIMEDIA_EN),y)
	MACROS		+= HI_P_MUTIMEDIA_EN=1
endif
ifeq ($(G_MUTIMEDIA_EN),n)
	MACROS		+= HI_P_MUTIMEDIA_EN=0
endif

##多媒体非目录是否打开(y/n)
ifeq ($(G_MUTIMEDIA_NOCATALOG),y)
	MACROS		+= D_MUTIMEDIA_NOCATALOG=1
endif

#####################################
##                                 ##
##       DBG输出相关配置        	 ##
##                                 ##
#####################################
#默认输出配置
ifeq ($(G_DBG_DISK_OPEN), y)
MACROS		+= D_DBG_DISK_OPEN=$(G_DBG_DISK_OPEN)
endif
######################################
##                                 ##
##       电视相关配置        	     ##
##                                 ##
#####################################
##电视功能软件类型(TV/TV_STB/STB)
ifeq ($(G_TV_SOFT_TYPE),TV)
	MACROS		+= HI_P_TV_TYPE_TV=1
endif	

ifeq ($(G_TV_SOFT_TYPE),TV_STB)
	MACROS		+= HI_P_TV_TYPE_TV_STB=1
endif	

##数字音质音乐和电影菜单是否打开(y/n)
ifeq ($(G_TV_MENU_SHOW_EN),y)
	MACROS		+= HI_P_TV_MENU_SHOW_EN=1
endif

ifeq ($(G_TV_MENU_SHOW_EN),n)
	MACROS		+= HI_P_TV_MENU_SHOW_EN=0
endif

#信号源显示(AV1 AV2 HDMI1 HDMI2)
ifdef G_IUTPUT_SUPPORT_DEF
	MACROS	+=	$(patsubst %,D_IUTPUT_SUPPORT_%,$(G_IUTPUT_SUPPORT_DEF))
endif

##在无DTV时是否支持PVR(y/n)
ifeq ($(G_TV_SUPPORT_PVR), y)
		MACROS	+=	D_TV_SUPPORT_PVR=1
endif

##是否是投影仪项目(y/n)
ifeq ($(G_TV_PEOJECT_TOUYY), y)
		MACROS	+=	D_TV_PEOJECT_TOUYY=1
endif

##是否图像设置新结构新菜单(y/n)
ifeq ($(G_TV_FC_IMAGE_SOURCE), y)
		MACROS	+=	D_TV_IAMGE_SOURCE=1
endif

##支持tv_mini
ifeq ($(G_TV_UI_STYLE),MINI)
	MACROS	+= D_TV_UI_STYLE_MINI=1
endif

##是否青岛海尔功能(y/n)
ifeq ($(G_TV_QINGDAO_HAIER_FUN),y)
	MACROS		+= HI_QINGDAO_HAIER_FUN=1
endif


##是否支持miracast(y/n)
ifeq ($(G_TV_MIRACAST_SOURCE), y)
	MACROS +=	D_TV_MIRACAST_SOURCE=1
	MACROS +=	D_TV_SUPPORT_WIFI=1
endif

##miracast 设备主名称
ifdef G_TV_MIRACAST_DEVNAME
	MACROS	+=	D_TV_MIRACAST_DEVNAME=$(G_TV_MIRACAST_DEVNAME)
endif

##是否支持dlna(y/n)
ifeq ($(G_TV_DLNA_SOURCE), y)
	MACROS +=	D_TV_DLNA_SOURCE=1
	MACROS +=	D_TV_SUPPORT_WIFI=1
endif

##dlna 设备主名称
ifdef G_TV_DLNA_DEVNAME
	MACROS	+=	D_TV_DLNA_DEVNAME=$(G_TV_DLNA_DEVNAME)
endif

##是否支持ts转发,即ts2net(y/n)
ifeq ($(G_TV_SUPPORT_TS2NET), y)
	MACROS +=	D_TV_SUPPORT_TS2NET=1
	MACROS +=	D_TV_SUPPORT_WIFI=1
endif

##ts2net 设备主名称
ifdef G_TV_TS2NET_DEVNAME
	MACROS	+=	D_TV_TS2NET_DEVNAME=$(G_TV_TS2NET_DEVNAME)
endif

##是否有iptv(y/n)
ifeq ($(G_TV_SUPPORT_IPTV),y)
	MACROS	+= D_TV_SUPPORT_IPTV=1
	MACROS +=	D_TV_SUPPORT_WIFI=1
endif

##是否有airplay(y/n)
ifeq ($(G_TV_SUPPORT_AIRPLAY),y)
	MACROS	+= D_TV_SUPPORT_AIRPLAY=1
	MACROS +=	D_TV_SUPPORT_WIFI=1
endif

##airplay 设备主名称
ifdef G_TV_AIRPLAY_DEVNAME
	MACROS	+=	D_TV_AIRPLAY_DEVNAME=$(G_TV_AIRPLAY_DEVNAME)
endif

#默认ca
MACROS		+= D_CA_SUPPORT_DEF=$(G_CA_SUPPORT_DEF)

#######################################
##                                 ##
##    是否有ypbpr 及 视频2    	   ##
##                                 ##
#####################################
##是否有ypbpr 及 视频2(y/n)
ifeq ($(G_TV_SIGNAL_SOURCE),y)
	MACROS	+= D_TV_SIGNAL_SOURCE=1
endif



###################################### 编译规则################################################
ALL_DEF: all
-include  *.d

##选择工具链
ifeq ($(G_DEVTOOLS), msvc)
	include $(PROJECT_DIR)/make/win32_msvc_cygwin.mk
endif

ifeq ($(G_DEVTOOLS), ghs_cyg)
	include $(PROJECT_DIR)/make/rtos_ghs_cygwin.mk
endif

ifeq ($(G_DEVTOOLS), mipsisa32_gcc_cyg)
	include $(PROJECT_DIR)/make/rtos_mipsisa32gcc_cygwin.mk
endif

ifeq ($(G_DEVTOOLS), mipsgnu_gcc_linux)
	include $(PROJECT_DIR)/make/linux_mipsgnugcc_i386.mk
endif

##公共规则
all: subdirs $(O_TARGET) $(LIB_TARGET) $(EXECUTE_TARGET)

clean:
	$(SPECIAL_CLEAN)
	$(ARCH_CLEAN)
	@$(RM) $(O_TARGET) $(OBJS) $(LIB_TARGET) $(EXT_OBJS) $(EXECUTE_TARGET) *.d *.dpp
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
