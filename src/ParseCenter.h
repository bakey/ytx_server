#ifndef _PARSE_CENTER_H_
#define _PARSE_CENTER_H_
#include "Configuration.h"
#include <vector>
#include <map>
using namespace std;
class ParseCenter {
public:
	ParseCenter();
	~ParseCenter();
	int loadConfig( const char *fileName );
	Configuration *getConfigBySite( const string &site );
	inline Configuration *getMainConfig() {
		return m_main_config;
	}
	void get_conf_path( const char *conf , string &path );
private:
	Configuration *m_main_config;
	map<string,Configuration *> mSiteConfig;

};
#endif