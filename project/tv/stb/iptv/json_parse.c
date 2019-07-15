#include "auth.h"

/********************************************************************/

/**
 * analyse request 1 body  
 */
gboolean _json_parse_request_one_body_info(Authenticator * auth, JsonData *jdata)
{
	JsonParser * parser = NULL;
	JsonNode * node = NULL;
	JsonObject * jobject = NULL;
	GError * error = NULL;
	char * ret = NULL;
	int value = 0;

	if(!auth || !jdata->data_body || jdata->length_body <=0)
		return FALSE;

	parser = json_parser_new();
	g_assert(parser != NULL);

	if(!json_parser_load_from_data(parser, jdata->data_body, jdata->length_body, &error)) {
		g_object_unref(parser);
		return FALSE;
	}

	node = json_parser_get_root(parser);
	if(!node) {
		g_object_unref(parser);
		return FALSE;
	}

	if(auth->authReply.code == 202)
	{
		jobject = json_node_get_object(node);
		ret = (char *)json_object_get_string_member(jobject, "api");
		if(auth->authReply.api_body)
			g_free(auth->authReply.api_body);
		auth->authReply.api_body = (char *)g_strdup(ret);

		ret = (char *)json_object_get_string_member(jobject, "snid");
		if(auth->authReply.snid_body)
			g_free(auth->authReply.snid_body);
		auth->authReply.snid_body	= (char *)g_strdup(ret);

		ret = (char *)json_object_get_string_member(jobject, "uid");
		if(auth->authReply.uid_body)
			g_free(auth->authReply.uid_body);
		auth->authReply.uid_body = (char *)g_strdup(ret);

		ret = (char *)json_object_get_string_member(jobject, "slt");
		if(auth->authReply.slt_body)
			g_free(auth->authReply.slt_body);
		auth->authReply.slt_body = (char *)g_strdup(ret);

		ret = (char *)json_object_get_string_member(jobject, "tid");
		if(auth->authReply.tid_body)
			g_free(auth->authReply.tid_body);
		auth->authReply.tid_body = (char *)g_strdup(ret);

		ret = (char *)json_object_get_string_member(jobject, "sid");
		if(auth->authReply.sid_body)
			g_free(auth->authReply.sid_body);
		auth->authReply.sid_body = (char *)g_strdup(ret);
	}
	else if(auth->authReply.code == 200)
	{
		jobject = json_node_get_object(node);

		if(json_object_has_member(jobject, "resInfo"))
		{
			JsonNode * jn = json_object_get_member(jobject, "resInfo");
			jobject = json_node_get_object(jn);

			value = json_object_get_int_member(jobject, "status");
			auth->authReply.resInfo.status = value;

			ret = (char *)json_object_get_string_member(jobject, "des");
			if(auth->authReply.resInfo.des)
				g_free(auth->authReply.resInfo.des);
			auth->authReply.resInfo.des = (char *)g_strdup(ret);
		}
		
		if(json_object_has_member(jobject, "userInfo"))
		{
			JsonNode * jn = json_object_get_member(jobject, "userInfo");
			jobject = json_node_get_object(jn);

			ret = (char *)json_object_get_string_member(jobject, "activeCode");
			if(auth->authReply.userInfo.activeCode)
				g_free(auth->authReply.userInfo.activeCode);
			auth->authReply.userInfo.activeCode = (char *)g_strdup(ret);
			
			value = json_object_get_int_member(jobject, "expireDay");
			auth->authReply.userInfo.expireDay = 30;

			ret = (char *)json_object_get_string_member(jobject, "activeTime");
			if(auth->authReply.userInfo.activeTime)
				g_free(auth->authReply.userInfo.activeTime);
			auth->authReply.userInfo.activeTime = (char *)g_strdup(ret);

			ret = (char *)json_object_get_string_member(jobject, "endTime");
			if(auth->authReply.userInfo.endTime)
				g_free(auth->authReply.userInfo.endTime);
			auth->authReply.userInfo.endTime = (char *)g_strdup(ret);
		}
	}
	else if(auth->authReply.code == 500)
	{
		jobject = json_node_get_object(node);

		if(json_object_has_member(jobject, "resInfo"))
		{
			JsonNode * jn = json_object_get_member(jobject, "resInfo");
			jobject = json_node_get_object(jn);

			value = json_object_get_int_member(jobject, "status");
			auth->authReply.resInfo.status = value;

			ret = (char *)json_object_get_string_member(jobject, "des");
			if(auth->authReply.resInfo.des)
				g_free(auth->authReply.resInfo.des);
			auth->authReply.resInfo.des = (char *)g_strdup(ret);
		}
	}
	
	return TRUE;
}

/**
 * analyse request 2 body  
 */
gboolean _json_parse_request_second_body_info(Authenticator * auth, JsonData *jdata)
{
	JsonParser * parser = NULL;
	JsonNode * node = NULL;
	JsonObject * jobject = NULL;
	GError * error = NULL;
	char * ret = NULL;
	int value = 0;

	if(!auth || !jdata->data_body || jdata->length_body <=0)
		return FALSE;

	parser = json_parser_new();
	g_assert(parser != NULL);

	if(!json_parser_load_from_data(parser, jdata->data_body, jdata->length_body, &error)) {
		g_object_unref(parser);
		return FALSE;
	}

	node = json_parser_get_root(parser);
	if(!node) {
		g_object_unref(parser);
		return FALSE;
	}

	if(auth->authReply.code == 202)
	{
		jobject = json_node_get_object(node);
		ret = (char *)json_object_get_string_member(jobject, "api");
		if(auth->authReply.api_body)
			g_free(auth->authReply.api_body);
		auth->authReply.api_body = (char *)g_strdup(ret);

		ret = (char *)json_object_get_string_member(jobject, "snid");
		if(auth->authReply.snid_body)
			g_free(auth->authReply.snid_body);
		auth->authReply.snid_body	= (char *)g_strdup(ret);

		ret = (char *)json_object_get_string_member(jobject, "uid");
		if(auth->authReply.uid_body)
			g_free(auth->authReply.uid_body);
		auth->authReply.uid_body = (char *)g_strdup(ret);

		ret = (char *)json_object_get_string_member(jobject, "slt");
		if(auth->authReply.slt_body)
			g_free(auth->authReply.slt_body);
		auth->authReply.slt_body = (char *)g_strdup(ret);

		ret = (char *)json_object_get_string_member(jobject, "tid");
		if(auth->authReply.tid_body)
			g_free(auth->authReply.tid_body);
		auth->authReply.tid_body = (char *)g_strdup(ret);

		ret = (char *)json_object_get_string_member(jobject, "sid");
		if(auth->authReply.sid_body)
			g_free(auth->authReply.sid_body);
		auth->authReply.sid_body = (char *)g_strdup(ret);
	}
	else if(auth->authReply.code == 403)
	{
		jobject = json_node_get_object(node);

		if(json_object_has_member(jobject, "resInfo"))
		{
			JsonNode * jn = json_object_get_member(jobject, "resInfo");
			jobject = json_node_get_object(jn);

			value = json_object_get_int_member(jobject, "status");
			auth->authReply.resInfo.status = value;

			ret = (char *)json_object_get_string_member(jobject, "des");
			if(auth->authReply.resInfo.des)
				g_free(auth->authReply.resInfo.des);
			auth->authReply.resInfo.des = (char *)g_strdup(ret);
		}
	}
	
	return TRUE;
}

/**
 * analyse request 3 body  
 */
gboolean _json_parse_request_third_body_info(Authenticator * auth, JsonData *jdata)
{
	JsonParser * parser = NULL;
	JsonNode * node = NULL;
	JsonObject * jobject = NULL;
	GError * error = NULL;
	char * ret = NULL;
	int value = 0;

	if(!auth || !jdata->data_body || jdata->length_body <=0)
		return FALSE;

	parser = json_parser_new();
	g_assert(parser != NULL);

	if(!json_parser_load_from_data(parser, jdata->data_body, jdata->length_body, &error)) {
		g_object_unref(parser);
		return FALSE;
	}

	node = json_parser_get_root(parser);
	if(!node) {
		g_object_unref(parser);
		return FALSE;
	}

	if(auth->authReply.code == 200)
	{
		jobject = json_node_get_object(node);

		if(json_object_has_member(jobject, "resInfo"))
		{
			JsonNode * jn = json_object_get_member(jobject, "resInfo");
			jobject = json_node_get_object(jn);

			value = json_object_get_int_member(jobject, "status");
			auth->authReply.resInfo.status = value;

			ret = (char *)json_object_get_string_member(jobject, "des");
			if(auth->authReply.resInfo.des)
				g_free(auth->authReply.resInfo.des);
			auth->authReply.resInfo.des = (char *)g_strdup(ret);
		}
		
		if(json_object_has_member(jobject, "userInfo"))
		{
			JsonNode * jn = json_object_get_member(jobject, "userInfo");
			jobject = json_node_get_object(jn);

			ret = (char *)json_object_get_string_member(jobject, "regTime");
			if(auth->authReply.userInfo.regTime)
				g_free(auth->authReply.userInfo.regTime);
			auth->authReply.userInfo.regTime = (char *)g_strdup(ret);
			
			ret = (char *)json_object_get_string_member(jobject, "endTime");
			if(auth->authReply.userInfo.endTime)
				g_free(auth->authReply.userInfo.endTime);
			auth->authReply.userInfo.endTime = (char *)g_strdup(ret);
			
			ret = (char *)json_object_get_string_member(jobject, "subscriberId");
			if(auth->authReply.userInfo.subscriberId)
				g_free(auth->authReply.userInfo.subscriberId);
			auth->authReply.userInfo.subscriberId = (char *)g_strdup(ret);
			
			ret = (char *)json_object_get_string_member(jobject, "activecode");
			if(auth->authReply.userInfo.activeCode)
				g_free(auth->authReply.userInfo.activeCode);
			auth->authReply.userInfo.activeCode = (char *)g_strdup(ret);
			
			value = json_object_get_int_member(jobject, "expireDay");
			auth->authReply.userInfo.expireDay = 30;

			ret = (char *)json_object_get_string_member(jobject, "produceId");
			if(auth->authReply.userInfo.produceId)
				g_free(auth->authReply.userInfo.produceId);
			auth->authReply.userInfo.produceId = (char *)g_strdup(ret);
		}
	}
	else if(auth->authReply.code == 403)
	{
		jobject = json_node_get_object(node);

		if(json_object_has_member(jobject, "resInfo"))
		{
			JsonNode * jn = json_object_get_member(jobject, "resInfo");
			jobject = json_node_get_object(jn);

			value = json_object_get_int_member(jobject, "status");
			auth->authReply.resInfo.status = value;

			ret = (char *)json_object_get_string_member(jobject, "des");
			if(auth->authReply.resInfo.des)
				g_free(auth->authReply.resInfo.des);
			auth->authReply.resInfo.des = (char *)g_strdup(ret);
		}
	}
	
	return TRUE;
}

/**
 * analyse cur stb info body  
 */
gboolean _json_parse_cur_stb_info(Authenticator * auth, JsonData *jdata)
{
	JsonParser * parser = NULL;
	JsonNode * node = NULL;
	JsonObject * jobject = NULL;
	GError * error = NULL;
	char * ret = NULL;
	int value = 0;

	if(!auth || !jdata->data_body || jdata->length_body <=0)
		return FALSE;

	parser = json_parser_new();
	g_assert(parser != NULL);

	if(!json_parser_load_from_data(parser, jdata->data_body, jdata->length_body, &error)) {
		g_object_unref(parser);
		return FALSE;
	}

	node = json_parser_get_root(parser);
	if(!node) {
		g_object_unref(parser);
		return FALSE;
	}

	if(auth->authReply.code == 200)
	{
		jobject = json_node_get_object(node);

		if(json_object_has_member(jobject, "resInfo"))
		{
			JsonNode * jn = json_object_get_member(jobject, "resInfo");
			jobject = json_node_get_object(jn);

			value = json_object_get_int_member(jobject, "status");
			auth->authReply.resInfo.status = value;

			ret = (char *)json_object_get_string_member(jobject, "des");
			if(auth->authReply.resInfo.des)
				g_free(auth->authReply.resInfo.des);
			auth->authReply.resInfo.des = (char *)g_strdup(ret);
		}
		
		ret = (char *)json_object_get_string_member(jobject, "subscriberId");
		if(auth->authReply.userInfo.subscriberId)
			g_free(auth->authReply.userInfo.subscriberId);
		auth->authReply.userInfo.subscriberId = (char *)g_strdup(ret);

		ret = (char *)json_object_get_string_member(jobject, "activeCode");
		if(auth->authReply.userInfo.activeCode)
			g_free(auth->authReply.userInfo.activeCode);
		auth->authReply.userInfo.activeCode = (char *)g_strdup(ret);

		ret = (char *)json_object_get_string_member(jobject, "numberDay");
		if(auth->authReply.userInfo.numberDay)
			g_free(auth->authReply.userInfo.numberDay);
		auth->authReply.userInfo.numberDay = (char *)g_strdup(ret);
	}
	
	return TRUE;
}

/**
 * analyse login info
 */
gboolean _json_parse_login_info(Authenticator * auth, JsonData *jdata)
{
	JsonParser * parser;
	JsonNode * node;
	JsonObject * jobject;
	GError * error;
	
	int i = 0;
	int value = 0;
	char * ret = NULL;
	const char  str_ru[] = "Russian";
	const char  str_uk[] = "Ukriane";
	char tmp_param[32];
	

	if(!auth || !jdata || jdata->length_body <=0)
		return FALSE;

	parser = json_parser_new();
	g_assert(parser != NULL);

	if(!json_parser_load_from_data(parser, jdata->data_body, jdata->length_body, &error)) {
		g_object_unref(parser);
		return FALSE;
	}

	node = json_parser_get_root(parser);
	if(!node) {
		g_object_unref(parser);
		return FALSE;
	}

	jobject = json_node_get_object(node);
	
	if(json_object_has_member(jobject, "category"))
	{
		JsonArray * ja = json_object_get_array_member(jobject, "category");
		g_assert(ja != NULL);
		SEE("%d", json_array_get_length(ja));
	
		if(auth->authReply.category_list && g_slist_length(auth->authReply.category_list) > 0)
		{
			g_slist_free(auth->authReply.category_list);
			auth->authReply.category_list = NULL;
		}

		for(i = 0; i < json_array_get_length(ja); ++i)
		{
			ProgramCategory *table = g_new0(ProgramCategory, 1);
			JsonNode * jn = json_array_get_element(ja, i);
			g_assert(jn != NULL);
			
			jobject = json_node_get_object(jn);
			
			table->tag = g_strdup(json_object_get_string_member(jobject, "tag"));
			//SEE("%s\n", table->tag);
			table->title = g_strdup(json_object_get_string_member(jobject, "title"));
			//SEE("%s\n", table->title);
			if(!memcmp(table->tag, str_ru, 6) || !memcmp(table->title, str_uk, 6)  || !memcmp(table->tag, str_ru, 6) || !memcmp(table->title, str_uk, 6) )
			{
				g_free(table);
				SEE("%s\n", str_ru);
				continue;
				
			}
		
			table->parentId = json_object_get_int_member(jobject, "parentId");
			
			table->icon = g_strdup(json_object_get_string_member(jobject, "icon"));
			
			table->type = json_object_get_int_member(jobject, "type");
			
			table->parentName = strdup(json_object_get_string_member(jobject, "parentName"));
			//SEE("%s\n", table->parentName);
			
			table->parentOrder = json_object_get_int_member(jobject, "parentOrder");
			
			table->categoryId = json_object_get_int_member(jobject, "categoryId");
			
			table->order = json_object_get_int_member(jobject, "order");

			auth->authReply.category_list = g_slist_append(auth->authReply.category_list, table);
		}
	}

	return TRUE;
}

/**
 * analyse login info
 */
gboolean _json_parse_channels_info(char * filename, Authenticator * auth)
{
	int i = 0;

	JsonParser * parser;
	JsonNode * node;
	JsonObject * jobject;
	JsonObject * jobject1;
	GError * error;

	JsonArray * array;
	GList * jnodes;

	parser = json_parser_new();
	
	if(!json_parser_load_from_file(parser, filename, &error)) {
		g_object_unref(parser);
		return;
	}

	node = json_parser_get_root(parser);

	if(!node) {
		MSG("\n");
		g_object_unref(parser);
		return;
	}

	jobject = json_node_get_object(node);

	if(json_object_has_member(jobject, "programs"))
	{
		JsonArray * ja1 = json_object_get_array_member(jobject, "programs");
		SEE("%d", json_array_get_length(ja1));

		i = 0;
		JsonNode * jn1 = json_array_get_element(ja1, i);
		jobject = json_node_get_object(jn1);

		if(json_object_has_member(jobject, "program"))
		{
			JsonArray * ja2 = json_object_get_array_member(jobject, "program");
			SEE("%d", json_array_get_length(ja2));

			if(auth->authReply.program_list && g_slist_length(auth->authReply.program_list) > 0)
			{
				g_slist_free(auth->authReply.program_list);
				auth->authReply.program_list = NULL;
			}

			for(i = 0; i < json_array_get_length(ja2); ++i)
			{
				ProgramUrl *table1 = g_new0(ProgramUrl, 1);
				JsonNode * jn2 = json_array_get_element(ja2, i);

				jobject = json_node_get_object(jn2);

				table1->name = g_strdup((char *)json_object_get_string_member(jobject, "programName"));
				SEE("%s", table1->name);

				if(json_object_has_member(jobject, "channels"))
				{
					JsonArray * ja3 = json_object_get_array_member(jobject, "channels");

					JsonNode * jn3 = json_array_get_element(ja3, 0);
					jobject1 = json_node_get_object(jn3);

					table1->url = g_strdup((char *)json_object_get_string_member(jobject1, "playUrl"));
					SEE("%s", table1->url);
				}
				
				auth->authReply.program_list = g_slist_append(auth->authReply.program_list, table1);
			
			}	
		}
	}
	
}
