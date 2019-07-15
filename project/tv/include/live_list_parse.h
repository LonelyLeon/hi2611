#ifndef __iptv_list_parse_H__
#define __iptv_list_parse_H__

#include <glib.h>

#define IPTV_LIVE_FILE		"/tmp/tvlist-iptv.xml"
	
typedef struct RealPlayTvlink RealPlayTvlink;
struct RealPlayTvlink {
	char * link;
	char * source;
};

typedef struct RealPlayChannel RealPlayChannel;
struct RealPlayChannel {
	gint channel_num;
	char * name;
	GList * tvlink;
	gint total;
	gint cid;
	gint id;
	gint qid;
	gint curlink;

//	ShortEpg* short_epg;
	int epgDate;	///<epg日期
	GList *epgs;
};

typedef struct RealPlayBlock RealPlayBlock;
struct RealPlayBlock {
	char * name;
	GList * channel;
	gint total;
	gint id;
	gint qid;
	gint flag;

	char * listUrl;
};

#endif
