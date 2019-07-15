#
##  Makefile
#
include $(PROJECT_CONFIG)

## 子目录
SUBDIRS	=

## 目标文件
OBJS	+= $(foreach f,$(SUBDIRS),$(f)/o_target.o)
OBJS	+=  patvMediaMainMenu.o patvMediaSetting.o patvMediaMusic.o patvMediaMovie.o patvMediaMovieFullScreen.o patvMediaPicture.o patvMediaPictureFullScreen.o patvMediaPictureFullMenu.o
OBJS  +=  patvMediaEbook.o  patvMediaEbkFullMenu.o  patvMediaTxtFullMenu.o patvMediaPrompt.o patvShowOsdMenu.o
OBJS  +=  patvMediaMovieInfoMenu.o

##ifeq ($(G_TV_SUPPORT_PVR), y)
	OBJS  += patvMediaPvr.o patvMediaPvrFullScreen.o patvMediaPvrRecord.o
##endif

##是否支持dlna(y/n)
ifeq ($(G_TV_DLNA_SOURCE), y)
	OBJS  += patvdlnawindow.o
endif

##是否支持airplay(y/n)
ifeq ($(G_TV_SUPPORT_AIRPLAY), y)
	OBJS  += patvairplaywindow.o
endif

## 生成库
O_TARGET	=	o_target.o

## 编译规则
include $(WORKROOT)/project/$(PROJECT)/make/project_rule.mk
