#include <algorithm>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <errno.h>
#include <iostream>
using namespace std;
#include "Configuration.h"
#include "node_type_def.h"

Configuration::Configuration()
{
	m_loaded = false;
}

Configuration::~Configuration()
{
	m_content.clear();
}

bool Configuration::load(const char* file_name , const int name_len )
{
	assert( file_name != NULL );
	if ( name_len > max_path ) {
		return false;
	}
	m_file_name.clear();
	m_file_name.append( file_name , name_len );
	//strncpy(m_file_name, file_name , name_len );	

	char buffer[max_line_length], *p_ret;
	FILE* fp = fopen(m_file_name.c_str(), "r");

	if(!fp)
	{
		return false;
	}

	m_content.clear();
	while(true) 
	{
		p_ret = fgets(buffer, max_line_length, fp);
		if(!p_ret)
		{
			break;
		}
		loadLine(buffer);
	}
	fclose(fp);
	m_loaded = true;
	return true;
}

bool Configuration::loadLine(char* buffer)
{
	char *p_eq = strchr(buffer, '=');
	if(p_eq)
	{
		int pos = p_eq - buffer;
		char *p_LF = strrchr(buffer, '\n');
		string key = string(buffer, 0, pos);
		string value = string(buffer, pos + 1, p_LF - p_eq - 1);
		trim(key);
		trim(value);
		if(key[0] != '#' || key[0] != '/')
		{
			insertItem(ItemData(key, value));
		}
	}
	else
	{
		return false;
	}
	return true;
}

void Configuration::trim(string& s)
{
	int bpos = s.find_first_not_of(0x20);
	int epos = s.find_last_not_of(0x20);
	if(bpos < 0 || epos < 0) {
		s.empty();
	}
	else {
		s = string(s, bpos, epos - bpos + 1);
	}
}

void Configuration::insertItem(const ItemData& item)
{
	vector<ItemData>::iterator it_find 
		= lower_bound(m_content.begin(), m_content.end(), item);

	if(it_find == m_content.end() || it_find->m_key != item.m_key)
	{
		m_content.insert(it_find, item);
	}
}

string Configuration::getString(const char* key,const char* strdefault)
{
	vector<ItemData>::iterator it_find 
		= lower_bound(m_content.begin(), m_content.end(), ItemData(key, ""));

	if(it_find != m_content.end() && it_find->m_key == key)
	{
		return it_find->m_value;
	}
	return strdefault;
}

int Configuration::getInt(const char* key,int ndefault)
{
	vector<ItemData>::iterator it_find 
		= lower_bound(m_content.begin(), m_content.end(), ItemData(key, ""));

	if(it_find != m_content.end() && it_find->m_key == key)
	{
		return atoi(it_find->m_value.c_str());
	}
	return ndefault;
}

bool Configuration::loadPagePattern( const char *file_name , const int name_len )
{
	assert( file_name != NULL );
	if ( name_len > max_path ) {
		return false;
	}
	m_file_name.assign( file_name , name_len );

	char buffer[max_line_length], *p_ret;
	FILE* fp = fopen(m_file_name.c_str(), "r");

	if(!fp)
	{
		cout << "load " << m_file_name << " failed. " << strerror(errno) << endl;
		return false;
	}

	m_content.clear();
    char node_attr[MAX_NODE_ATTRIBUTE_NAMELEN];
    char pattern[ MAX_PATTERN_LEN ];
	char childrenPath[ MAX_PATTERN_LEN ];
	char keyword[ MAX_KEYWORD_LEN ];
    int node_type;
	while(true) 
	{
        if ( !fgets(buffer , max_line_length , fp) ) {
            break;
        }
        int node_type = atoi( buffer );
		XPathPattern pp;
        switch( node_type )
        {
            case NODE_TYPE_EMPTY_CONTENT:
            case NODE_TYPE_SINGLE_VALUE:
			case NODE_TYPE_LIST_VALUE:
			case NODE_TYPE_STATIC_VALUE:
			case NODE_TYPE_PLAYLINK:
			case NODE_TYPE_SRC_LINK:
				fgets( node_attr , MAX_NODE_ATTRIBUTE_NAMELEN , fp );
				fgets( pattern , MAX_PATTERN_LEN , fp );
				node_attr[ strlen(node_attr)-1 ] = '\0';
				pattern[ strlen(pattern)-1 ] = '\0';
				pp._XPathPattern = pattern;
				pp._pathType = node_type;
				break;
			case NODE_TYPE_KEYWORD_FILTER:
				fgets( node_attr , MAX_NODE_ATTRIBUTE_NAMELEN , fp );
				fgets( pattern , MAX_PATTERN_LEN , fp );
				fgets( childrenPath , MAX_PATTERN_LEN , fp );
				fgets( keyword , MAX_KEYWORD_LEN , fp );
				node_attr[ strlen(node_attr)-1 ] = '\0';
				pattern[ strlen(pattern)-1 ] = '\0';
				childrenPath[ strlen(childrenPath)-1 ] = '\0';
				keyword[ strlen(keyword)-1 ] = '\0';	
				pp._XPathPattern = pattern;
				pp._ChildPath = childrenPath;
				pp._pathType = node_type;
				pp._keyWord = keyword;

				break;
			default :
				break;
		}    
		m_nodePatternMap.insert( make_pair<string,XPathPattern>(node_attr,pp) );
	}
	/*for( nodePatternMap::iterator it = m_nodePatternMap.begin();
		it != m_nodePatternMap.end();
		++ it ) {
			cout << it->first << endl;
			cout << it->second._XPathPattern << " " << it->second._pathType << endl;
			if ( it->second._ChildPath != "" ) {
				cout << it->second._ChildPath << endl;
			}
			if ( it->second._keyWord != "" ) {
				cout << it->second._keyWord << endl;
			}
			cout << "========================================" << endl;
	}*/
	fclose(fp);
    cout << "load [" << m_file_name << "] success" << endl;
	return true;

}

bool Configuration::loadPatternLine( char *buffer )
{
	char node_attr[MAX_NODE_ATTRIBUTE_NAMELEN];
	char pattern[ MAX_PATTERN_LEN ];
	int node_type ;
	if ( sscanf( buffer , "%s%s%d" , node_attr , pattern , &node_type ) != 3 ) {
		return false;
	}
	string patternStr = pattern;
	XPathPattern pp( patternStr , node_type );
	m_nodePatternMap.insert( make_pair<string,XPathPattern>(node_attr,pp) );
	//m_nodePatternMap[ (string)node_attr ] = XPathPattern( patternStr , node_type );
	return true;
}

