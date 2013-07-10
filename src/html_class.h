/*******************************************************************************
 *               Copyright (C), 2003-2013, KuaiBo All rights reserved
 -------------------------------------------------------------------------------
 * File Name	:	handle_class.h
 * Version		:	Initial Draft
 * Author		:	yuyong
 * Created		:	2013/5/16
 * Description	:	解析html的类, 主要用来把HTML解析为DOM树.
 -------------------------------------------------------------------------------
 * History:
 *		yuyong 2013/5/16	Created
 *******************************************************************************/
#ifndef HTML_CLASS_H
#define HTML_CLASS_H
#include <def.h>
typedef xmlNodePtr html_node_ptr;
typedef xmlNode html_node;
typedef xmlNodeSetPtr html_set_ptr;
typedef class html_c *html_ptr;

class html_c
{
	public:
		html_c();
		~html_c();
		bool html_open_file(char *file_name, char *encoding="utf-8");
		bool html_read_mem(char *buffer, char *base_url, char *encoding="utf-8");
		html_node_ptr html_xpath_node(char *xpath);
		xmlXPathObjectPtr html_xpath_node_xpath_object(char *xpath);
		void         html_free_xpath_object();
        html_set_ptr html_xpath_multi_node(char *xpath);
		static char *html_node_value(html_node_ptr node);
		static char *html_node_text(html_node_ptr node);
		static char *html_node_prop(html_node_ptr node, char *prop);
		static html_node_ptr html_node_next(html_node_ptr node);
		
	private:
		xmlDocPtr 			m_doc;
		xmlXPathContext*	m_xpath_context;
		xmlXPathObjectPtr   m_xpath_object;
};

#endif
