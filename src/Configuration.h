#ifndef _CONFIGURATION_H_
#define _CONFIGURATION_H_

#include <vector>
#include <string>
#include <map>
using namespace std;

class ItemData
{
public:
	ItemData(const std::string& s1, const std::string& s2)
	{
		m_key = s1;
		m_value = s2;
	}

	std::string m_key;
	std::string m_value;

	friend bool operator< (const ItemData& s1, const ItemData& s2)
	{
		return s1.m_key < s2.m_key;
	}
};
class XPathPattern {
public:
	XPathPattern() {
		_XPathPattern = _ChildPath = _keyWord = "";
		_pathType = 0;
	}
	XPathPattern( const string p , const int t ) {
		_XPathPattern = p;
		_pathType = t;
		_ChildPath = _keyWord = "";
	}
	XPathPattern( const string &p , const int t , const string &childPattern , 
		const string &keyword ) {
			_XPathPattern = p;
			_pathType = t;
			_ChildPath = childPattern;
			_keyWord = keyword;
	}
	XPathPattern( const XPathPattern &robj ){
		_XPathPattern = robj._XPathPattern;
		_ChildPath = robj._ChildPath;
		_keyWord = robj._keyWord;
		_pathType = robj._pathType;
	}
	string _XPathPattern;
	string _ChildPath;
	string _keyWord;
	int    _pathType;
};
typedef map<string,XPathPattern> nodePatternMap;

class Configuration
{
	static const int max_path = 2560;
	static const int max_line_length = 2560;
	static const int MAX_NODE_ATTRIBUTE_NAMELEN = 256;
	static const int MAX_PATTERN_LEN = 1024;
	static const int MAX_KEYWORD_LEN = 1024;
public:
	Configuration();
	virtual ~Configuration();

	bool load( const char* file_name  , const int name_len );
	bool loadPagePattern( const char *file_name , const int name_len );
	inline const char*	getConfigurationName() {return m_file_name.c_str();}
	std::string getString(const char* key,const char* strdefault = "") ;
	int getInt(const char* key,int ndefault = 0);
	const nodePatternMap &getNodePatternMap() {
		return m_nodePatternMap;
	}

private:
	
	string m_file_name;
	std::vector<ItemData> m_content;

	nodePatternMap m_nodePatternMap;
	bool loadLine(char* buffer);
	bool loadPatternLine( char *buffer);
	void trim(std::string&);
	void insertItem(const ItemData&);
	bool m_loaded;
};

#endif

