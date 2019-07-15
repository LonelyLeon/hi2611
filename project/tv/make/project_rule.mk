#
##  �����������
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

#####################################������#######################################

MACROS	+=	PREFIXCONST=
MACROS	+=	POSTCONST=

##DEBUGѡ��
ifeq ($(G_PROJECT_DEBUG), y)
	MACROS	+=	D_DEBUG=1
endif

##GAMATESTѡ��
ifeq ($(G_PLATFORM_GAMATEST), y)
	MACROS	+=	D_GAMA_TEST=1
endif

##DEBUG���Զ�λ���ں�(0,1,...)
MACROS	+=	D_DEBUG_TO_UART=$(G_DEBUG_TO_UART)

##DEBUG��ӡ����(0-4)
MACROS	+=	D_DEBUG_LEVEL=$(G_DEBUG_LEVEL)

##�Ƿ�����testtool������(y/n)
ifeq ($(G_USE_TESTTOOL), y)
	MACROS	+=	D_USE_TESTTOOL=1
endif

##�Ƿ�����д���к�(y/n)
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

##�Ƿ񿪴��ڵ�����ƽ��(���ӻ�����ʱʹ��)(y/n)
ifeq ($(G_COLOUR_SERIAL_EN), y)
	MACROS	+=	D_COLOUR_SERIAL_EN=1
endif

#�Ƿ���������Ŀ�պ�����(y/n)
ifeq ($(G_JIANGSU_BURNER_SERIAL_NUM), y)
	MACROS	+=	D_JIANGSU_BURNER_SERIAL_NUM=1
endif

##�Ƿ�����дOTP����(y/n)
ifeq ($(G_BURNER_OTP), y)
	MACROS	+=	D_BURNER_OTP=1
	ifeq ($(G_BURN_OTP_MODE), a)
		MACROS	+=	D_BURN_OTP_MODE_A=1
	endif
	ifeq ($(G_BURN_OTP_MODE), b)
		MACROS	+=	D_BURN_OTP_MODE_B=1
	endif
endif

##Ӧ�÷�����flash���ƫ�Ƶ�ַ(������ʱ��Ĭ��ֵ)
MACROS	+=	D_APP_PART_DEFAULT_OFFSET=$(G_APP_PART_DEFAULT_OFFSET)

##����platform��һЩ����
include $(PLATFORM_DIR)/make/platform_cfg.mk

#####################################
##                                 ##
##      config���ݿ��������       ##
##                                 ##
#####################################
#����ID(32λ)
MACROS	+=	D_MANUFACTORY_ID=$(G_MANUFACTORY_ID)

#Ӳ��ID(8λ)
MACROS	+=	D_HARDWARE_ID=$(G_HARDWARE_ID)

#Ӳ�����汾��(8λ)
MACROS	+=	D_HARDWARE_MAJOR_VER=$(G_HARDWARE_MAJOR_VER)

#Ӳ���ΰ汾��(16λ)
MACROS	+=	D_HARDWARE_MINOR_VER=$(G_HARDWARE_MINOR_VER)

#������汾��(8λ)
MACROS	+=	D_SOFTWARE_MAJOR_VER=$(G_SOFTWARE_MAJOR_VER)

#����ΰ汾��(8λ)
MACROS	+=	D_SOFTWARE_MINOR_VER=$(G_SOFTWARE_MINOR_VER)

#����ڲ��汾��(16λ)
MACROS	+=	D_SOFTWARE_BUILD_NUM=$(G_SOFTWARE_BUILD_NUM)

#����λ��
#MACROS	+=	D_CONF_PASSWORD_LEN=$(G_CONF_PASSWORD_LEN)

#Ĭ������
#MACROS	+=	D_CONF_DEF_PASSWORD=$(G_CONF_DEF_PASSWORD)

#��������
#MACROS	+=	D_CONF_SUPER_PASSWORD=$(G_CONF_SUPER_PASSWORD)

#config�����ڴ洢���ƫ����
MACROS	+=	D_CONF_OFFSET_IN_TBL=$(G_CONF_OFFSET_IN_TBL)
MACROS	+=	D_TVCONF_OFFSET_IN_TBL=$(G_TVCONF_OFFSET_IN_TBL)

#####################################
##                                 ##
##        Ӳ����Դ�������         ##
##                                 ##
#####################################
#Ŀ���(HIC_2610D_DVBC/HIC_2610D_DTMB/HIC_2610D_DTMB_DVBC)
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


#Ŀ��������Ƿ�ʹ�����Ԥ��(y/n)
ifeq ($(G_BOARD_CONFIG_USE_LOCAL), y)
	MACROS	+=	D_BOARD_CONFIG_USE_LOCAL=1
endif

#Flash mapѡ��(8M/4M/16M)
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

#DDR��С����(16M/32M/64M)
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

#�ڴ����1��С(Byte)
MACROS	+=	D_MEM1_SIZE=$(G_MEM1_SIZE)

#�ڴ����2��С(Byte)
MACROS	+=	D_MEM2_SIZE=$(G_MEM2_SIZE)

#�Ƿ���������(y/n)
ifeq ($(G_USE_NETWORK), y)
	MACROS	+=	D_USE_NETWORK=1
endif

#��Ļˮƽ�ֱ���
MACROS	+=	D_SCREEN_HOR_RESOLUTION=$(G_SCREEN_HOR_RESOLUTION)

#��Ļ��ֱ�ֱ���
MACROS	+=	D_SCREEN_VER_RESOLUTION=$(G_SCREEN_VER_RESOLUTION)

#��Ļ��ɫRGBλ��
MACROS	+=	D_SCREEN_COLOR_BITS=$(G_SCREEN_COLOR_BITS)

#�Ƿ�ʹ�ú󱸻�����
ifeq ($(G_USE_BACK_BUFFER), y)
	MACROS	+=	D_USE_BACK_BUFFER=1

ifeq ($(G_TV_LIULINK_OSD_PORTRAIT), y)
	#### ����
	
	MACROS	+=	D_TV_LIULINK_OSD_PORTRAIT=1
	
	## Ĭ��������ת90
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
##        GUI��Դ�������          ##
##                                 ##
#####################################
##֧��JPEGͼ��
ifeq ($(G_GUI_SUPPORT_JPEG), y)
	MACROS	+= D_GUI_SUPPORT_JPEG=1
endif

##֧��PNGͼ��
ifeq ($(G_GUI_SUPPORT_PNG), y)
	MACROS	+=	D_GUI_SUPPORT_PNG=1
endif

##֧��freetype
ifeq ($(G_GUI_SUPPORT_FREETYPE), y)
	MACROS	+=	D_GUI_SUPPORT_FREETYPE=1
endif

##������չ�ֿ�GBK
ifeq ($(G_GUI_SUPPORT_GBK), y)
	MACROS	+=	D_GUI_SUPPORT_GBK=1
endif

##֧������������
ifeq ($(G_GUI_SUPPORT_SPEAKER), y)
	MACROS	+=	D_GUI_SUPPORT_SPEAKER=1
endif
#####################################
##                                 ##
##        CA��Դ�������           ##
##                                 ##
#####################################

#Ĭ��ca
MACROS		+= D_CA_SUPPORT_DEF=$(G_CA_SUPPORT_DEF)

#####################################
##                                 ##
##       ���ݿ���Դ�������        ##
##                                 ##
#####################################
ifeq ($(DVB_TYPE), dvbs)	
	MACROS		+= HI_SOFT_TYPE_DVBS=1
	MACROS		+= P_DBASE_DVBS=1			#DVBS���ݿ�
	MACROS		+= P_DB_MAX_ANTE_CNT=20		#���߸���	
	MACROS		+= P_DB_MAX_SAT_CNT=100		#���Ǹ���
	MACROS		+= P_DB_MAX_TS_CNT=504		#ת��������
	MACROS		+= P_DB_TEMP_TS_CNT=4		#��ʱת��������
	MACROS		+= P_CHECK_FRE_RANGE=3			#�ж��Ƿ���ͬһת����ʱ��Ƶ�ʵ�ƫ�Χ
	MACROS		+= P_CHECK_BAUD_RANGE=10		#�ж��Ƿ���ͬһת����ʱ�������ʵ�ƫ�Χ
	MACROS		+= P_DB_MAX_SRV_CNT=2010		#���ý�Ŀ��
	MACROS		+= P_DB_TEMP_SRV_CNT=10		#��ʱ��Ŀ��
	MACROS		+= P_DB_MAX_NET_CNT=32		#���������
endif

ifeq ($(DVB_TYPE), dtmb)
	MACROS		+= HI_SOFT_TYPE_DTMB=1
	MACROS		+= P_DBASE_DVBT=1			#DVBT���ݿ�
	MACROS		+= P_DB_MAX_ANTE_CNT=0
	MACROS		+= P_DB_MAX_SAT_CNT=0
ifeq ($(G_DDR_SIZE), 64M)
	MACROS		+= P_DB_MAX_TS_CNT=99		#ת��������	
	MACROS		+= P_DB_TEMP_TS_CNT=4		#��ʱת��������
	MACROS		+= P_DB_MAX_SRV_CNT=299		#���ý�Ŀ��
else
	MACROS		+= P_DB_MAX_TS_CNT=204		#ת��������	
	MACROS		+= P_DB_TEMP_TS_CNT=4		#��ʱת��������
	MACROS		+= P_DB_MAX_SRV_CNT=1010		#���ý�Ŀ��
endif
	MACROS		+= P_DB_TEMP_SRV_CNT=10		#��ʱ��Ŀ��
	MACROS		+= P_DB_MAX_NET_CNT=1		#������ʱֻ��һ��
endif

ifeq ($(DVB_TYPE), dvbc)
	MACROS		+= HI_SOFT_TYPE_DVBC=1
	MACROS		+= P_DBASE_DVBC=1			#DVBC���ݿ�
	MACROS		+= P_DB_MAX_ANTE_CNT=0
	MACROS		+= P_DB_MAX_SAT_CNT=0
	MACROS		+= P_DB_MAX_TS_CNT=204		#ת��������	
	MACROS		+= P_DB_TEMP_TS_CNT=4		#��ʱת��������	
	MACROS		+= P_DB_MAX_SRV_CNT=1010		#���ý�Ŀ��
	MACROS		+= P_DB_TEMP_SRV_CNT=10		#��ʱ��Ŀ��
	MACROS		+= P_DB_MAX_NET_CNT=1		#������ʱֻ��һ��
endif

ifeq ($(DVB_TYPE), dtmb_dvbc)
	MACROS		+= HI_SOFT_TYPE_DTMB_DVBC=1
	MACROS		+= P_DBASE_DVBC=1			#DVBC���ݿ�
	MACROS		+= P_DB_MAX_ANTE_CNT=0
	MACROS		+= P_DB_MAX_SAT_CNT=0
	MACROS		+= P_DB_MAX_TS_CNT=204		#ת��������	
	MACROS		+= P_DB_TEMP_TS_CNT=4		#��ʱת��������	
	MACROS		+= P_DB_MAX_SRV_CNT=1010		#���ý�Ŀ��
	MACROS		+= P_DB_TEMP_SRV_CNT=10		#��ʱ��Ŀ��
	MACROS		+= P_DB_MAX_NET_CNT=1		#������ʱֻ��һ��
endif
ifeq ($(G_AD_USE_EPG_MEM), y)
					MACROS		+= P_DB_MAX_EVT_CNT=0						#�¼�����
					MACROS		+= P_AD_USE_EPG_MEM=1													#���ڿռ����⣬������ʱ��ر�epg
endif	
ifneq ($(G_AD_USE_EPG_MEM), y)
MACROS		+= P_DB_MAX_EVT_CNT=$(G_DB_MAX_EVT_CNT)		#�¼�����
endif
MACROS		+= P_DB_MAX_BOUQ_CNT=$(G_DB_MAX_BOUQ_CNT)	#ҵ��Ⱥ��Ŀ

MACROS		+= P_DB_MAX_SUB_CNT=$(G_DB_MAX_SUB_CNT)		#ԤԼ��Ŀ����
MACROS		+= P_SUBSCRIBE_TIME=$(G_SUBSCRIBE_TIME) 	#�ж϶�ʱ���Ƿ�ʱʱʹ�ã���ǰ30�뵹��ʱ

MACROS		+= P_NVPART_TAIL_FLAG=$(G_NVPART_TAIL_FLAG)

MACROS		+= P_CONFIG_BLOCK_SIZE=$(G_CONFIG_BLOCK_SIZE)


#####################################
##                                 ##
##       UMT�����������        	 ##
##                                 ##
#####################################
##UMT��������
ifeq ($(G_UMT_TYPE), y)
	MACROS	+=	D_UMT_UP_DATA_TYPE=1
endif


#####################################
##                                 ##
##       ��ý���������            ##
##                                 ##
#####################################
##pvr�����Ƿ��(y/n)
ifeq ($(G_PVR_EN),y)
	MACROS		+= HI_P_PVR_EN=1
endif

ifeq ($(G_PVR_EN),n)
	MACROS		+= HI_P_PVR_EN=0
endif

##��ý�幦���Ƿ��(y/n)
ifeq ($(G_MUTIMEDIA_EN),y)
	MACROS		+= HI_P_MUTIMEDIA_EN=1
endif
ifeq ($(G_MUTIMEDIA_EN),n)
	MACROS		+= HI_P_MUTIMEDIA_EN=0
endif

##��ý���Ŀ¼�Ƿ��(y/n)
ifeq ($(G_MUTIMEDIA_NOCATALOG),y)
	MACROS		+= D_MUTIMEDIA_NOCATALOG=1
endif

#####################################
##                                 ##
##       DBG����������        	 ##
##                                 ##
#####################################
#Ĭ���������
ifeq ($(G_DBG_DISK_OPEN), y)
MACROS		+= D_DBG_DISK_OPEN=$(G_DBG_DISK_OPEN)
endif
######################################
##                                 ##
##       �����������        	     ##
##                                 ##
#####################################
##���ӹ����������(TV/TV_STB/STB)
ifeq ($(G_TV_SOFT_TYPE),TV)
	MACROS		+= HI_P_TV_TYPE_TV=1
endif	

ifeq ($(G_TV_SOFT_TYPE),TV_STB)
	MACROS		+= HI_P_TV_TYPE_TV_STB=1
endif	

##�����������ֺ͵�Ӱ�˵��Ƿ��(y/n)
ifeq ($(G_TV_MENU_SHOW_EN),y)
	MACROS		+= HI_P_TV_MENU_SHOW_EN=1
endif

ifeq ($(G_TV_MENU_SHOW_EN),n)
	MACROS		+= HI_P_TV_MENU_SHOW_EN=0
endif

#�ź�Դ��ʾ(AV1 AV2 HDMI1 HDMI2)
ifdef G_IUTPUT_SUPPORT_DEF
	MACROS	+=	$(patsubst %,D_IUTPUT_SUPPORT_%,$(G_IUTPUT_SUPPORT_DEF))
endif

##����DTVʱ�Ƿ�֧��PVR(y/n)
ifeq ($(G_TV_SUPPORT_PVR), y)
		MACROS	+=	D_TV_SUPPORT_PVR=1
endif

##�Ƿ���ͶӰ����Ŀ(y/n)
ifeq ($(G_TV_PEOJECT_TOUYY), y)
		MACROS	+=	D_TV_PEOJECT_TOUYY=1
endif

##�Ƿ�ͼ�������½ṹ�²˵�(y/n)
ifeq ($(G_TV_FC_IMAGE_SOURCE), y)
		MACROS	+=	D_TV_IAMGE_SOURCE=1
endif

##֧��tv_mini
ifeq ($(G_TV_UI_STYLE),MINI)
	MACROS	+= D_TV_UI_STYLE_MINI=1
endif

##�Ƿ��ൺ��������(y/n)
ifeq ($(G_TV_QINGDAO_HAIER_FUN),y)
	MACROS		+= HI_QINGDAO_HAIER_FUN=1
endif


##�Ƿ�֧��miracast(y/n)
ifeq ($(G_TV_MIRACAST_SOURCE), y)
	MACROS +=	D_TV_MIRACAST_SOURCE=1
	MACROS +=	D_TV_SUPPORT_WIFI=1
endif

##miracast �豸������
ifdef G_TV_MIRACAST_DEVNAME
	MACROS	+=	D_TV_MIRACAST_DEVNAME=$(G_TV_MIRACAST_DEVNAME)
endif

##�Ƿ�֧��dlna(y/n)
ifeq ($(G_TV_DLNA_SOURCE), y)
	MACROS +=	D_TV_DLNA_SOURCE=1
	MACROS +=	D_TV_SUPPORT_WIFI=1
endif

##dlna �豸������
ifdef G_TV_DLNA_DEVNAME
	MACROS	+=	D_TV_DLNA_DEVNAME=$(G_TV_DLNA_DEVNAME)
endif

##�Ƿ�֧��tsת��,��ts2net(y/n)
ifeq ($(G_TV_SUPPORT_TS2NET), y)
	MACROS +=	D_TV_SUPPORT_TS2NET=1
	MACROS +=	D_TV_SUPPORT_WIFI=1
endif

##ts2net �豸������
ifdef G_TV_TS2NET_DEVNAME
	MACROS	+=	D_TV_TS2NET_DEVNAME=$(G_TV_TS2NET_DEVNAME)
endif

##�Ƿ���iptv(y/n)
ifeq ($(G_TV_SUPPORT_IPTV),y)
	MACROS	+= D_TV_SUPPORT_IPTV=1
	MACROS +=	D_TV_SUPPORT_WIFI=1
endif

##�Ƿ���airplay(y/n)
ifeq ($(G_TV_SUPPORT_AIRPLAY),y)
	MACROS	+= D_TV_SUPPORT_AIRPLAY=1
	MACROS +=	D_TV_SUPPORT_WIFI=1
endif

##airplay �豸������
ifdef G_TV_AIRPLAY_DEVNAME
	MACROS	+=	D_TV_AIRPLAY_DEVNAME=$(G_TV_AIRPLAY_DEVNAME)
endif

#Ĭ��ca
MACROS		+= D_CA_SUPPORT_DEF=$(G_CA_SUPPORT_DEF)

#######################################
##                                 ##
##    �Ƿ���ypbpr �� ��Ƶ2    	   ##
##                                 ##
#####################################
##�Ƿ���ypbpr �� ��Ƶ2(y/n)
ifeq ($(G_TV_SIGNAL_SOURCE),y)
	MACROS	+= D_TV_SIGNAL_SOURCE=1
endif



###################################### �������################################################
ALL_DEF: all
-include  *.d

##ѡ�񹤾���
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

##��������
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
