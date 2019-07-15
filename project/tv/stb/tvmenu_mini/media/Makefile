#
##  Makefile
#
include $(PROJECT_CONFIG)

## 子目录
SUBDIRS	=

## 目标文件
OBJS	+= $(foreach f,$(SUBDIRS),$(f)/o_target.o)
OBJS	+= patvMediaMainMenu.o patvMediaSetting.o  patvMediaPictureFullMenu.o patvMediaEbookList.o patvMediaEbook.o patvMediaTxtFullMenu.o
OBJS  += patvMediaPrompt.o patvShowOsdMenu.o patvMediaMovieInfoMenu.o patvMediaPvrList.o patvMediaPvrFullScreen.o patvMediaPvrRecord.o 

ifneq ($(G_MUTIMEDIA_NOCATALOG),y)
	OBJS	+= patvMediaMuiseList.o patvMediaPicList.o patvMediaMovieList.o 
	OBJS  += patvMediaMovieFullScreen.o  patvMediaPictureFullScreen.o
endif
ifeq ($(G_MUTIMEDIA_NOCATALOG),y)
	OBJS	+= patvMediaMuiseList_nocatalog.o patvMediaMovieList_nocatalog.o patvMediaMovieFullScreen_nocatalog.o 
	OBJS  += patvMediaPicList_nocataiog.o patvMediaPictureFullScreen_nocatalog.o
endif	

##OBJS  +=  patvMediaEbook.o  patvMediaEbkFullMenu.o  patvMediaTxtFullMenu.o  
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
