#include <handle_qq.h>
#include <regular.h>
#include <global.h>

handle_qq::handle_qq(xml_write_ptr ptr)
{
	m_write_xml = ptr;
}

handle_qq::~handle_qq()
{
	m_write_xml = NULL;
}


bool handle_qq::handle_movie(char *url, html_ptr ptr)
{
	if (ptr == NULL)
	{
		return false;
	}
	
	// 解析国家地区
	html_node_ptr node = ptr->html_xpath_node("/html/body/div[3]/div/div/div[2]/ul/li[3]/span/a");
	if (node != NULL)
	{
		m_write_xml->write_countries(ptr->html_node_value(node));
	}
	
	// 解析导演
	int i = 0;
	bool is_first = true;
	char type_tmp[800] = { 0 };
	for (i = 0; i < 1000; i++)
	{
		char tmp[500] = { 0 };
		snprintf(tmp, sizeof(tmp) - 1, "/html/body/div[3]/div/div/div[2]/ul/li/div/a[%d]", i + 1);
		if ((node = ptr->html_xpath_node(tmp)) != NULL)
		{
			if (!is_first)
			{
				snprintf(type_tmp + strlen(type_tmp), sizeof(type_tmp) - strlen(type_tmp) - 1, "/");
			}
			snprintf(type_tmp + strlen(type_tmp), sizeof(type_tmp) - strlen(type_tmp) - 1, "%s", 
					ptr->html_node_value(node));
			is_first = false;
		}
		else
		{
			break;
		}
	}
	m_write_xml->write_director(type_tmp);
	
	// 解析演员
	is_first = true;
	memset(type_tmp, 0, sizeof(type_tmp));
	for ( i = 0; i < 1000; i++)
	{
		char tmp[500] = { 0 };
		snprintf(tmp, sizeof(tmp) - 1, "/html/body/div[3]/div/div/div[2]/ul/li[2]/div/a[%d]",
					i + 1);
		if ((node = ptr->html_xpath_node(tmp)) != NULL)
		{
			if (!is_first)
			{
				snprintf(type_tmp + strlen(type_tmp), sizeof(type_tmp) - strlen(type_tmp) - 1, "/");
			}
			
			snprintf(type_tmp + strlen(type_tmp), sizeof(type_tmp) - strlen(type_tmp) - 1, "%s",
					ptr->html_node_value(node));
			is_first = false;
		}
		else
		{
			break;
		}
	}
	m_write_xml->write_actor(type_tmp);
	
	// 解析类型
	is_first = true;
	memset(type_tmp, 0, sizeof(type_tmp));
	for (i = 0; i < 1000; i++)
	{
		char tmp[500] = { 0 };
		snprintf(tmp, sizeof(tmp) - 1, "/html/body/div[3]/div/div/div[2]/ul/li[3]/span[2]/a[%d]",
			i + 1);
		if ((node = ptr->html_xpath_node(tmp)) != NULL)
		{
			if (!is_first)
			{
				snprintf(type_tmp + strlen(type_tmp), sizeof(type_tmp) - strlen(type_tmp) - 1, "/");
			}
			
			snprintf(type_tmp + strlen(type_tmp), sizeof(type_tmp) - strlen(type_tmp) - 1, "%s",
					ptr->html_node_value(node));
			is_first = false;
		}
		else
		{
			break;
		}
	}
	m_write_xml->write_type(type_tmp);
	
	if ((node = ptr->html_xpath_node("/html/body/div[3]/div/div/div[2]/ul/li[4]/span/a")) != NULL)
	{
		m_write_xml->write_release_time(ptr->html_node_value(node));
	}
	
	if ((node = ptr->html_xpath_node("/html/body/div[3]/div/div/div[2]/ul/li[4]/span[2]")) != NULL)
	{
		m_write_xml->write_duration(ptr->html_node_value(node));
	}
	
	if ((node = ptr->html_xpath_node("//*[@id=\"mod_viewcount_total\"]")) != NULL)
	{
		m_write_xml->write_views(ptr->html_node_value(node));
	}
	
	if ((node = ptr->html_xpath_node("/html/body/div[3]/div/div/div[2]/div/p")) != NULL)
	{
		m_write_xml->write_description(ptr->html_node_value(node));
	}
	
	if ((node = ptr->html_xpath_node("//*[@id=\"img_cover_pic\"]")) != NULL)
	{
		m_write_xml->write_post(ptr->html_node_prop(node, "src"));
	}
	
	if ((node = ptr->html_xpath_node("/html/body/div[3]/div/div/div[2]/div[3]/a")) != NULL)
	{
		m_write_xml->write_seri_begin();
		m_write_xml->write_seri("1", ptr->html_node_prop(node, "href"), NULL);
		m_write_xml->write_seri_end();
	}
	
	m_write_xml->write_end();
	return true;
}

bool handle_qq::handle_tv(char *url, html_ptr ptr)
{
	if (ptr == NULL)
	{
		return false;
	}
	
	// 解析国家地区
	html_node_ptr node = ptr->html_xpath_node("/html/body/div[3]/div/div/div[2]/ul/li[3]/span/a");
	if (node != NULL)
	{
		m_write_xml->write_countries(ptr->html_node_value(node));
	}
	
	// 解析导演
	int i = 0;
	bool is_first = true;
	char type_tmp[800] = { 0 };
	for (i = 0; i < 1000; i++)
	{
		char tmp[500] = { 0 };
		snprintf(tmp, sizeof(tmp) - 1, "/html/body/div[3]/div/div/div[2]/ul/li/div/a[%d]", i + 1);
		if ((node = ptr->html_xpath_node(tmp)) != NULL)
		{
			if (!is_first)
			{
				snprintf(type_tmp + strlen(type_tmp), sizeof(type_tmp) - strlen(type_tmp) - 1, "/");
			}
			snprintf(type_tmp + strlen(type_tmp), sizeof(type_tmp) - strlen(type_tmp) - 1, "%s", 
					ptr->html_node_value(node));
			is_first = false;
		}
		else
		{
			break;
		}
	}
	m_write_xml->write_director(type_tmp);
	
	// 解析演员
	is_first = true;
	memset(type_tmp, 0, sizeof(type_tmp));
	for ( i = 0; i < 1000; i++)
	{
		char tmp[500] = { 0 };
		snprintf(tmp, sizeof(tmp) - 1, "/html/body/div[3]/div/div/div[2]/ul/li[2]/div/a[%d]",
					i + 1);
		if ((node = ptr->html_xpath_node(tmp)) != NULL)
		{
			if (!is_first)
			{
				snprintf(type_tmp + strlen(type_tmp), sizeof(type_tmp) - strlen(type_tmp) - 1, "/");
			}
			
			snprintf(type_tmp + strlen(type_tmp), sizeof(type_tmp) - strlen(type_tmp) - 1, "%s",
					ptr->html_node_value(node));
			is_first = false;
		}
		else
		{
			break;
		}
	}
	m_write_xml->write_actor(type_tmp);
	
	// 解析类型
	is_first = true;
	memset(type_tmp, 0, sizeof(type_tmp));
	for (i = 0; i < 1000; i++)
	{
		char tmp[500] = { 0 };
		snprintf(tmp, sizeof(tmp) - 1, "/html/body/div[3]/div/div/div[2]/ul/li[3]/span[2]/a[%d]",
			i + 1);
		if ((node = ptr->html_xpath_node(tmp)) != NULL)
		{
			if (!is_first)
			{
				snprintf(type_tmp + strlen(type_tmp), sizeof(type_tmp) - strlen(type_tmp) - 1, "/");
			}
			
			snprintf(type_tmp + strlen(type_tmp), sizeof(type_tmp) - strlen(type_tmp) - 1, "%s",
					ptr->html_node_value(node));
			is_first = false;
		}
		else
		{
			break;
		}
	}
	m_write_xml->write_type(type_tmp);
	
	// 解析发布时间
	if ((node = ptr->html_xpath_node("/html/body/div[3]/div/div/div[2]/ul/li[4]/span/a")) != NULL)
	{
		m_write_xml->write_release_time(ptr->html_node_value(node));
	}

	// 解析观看次数	
	if ((node = ptr->html_xpath_node("//*[@id=\"mod_viewcount_total\"]")) != NULL)
	{
		m_write_xml->write_views(ptr->html_node_value(node));
	}
	
	// 解析简述
	if ((node = ptr->html_xpath_node("/html/body/div[3]/div/div/div[2]/div/p")) != NULL)
	{
		m_write_xml->write_description(ptr->html_node_value(node));
	}
	
	// 解析图片
	if ((node = ptr->html_xpath_node("//*[@id=\"img_cover_pic\"]")) != NULL)
	{
		m_write_xml->write_post(ptr->html_node_prop(node, "src"));
	}
	
	// 解析播放链接 /html/body/div[3]/div/div[2]/div[2]/div[2]/ul/li/p/a
	// /html/body/div[3]/div/div[2]/div[2]/div[2]/ul/li/p/a
	// /html/body/div[3]/div/div[2]/div[2]/div[2]/ul[2]/li[2]/p/a
	// /html/body/div[3]/div/div[2]/div[2]/div[2]/ul[3]/li[2]/p/a
	
	is_first = true;
	memset(type_tmp, 0, sizeof(type_tmp));
	m_write_xml->write_seri_begin();
	char domain[500] = { 0 };
	
	char *url_tmp = (char *)malloc(1024*10);
	NEW_CHECK(url_tmp);
	int j = 0;
	for ( j = 0; j < 100; j++)
	{
		for (i = 0; i < 10000; i++)
		{
			char tmp[500] = { 0 };
			snprintf(tmp, sizeof(tmp) - 1, "/html/body/div[3]/div/div[2]/div[2]/div[2]/ul[%d]/li[%d]/p/a",
				j + 1, i + 1);
			if ((node = ptr->html_xpath_node(tmp)) != NULL)
			{
				memset(url_tmp, 0, 1024 * 10);
				utility_c::util_url_abs(url, ptr->html_node_prop(node, "href"), url_tmp);
				m_write_xml->write_seri(ptr->html_node_value(node), url_tmp, "");
			}
			else
			{
				break;
			}
		}
	}
	m_write_xml->write_seri_end();
	free(url_tmp);
	
	m_write_xml->write_end();
	return true;
}

bool handle_qq::handle_video(char *url, char *html)
{
	if (url == NULL || html == NULL)
	{
		return false;
	}
	
	html_c html_doc;
	if (!html_doc.html_read_mem(html, "utf-8"))
	{
		return false;
	}
	
	m_write_xml->write_begin();
	html_node_ptr node = html_doc.html_xpath_node("/html/body/div[2]/div/div/p/a");
	if (node != NULL)
	{
		m_write_xml->write_kind(html_doc.html_node_value(node));
		if (strstr(html_doc.html_node_value(node), "电影") != NULL)
		{
			return handle_movie(url, &html_doc);
		}
		else if (strstr(html_doc.html_node_value(node), "电视剧") != NULL)
		{
			return handle_tv(url, &html_doc);
		}
	}
	
	return false;
}

bool handle_qq::handle_html(char *url, char *html)
{
	if (url == NULL || html == NULL)
	{
		return false;
	}
	
	utility_c::util_url_format(url);
	if (match_judge(url, "^v.qq.com/detail/*"))
	{
		return handle_video(url, html);	
	}
	return false;
}
