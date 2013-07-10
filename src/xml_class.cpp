#include <xml_class.h>
xml_c::xml_c()
{
	m_doc = NULL;
	memset(m_input_name, 0, sizeof(m_input_name));
	memset(m_encoding, 0, sizeof(m_encoding));
}
xml_c::xml_c(char *file_name, char *encoding)
{
	m_doc = NULL;
	memset(m_input_name, 0, sizeof(m_input_name));
	memset(m_encoding, 0, sizeof(m_encoding));
	strncpy(m_input_name, file_name, sizeof(m_input_name) - 1);
	strncpy(m_encoding, encoding, sizeof(encoding) - 1);
}
bool xml_c::xml_load_file()
{
	if (strlen(m_input_name) < 1)
	{
		g_log->error_stream()<<ERROR_HEAD<<"length(m_input_name) < 1";
		return false;
	}
	
	
	if (m_doc != NULL)
	{
		delete m_doc;
		m_doc = NULL;
	}
	
	m_doc = new TiXmlDocument(m_input_name);
	NEW_CHECK(m_doc);
	if (strcmp(m_encoding, "utf-8") == 0 || strcmp(m_encoding, "UTF-8") == 0)
	{
		if (!m_doc->LoadFile(TIXML_ENCODING_UTF8))
		{
			g_log->error_stream()<<ERROR_HEAD<<"m_doc->LoadFile() fail, file_name is "<<m_input_name;
			return false;
		}
	}
	else
	{
		if (!m_doc->LoadFile(TIXML_ENCODING_UNKNOWN))
		{
			g_log->error_stream()<<ERROR_HEAD<<"m_doc->LoadFile() fail, file_name is "<<m_input_name;
			return false;
		}
	}
	
	return true;
}

xml_c::~xml_c()
{
	if (m_doc != NULL)
	{
		delete m_doc;
		m_doc = NULL;
	}
}
bool xml_c::xml_load_file(char *file_name, char *encoding)
{
	if (file_name == NULL)
	{
		g_log->error_stream()<<ERROR_HEAD<<"xml::xml_load_file paragram file_name is NULL";
		return false;
	}
	
	memset(m_input_name, 0, sizeof(m_input_name));
	memset(m_encoding, 0, sizeof(m_encoding));
	strncpy(m_input_name, file_name, sizeof(m_input_name) - 1);
	strncpy(m_encoding, encoding, sizeof(m_encoding) - 1);
	
	return xml_load_file();
}
char *xml_c::xml_node_text(xml_node_ptr ptr)
{
	if (ptr == NULL)
	{
		return NULL;
	}
	return (char *)ptr->Value();
}
char *xml_c::xml_node_value(xml_node_ptr ptr)
{
	if (ptr == NULL)
	{
		return NULL;
	}
	return (char *)ptr->GetText();
}
char *xml_c::xml_node_attr(xml_node_ptr ptr, char *attr)
{
	if (ptr == NULL || attr == NULL)
	{
		return NULL;
	}
	return (char *)(ptr->Attribute(attr));
}
xml_node_ptr xml_c::xml_root_node()
{
	return m_doc->RootElement();
}
bool xml_c::xml_block_process(xml_node_ptr ptr, char *tag_name, int32 (*func)(xml_node_ptr))
{
	xml_node_ptr child = NULL;
	while( child = (xml_node_ptr)(ptr->IterateChildren(child )) )
	{
		if (strcmp(tag_name, child->Value()) == 0)
		{
			func(child);	
		}
	}
	
	return true;
}
xml_node_ptr xml_c::xml_search_node(xml_node_ptr ptr, char *tag_name)
{
	if (ptr == NULL || tag_name == NULL)
	{
		g_log->warn_stream()<<ERROR_HEAD<<"xml::xml_search_node paragram ptr or tag_name is NULL";
		return NULL;
	}
	
	return (xml_node_ptr)(ptr->FirstChild(tag_name));
}
xml_node_ptr xml_c::xml_search_node_re(xml_node_ptr ptr, char *tag_name)
{
	if (ptr == NULL || tag_name == NULL)
	{
		g_log->warn_stream()<<ERROR_HEAD<<ERROR_HEAD<<
						"xml::xml_search_node_re paragram ptr or tag_name is NULL";
		return NULL;
	}
	
	xml_node_ptr child = NULL;
	if ((child = xml_search_node(ptr, tag_name)) != NULL)
	{
		return child;
	}
	
	while( child = (xml_node_ptr)(ptr->IterateChildren( child ) ))
	{
		xml_node_ptr tmp = NULL;
		if ((tmp = xml_search_node_re(child, tag_name)) != NULL)
		{
			return tmp;
		}
	}
	
	return NULL;
}
bool xml_c::xml_reset()
{
	if (m_doc != NULL)
	{
		delete m_doc;
		m_doc = NULL;
	}
	
	memset(m_input_name, 0, sizeof(m_input_name));
	memset(m_encoding, 0, sizeof(m_encoding));
	return true;
}

xml_node_ptr xml_c::xml_first_children(xml_node_ptr ptr)
{
	if (ptr == NULL)
	{
		g_log->error_stream()<<ERROR_HEAD<<"paragram is NULL";
		return NULL;
	}
	
	return (xml_node_ptr)(ptr->FirstChild());
}
xml_node_ptr xml_c::xml_next_sibling(xml_node_ptr ptr)
{
	if (ptr == NULL)
	{
		g_log->error_stream()<<ERROR_HEAD<<"paragram is NULL";
		return NULL;
	}
	
	return (xml_node_ptr)(ptr->NextSibling());
}
