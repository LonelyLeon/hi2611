#ifndef __AUTHENTICATION_H__
#define __AUTHENTICATION_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <libsoup/soup.h>
#include <htk/htk.h>
#include <json-glib/json-glib.h>

#include <libconfig.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <pthread.h>

#include "_helper.h"

#define	 QUERY_URL	"http://emsl1.tvhome.info:12004/v1/b"
#define  FirstRequest_URL "http://emsl1.tvhome.info:12004/v4/sunplus/q" 
#define  Login_URL "http://emsl1.tvhome.info:12004/v4/sunplus/c" 
#define  EPG_URL "http://emsl1.tvhome.info:12004/v4/sunplus/p" 

typedef struct res_info ResInfo;
struct res_info
{
	int status;//or code
	char *des;
};

typedef struct user_info UserInfo;
struct user_info 
{
	char *activeCode;
	int	expireDay;
	char *activeTime;
	char *endTime;

	char *regTime;
//	char *endTime;
	char *subscriberId;
//	char *activecode;
//	char *expireDay;
	char *produceId;

	char *numberDay;
};

typedef struct program_category ProgramCategory; 
struct program_category
{
	char *tag;
	char *title;
	int	parentId;
	char *icon;
	int type;
	char *parentName;
	int parentOrder;
	int categoryId;
	int order;
};

typedef struct program_url ProgramUrl; 
struct program_url
{
	char *name;
	char *url;
};

enum AUTH_STATUS
{
	STATUS_DEFAULT,

	REGISTER_ONE_OK_SUCCESS,			//202
	REGISTER_REQUEST_RENEW_OR_REPLACE,	//200
	REGISTER_ONE_PARAM_ERROR,			//500
	REGISTER_ONE_SNID_NOT_EXIST,		//401
	REGISTER_ONE_SUB_ID_NOT_EXIST,		//400
	REGISTER_ONE_SUB_ID_EXPIRED,		//410
	REGISTER_ONE_SUB_ID_CANNOT_USE,		//412
	REGISTER_ONE_ACTIVE_CODE_NOT_EXIST,	//406
	REGISTER_ONE_ACTIVE_CODE_USED,		//405
	REGISTER_ONE_OTHER_ERROR,			//403
	REGISTER_ONE_ACTIVE_CODE_NOT_MATCH,	//409
	REGISTER_ONE_CLIENT_INFO_ERROR,		//411
	REGISTER_ONE_AUT_ERROR,				//501

	REGISTER_SECOND_OK_NEXT,			//202
	REGISTER_SECOND_PARAM_ERROR,		//403
	REGISTER_SECOND_OTHER_ERROR,		//500
	REGISTER_SECOND_SN_INVALID,			//401
	REGISTER_SECOND_SN_REGISTERED,		//408
	REGISTER_SECOND_AUT_ERROR,			//501

	REGISTER_THIRED_REGISTERED_SUCCESS,	//200
	REGISTER_THIRED_PARAM_ERROR,		//403 500
	REGISTER_THIRED_SN_INVALID,			//401
	REGISTER_THIRED_SN_REGISTERED,		//408
	REGISTER_THIRED_ACTIVE_CODE_USED,	//405
	REGISTER_THIRED_ACTIVE_CODE_INVALID,//406
	REGISTER_THIRED_HID_EXIST,			//407
	REGISTER_THIRED_NOT_MATCH,			//409
	REGISTER_THIRED_CLIENT_INFO_ERROR,	//411
	REGISTER_THIRED_AUT_ERROR,			//501
	
	REGISTER_ERROR,
	
	REGISTER_SUCESS_READY_FOR_LOGIN,

	DATA_ERROR,

	BACK_USER_SUCCESS,
	BACK_USER_FAILED,
	BACK_USER_FAILED_NEED_ACTIVE,

	LOGIN_GET_EPG_SUCCESS,
	LOGIN_GET_EPG_FAILED,
	
	LOGIN_GET_EPG_EXPIRED,
	
	LOGIN_GET_EPG_PROGRAM_SUCCESS,
	LOGIN_GET_EPG_PROGRAM_FAILED,
	WIFI_ERROR,
	STATUS_MAX
};

enum  API_REQUEST
{
	NO_REQUEST,
	
	REQUEST_START,
	REQUEST_REGISTER,
	REQUEST_EPG,
	REQUEST_LOGIN
};

typedef struct auth_reply AuthReply; 
struct auth_reply 
{
	int code;
	enum AUTH_STATUS status;
	
	char *hid_header;
	char *tid_header;
	char *stp_header;
	char *slt_header;
	char *sid_header;
	char *server_header;
	char *aut_header;

	char *api_body;
	char *snid_body;
	char *uid_body;
	char *slt_body;
	char *tid_body;
	char *sid_body;

	ResInfo resInfo;
	UserInfo userInfo;

	//节目分类信息
	GList * category_list;
	//节目信息
	GList * program_list;
};

typedef struct authenticator Authenticator;
struct authenticator 
{
	char * Random;
	char * UserToken;
	char * MAC;
	char * Base58_mac;
	char * Base58_activecode;
	int status; //当前的状态
	int cur_api; //当前的状态

	SoupSession * session;
	//FunXmlCb xmlCb;

	AuthReply authReply;
};

typedef struct jsonData JsonData;
struct jsonData 
{
	int length_headers;
	char * data_headers;
	
	int length_body;
	char * data_body;
};

Authenticator * OTT_new_authentication(void);
Authenticator * OTT_get_default_auth(void);

/*初始化查询本机信息，登录或者注册*/
void OTT_auth_init();
void OTT_auth_uninit();

/*获取全局变量*/
void OTT_set_default_auth(Authenticator * auth);

/*获取当前节目分类的节目表
 * param 1: 类别序列号
 */
int OTT_auth_get_cur_epg(int id);

/*注册
 * param 1: 激活码
 */
int OTT_start_register(char *active_code);

/*login
 */
int OTT_start_login();

gboolean _json_parse_request_one_body_info(Authenticator * auth, JsonData *jdata);
gboolean _json_parse_request_second_body_info(Authenticator * auth, JsonData *jdata);
gboolean _json_parse_request_third_body_info(Authenticator * auth, JsonData *jdata);

void _iptv_start_play(int id);
void _iptv_stop_play();

char *_get_mac();

#endif
