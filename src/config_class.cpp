#include <config_class.h>

config_c::config_c(char *file_name, char *encoding)
{
	if (file_name == NULL || strlen(file_name) < 1 || strlen(file_name) >= MAX_PATH_LENGTH)
	{
		g_log->crit_stream()<<"no configure file!";
		exit(-1);
	}
	
	memset(xml_file, 0, sizeof(xml_file));
	strncpy(xml_file, file_name, sizeof(xml_file) - 1);
	memset(xml_encoding, 0, sizeof(xml_encoding));
	strncpy(xml_encoding, encoding, sizeof(xml_encoding));
	memset(gu_data_path, 0, sizeof(gu_data_path));
	memset(du_data_path, 0, sizeof(du_data_path));
	memset(du_conf, 0, sizeof(du_conf));
	memset(du_xml, 0, sizeof(du_xml));
	memset(data_douban, 0, sizeof(data_douban));
	memset(data_m1905, 0, sizeof(data_m1905));
	memset(data_sohu, 0, sizeof(data_sohu));
	memset(data_qvod, 0, sizeof(data_qvod));
	memset(data_kankan, 0, sizeof(data_kankan));
	memset(data_pptv, 0, sizeof(data_pptv));
	memset(data_cntv, 0, sizeof(data_cntv));
	memset(data_ku6, 0, sizeof(data_ku6));
	memset(data_baomihua, 0, sizeof(data_baomihua));
	memset(data_taomee, 0, sizeof(data_taomee));
	memset(data_douban_2, 0, sizeof(data_douban_2));
}

config_c::~config_c()
{
	
}

bool config_c::config_set_str(xml_node_ptr node, char *str)
{
	if (node == NULL || str == NULL)
	{
		g_log->crit_stream()<<ERROR_HEAD<<"paragram is NULL";
		return false;
	}
	
	char *data = xml_c::xml_node_value(node);
	if (data == NULL || strlen(data) < 1)
	{
		g_log->crit_stream()<<ERROR_HEAD<<"data is NULL";
		return false;
	}
	
	strcpy(str, data);
	
	return true;
}
bool config_c::config_set_uint8(xml_node_ptr node, uint8 *conf_i)
{
	if (node == NULL || conf_i == NULL)
	{
		g_log->crit_stream()<<ERROR_HEAD<<"paragram is NULL";
		return false;
	}
	
	char *data = xml_c::xml_node_value(node);
	if (data == NULL || strlen(data) < 1)
	{
		g_log->crit_stream()<<ERROR_HEAD<<"data is NULL";
		return false;
	}
	
	int tmp = atoi(data);
	
	*conf_i = (uint8)tmp;
	return true;
}
bool config_c::config_set_uint16(xml_node_ptr node, uint16 *conf_i)
{
	
	if (node == NULL || conf_i == NULL)
	{
		g_log->crit_stream()<<ERROR_HEAD<<"paragram is NULL";
		return false;
	}
	
	char *data = xml_c::xml_node_value(node);
	if (data == NULL || strlen(data) < 1)
	{
		g_log->crit_stream()<<ERROR_HEAD<<"data is NULL";
		return false;
	}
	
	int tmp = atoi(data);
	*conf_i = (uint16)tmp;
	return true;
}
bool config_c::config_set_uint32(xml_node_ptr node, uint32 *conf_i)
{
	if (node == NULL || conf_i == NULL)
	{
		g_log->crit_stream()<<ERROR_HEAD<<"paragram is NULL";
		return false;
	}
	
	char *data = xml_c::xml_node_value(node);
	if (data == NULL || strlen(data) < 1)
	{
		g_log->crit_stream()<<ERROR_HEAD<<"data is NULL";
		return false;
	}
	
	int tmp = atoi(data);
	*conf_i = (uint32)tmp;
	return true;
}
bool config_c::config_set_uint64(xml_node_ptr node, uint64 *conf_i)
{
	if (node == NULL || conf_i == NULL)
	{
		g_log->crit_stream()<<ERROR_HEAD<<"paragram is NULL";
		return false;
	}
	
	char *data = xml_c::xml_node_value(node);
	if (data == NULL || strlen(data) < 1)
	{
		g_log->crit_stream()<<ERROR_HEAD<<"data is NULL";
		return false;
	}
	
	int tmp = atoi(data);
	*conf_i = (uint64)tmp;
	return true;
}

bool config_c::config_get()
{
	xml_ptr doc_ptr = new xml_c(xml_file, xml_encoding);
	NEW_CHECK(doc_ptr);
	if (!doc_ptr->xml_load_file())
	{
		g_log->crit_stream()<<ERROR_HEAD<<"load_file fail";
		return false;
	}
	
	xml_node_ptr node = doc_ptr->xml_root_node();
	if (node == NULL)
	{
		g_log->crit_stream()<<ERROR_HEAD<<"no root node";
		return false;
	}
	
	if (!config_set_node_str(node, "gu_data_path", gu_data_path))
	{
		g_log->crit_stream()<<ERROR_HEAD<<"no gu_data_path";
		exit(-1);
	}
	
	if (!config_set_node_str(node, "du_data_path", du_data_path))
	{
		g_log->crit_stream()<<ERROR_HEAD<<"no du_data_path";
		exit(-1);
	}
	
	if (!config_set_node_str(node, "du_conf", du_conf))
	{
		g_log->crit_stream()<<ERROR_HEAD<<"no du_conf";
		exit(-1);
	}
	
	if (!config_set_node_str(node, "du_xml", du_xml))
	{
		g_log->crit_stream()<<ERROR_HEAD<<"no du_xml";
		exit(-1);
	}
	
	config_set_node_str(node, "data_douban", data_douban);
	config_set_node_str(node, "data_m1905", data_m1905);
	config_set_node_str(node, "data_sohu", data_sohu);
	config_set_node_str(node, "data_qvod", data_qvod);
	config_set_node_str(node, "data_kankan", data_kankan);
	config_set_node_str(node, "data_pptv", data_pptv);
	config_set_node_str(node, "data_cntv", data_cntv);
	config_set_node_str(node, "data_ku6", data_ku6);
	config_set_node_str(node, "data_baomihua", data_baomihua);
	config_set_node_str(node, "data_taomee", data_taomee);
	config_set_node_str(node, "data_douban_2", data_douban_2);
	return true;
}
bool config_c::config_print()
{
	g_log->crit_stream()<<"gu_data_path is "<<gu_data_path;
	g_log->crit_stream()<<"du_data_path is "<<du_data_path;
	g_log->crit_stream()<<"du_conf is "<<du_conf;
	g_log->crit_stream()<<"du_xml is "<<du_xml;
	g_log->crit_stream()<<"data_douban is "<<data_douban;
	g_log->crit_stream()<<"data_m1905 is "<<data_m1905;
	g_log->crit_stream()<<"data_sohu is "<<data_sohu;
	g_log->crit_stream()<<"data_qvod is "<<data_qvod;
	g_log->crit_stream()<<"data_kankan is "<<data_kankan;
	g_log->crit_stream()<<"data_pptv is "<<data_pptv;
	g_log->crit_stream()<<"data_cntv is "<<data_cntv;
	g_log->crit_stream()<<"data_ku6 is "<<data_ku6;
	g_log->crit_stream()<<"data_baomihua is "<<data_baomihua;
	g_log->crit_stream()<<"data_taomee is "<<data_taomee;
	g_log->crit_stream()<<"data_douban_2 is "<<data_douban_2;
	
	return true;
}

bool config_c::config_set_node_str(xml_node_ptr node, char *tag, char *str)
{
	if (node == NULL || tag == NULL || str == NULL)
	{
		g_log->crit_stream()<<ERROR_HEAD<<"paragram is NULL";
		return  false;
	}
	
	xml_node_ptr cur_node = xml_c::xml_search_node(node, tag);
	if (cur_node == NULL)
	{
		g_log->crit_stream()<<ERROR_HEAD<<"no tag "<<tag;
		return false;
	}
	
	return config_set_str(cur_node, str);
}

