/*******************************************************************************
 *               Copyright (C), 2003-2013, KuaiBo All rights reserved
 -------------------------------------------------------------------------------
 * File Name	:	xml_class.h
 * Version		:	Initial Draft
 * Author		:	yuyong
 * Created		:	2013/4/21
 * Description	:   xml类--用来解析xml的
 -------------------------------------------------------------------------------
 * History:
 *		yuyong 2013/4/21	Created
 *******************************************************************************/
#ifndef __XML_H
#define __XML_H
#include <tiny/tinyxml.h>
#include <tiny/tinystr.h>
#include <def.h>
#include <log_class.h>
extern log_ptr g_log;
typedef	TiXmlDocument 	xml_doc;
typedef	TiXmlDocument* xml_doc_ptr;
typedef	TiXmlElement	xml_node;
typedef TiXmlElement*	xml_node_ptr;
typedef class xml_c* xml_ptr;
class xml_c
{
	public:
		xml_c();
		xml_c(char *file_name, char *encoding="utf-8");
		~xml_c();
		bool xml_load_file();
		bool xml_load_file(char *file_name, char *encoding="utf-8");
		static char *xml_node_text(xml_node_ptr ptr);
		static char *xml_node_value(xml_node_ptr ptr);
		static char *xml_node_attr(xml_node_ptr ptr, char *attr_name);
		xml_node_ptr xml_root_node();
		static bool xml_block_process(xml_node_ptr ptr, char *tag_name, int32 (*func)(xml_node_ptr));
		static xml_node_ptr xml_search_node(xml_node_ptr ptr, char *tag_name);
		static xml_node_ptr xml_search_node_re(xml_node_ptr ptr, char *tag_name);
		static xml_node_ptr xml_first_children(xml_node_ptr ptr);
		static xml_node_ptr xml_next_sibling(xml_node_ptr ptr);
		bool xml_reset();
	private:
		char m_input_name[300];
		char m_encoding[100];
		xml_doc_ptr m_doc;
};

#endif
