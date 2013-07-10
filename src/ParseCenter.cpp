#include "ParseCenter.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

ParseCenter::ParseCenter()
{
	m_main_config = NULL;
}
ParseCenter::~ParseCenter()
{
	if ( m_main_config != NULL ) {
		delete m_main_config;
		m_main_config = NULL;
	}
}
void ParseCenter::get_conf_path( const char *conf , string &path )
{
	char *sep = strrchr( conf , '/' );
	if ( sep != NULL ) {
		path.assign( conf , sep - conf );
	}else {
    	path = "";
    }
}

int ParseCenter::loadConfig( const char *fileName )
{
	assert( fileName != NULL );
	if ( m_main_config == NULL ) {
		m_main_config = new Configuration;
	}
	if ( !m_main_config->load( fileName , strlen(fileName )) ) {
		return -1;
	}
	string conf_path = "";
	get_conf_path( fileName , conf_path );
	int site_cnt = m_main_config->getInt("site_count",0);
	if ( site_cnt <= 0 ) {
		return 0;
	}
	for( int i = 0 ; i < site_cnt ; ++ i ) {
		char key[128];
		snprintf( key , 128 , "site_name_%d" , i );
		string site_name = m_main_config->getString( key , "");
		assert( site_name != "" );
		string conf_name ;
		if ( conf_path != "") {
			conf_name = conf_path + "/" + site_name + ".conf";
			site_name + ".conf";
		}else {
			conf_name = site_name + ".conf";
		}
		/*Configuration *pNewConf = new Configuration();
		cout << "loading : " << conf_name << endl;
		assert( pNewConf->loadPagePattern( conf_name.c_str() , conf_name.length() ) );
		mSiteConfig[ site_name ] = pNewConf;*/
	}
}

Configuration * ParseCenter::getConfigBySite( const string &site )
{
	map<string,Configuration *>::iterator it = mSiteConfig.find( site );
	if ( it != mSiteConfig.end() ) {
		return it->second;
	}else {
		return NULL;
	}
}

