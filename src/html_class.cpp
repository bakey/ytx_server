#include <html_class.h>

html_c::html_c()
{
	m_doc = NULL;
	m_xpath_context = NULL;
}
html_c::~html_c()
{
	if (m_xpath_context != NULL)
	{
		xmlXPathFreeContext(m_xpath_context);
		m_xpath_context = NULL;
	}
	if (m_doc != NULL)
	{
		xmlFreeDoc(m_doc);
		m_doc = NULL;
	}
	
	xmlCleanupParser();
}
bool html_c::html_open_file(char *file_name, char *encoding)
{
	if (file_name == NULL || encoding == NULL)
	{
		return false;
	}
	if (m_xpath_context != NULL)
	{
		xmlXPathFreeContext(m_xpath_context);
		m_xpath_context = NULL;
	}
	if (m_doc != NULL)
	{
		xmlFreeDoc(m_doc);
		m_doc = NULL;
	}
	xmlKeepBlanksDefault(0);
	
	m_doc = htmlReadFile(file_name, encoding, XML_PARSE_NOENT);
	//m_doc = xmlReadFile(file_name, encoding, XML_PARSE_NOENT);
	if (!m_doc)
	{
		return false;
	}
	
	m_xpath_context = xmlXPathNewContext(m_doc);
	if (m_xpath_context == NULL)
	{
		xmlFreeDoc(m_doc);
		m_doc = NULL;
		return false;
	}

	return true;
}
bool html_c::html_read_mem(char *buffer, char *base_url, char *encoding)
{
	if (buffer == NULL || base_url == NULL || encoding == NULL)
	{
		return false;
	}
	if (m_xpath_context != NULL)
	{
		xmlXPathFreeContext(m_xpath_context);
		m_xpath_context = NULL;
	}
	if (m_doc != NULL)
	{
		xmlFreeDoc(m_doc);
		m_doc = NULL;
	}
	xmlKeepBlanksDefault(0);
	
	m_doc = htmlReadMemory(buffer, strlen(buffer), base_url, encoding, XML_PARSE_NOENT);
	if (!m_doc)
	{
		return false;
	}
	
	m_xpath_context = xmlXPathNewContext(m_doc);
	if (m_xpath_context == NULL)
	{
		xmlFreeDoc(m_doc);
		m_doc = NULL;
		return false;
	}
	
	return true;
}
html_node_ptr html_c::html_xpath_node(char *xpath)
{
	if (xpath == NULL)
	{
		return NULL;
	}
	
	m_xpath_object = xmlXPathEvalExpression((const xmlChar*)xpath, m_xpath_context);
	if (m_xpath_object == NULL)
	{
		return NULL;
	}
	
	if (m_xpath_object->nodesetval == NULL)
	{
		xmlXPathFreeObject(m_xpath_object);
		return NULL;
	}
	
	if (m_xpath_object->nodesetval->nodeNr < 1)
	{
		xmlXPathFreeObject(m_xpath_object);
		return NULL;
	}
	
	return m_xpath_object->nodesetval->nodeTab[0];
}
xmlXPathObjectPtr html_c::html_xpath_node_xpath_object(char *xpath)
{
	if (xpath == NULL)
	{
		return NULL;
	}
	
	xmlXPathObjectPtr xpathObject = xmlXPathEvalExpression((const xmlChar*)xpath, m_xpath_context);
	if (xpathObject == NULL)
	{
		return NULL;
	}
	
	if (xpathObject->nodesetval == NULL)
	{
		xmlXPathFreeObject(xpathObject);
		return NULL;
	}
	
	if (xpathObject->nodesetval->nodeNr < 1)
	{
		xmlXPathFreeObject(xpathObject);
		return NULL;
	}
	
	return xpathObject;
}

void html_c::html_free_xpath_object()
{
	if ( m_xpath_object != NULL ) {
		xmlXPathFreeObject( m_xpath_object) ;
		m_xpath_object = NULL;
	}
}

html_set_ptr html_c::html_xpath_multi_node(char *xpath)
{
     if (xpath == NULL)
    {   
        return NULL;
    }   
    
    m_xpath_object = xmlXPathEvalExpression((const xmlChar*)xpath, m_xpath_context);
    if (m_xpath_object == NULL)
    {   
        return NULL;
    }   
    
    if (m_xpath_object->nodesetval == NULL)
    {   
        xmlXPathFreeObject(m_xpath_object);
        return NULL;
    }   
    
    if (m_xpath_object->nodesetval->nodeNr < 1)
    {   
        xmlXPathFreeObject(m_xpath_object);
        return NULL;
    }   
    return m_xpath_object->nodesetval;
}
char *html_c::html_node_value(html_node_ptr node)
{
	if (node == NULL)
	{
		return NULL;
	}
	return (char *)xmlNodeGetContent(node);
}
char *html_c::html_node_text(html_node_ptr node)
{
	if (node == NULL)
	{
		return NULL;
	}
	return (char *)node->name;
}
char *html_c::html_node_prop(html_node_ptr node, char *prop)
{
	if (node == NULL || prop == NULL)
	{
		return NULL;
	}
	
	return (char *)xmlGetProp(node, (const xmlChar*)prop);
}
html_node_ptr html_c::html_node_next(html_node_ptr node)
{
	if (node == NULL)
	{
		return NULL;
	}
	return node->next;
}
