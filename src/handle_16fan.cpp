#include <handle_16fan.h>
#include <regular.h>
#include <global.h>
#include "uconv.h"
#include "comlog.h"
#include "ul_url_sign.h"
#include "ul_sign.h"
#include <mysql_client.h>


extern db_conn_t *g_mysql;
string handle_16fan::m_my_sitename = "16fan";
handle_16fan::handle_16fan(xml_write_ptr ptr )
{
	mPCenter = NULL;
}
handle_16fan::~handle_16fan()
{
}
void handle_16fan::setParseCenter( ParseCenter *center ) {
	mPCenter = center;
  	Configuration *config = mPCenter->getMainConfig();
}


bool handle_16fan::handle_html(char *url, char *html)
{
	if (url == NULL || html == NULL)
	{
		return false;
	}	
	utility_c::util_url_format(url);	
	string urlPattern = mPCenter->getMainConfig()->getString("16fan_url_pattern" , "");
	if ( urlPattern != "" && match_judge(url, (char*)urlPattern.c_str() ) )
	{
		com_writelog( COMLOG_DEBUG , "pass pattern , url = %s" , url );	
		bool ret = handle_page( url , html );
		if ( !ret ) {
			return false;
		}
		return 	true;
	}else {
		com_writelog( COMLOG_DEBUG , "url not match pattern : %s" , url );
	}
	return false;
}


bool handle_16fan::handle_page(char *url, char *html)
{	
    size_t ori_len = strlen( html );
    char *encode_buf = new char[ ori_len * 2 ];
    size_t dst_len = gbk_to_utf8( html , ori_len , encode_buf , ori_len*2 , 0 );
	bool ret = m_html_doc.html_read_mem( encode_buf , url , "utf-8");
	if ( !ret ) {
        delete []encode_buf;
		return ret;
	}
	string title = getTitle();
	if ( title == "" ) {
        delete []encode_buf;
		com_writelog( COMLOG_WARNING , "get title failed , url = %s" , url );
		return false;
	}
    com_writelog( COMLOG_DEBUG , "get title = %s" , title.c_str() );
	string author = getAuthor();
	if ( author == "" ) {
		author = "hkzhe";
	}
    int reply_cnt = getReplyCount();
    int hit_cnt = getHitCount( url );
    //int pub_time = getPublicTime();
    //int update_time = getUpdateTime();
	/*string content = getContent();
	if ( content == "" ) {
        com_writelog( COMLOG_WARNING , "get content failed , url = %s" , url );
        delete []encode_buf;
		return false;
	}*/
	com_writelog(COMLOG_DEBUG , "title = %s , author = %s , reply count = %d , hit count = %d" , title.c_str() , author.c_str() , reply_cnt , hit_cnt );
    delete []encode_buf;
	return true;
}
int handle_16fan::getUpdateTime() {
   /* html_node_ptr node = m_html_doc.html_xpath_node("");
    if ( node == NULL ) {
        m_html_doc.html_free_xpath_object();
        return -1;
    }
    char *str = m_html_doc.html_node_value( node );
    if ( str == NULL  ) {
        m_html_doc.html_free_xpath_object();
        return -1;
    }*/
    return 0;
}
int handle_16fan::getPublicTime() {
    html_node_ptr node = m_html_doc.html_xpath_node("//*[@id=\"authorposton35731\"]");
    if ( node == NULL ) {
        return -1;
    }
    char *str = m_html_doc.html_node_value( node );
    if ( str == NULL  ) {
        m_html_doc.html_free_xpath_object();
        return -1;
    }
    char rbuf[256] , datebuf[256] , timebuf[256];
    sscanf( str , "%s%s%s" , rbuf , datebuf , timebuf );
    string sstr = (string)datebuf + (string)timebuf;
    //com_writelog( COMLOG_DEBUG , "get time buf = %s" , sstr.c_str() );
    return 0;
}
int handle_16fan::getHitCount( char *url ) {
	html_set_ptr node_set = m_html_doc.html_xpath_multi_node("//*[@class=\"xi1\"][1]");
    if ( node_set == NULL ) {
        com_writelog( COMLOG_DEBUG , "get hit count failed for url = %s" , url );
        return -1 ;
    }
	html_node_ptr node = (html_node_ptr)node_set->nodeTab[0];
    char *str = m_html_doc.html_node_value( node );
    if ( str == NULL  ) {
        m_html_doc.html_free_xpath_object();
        return -1 ;
    }
    int count = atoi( str );
    m_html_doc.html_free_xpath_object();
    xmlFree( str );
    return count;
}

std::string handle_16fan::getTitle()
{
	html_node_ptr title_node = m_html_doc.html_xpath_node("//*[@id=\"thread_subject\"]");
	if ( title_node == NULL ) {
		m_html_doc.html_free_xpath_object();
		return "";
	}
	char *str = m_html_doc.html_node_value( title_node );
	string title = (string)str;
	m_html_doc.html_free_xpath_object();
	xmlFree( str );
	return title;
}
int handle_16fan::getReplyCount()
{
    html_node_ptr node = m_html_doc.html_xpath_node("//*[@id=\"postlist\"]/table[1]/tbody/tr/td[2]/div[3]/span[2]");
    if ( node == NULL ) {
        //m_html_doc.html_free_xpath_object();
        return -1;
    }
    char *str = m_html_doc.html_node_value( node );
    if ( str == NULL  ) {
        m_html_doc.html_free_xpath_object();
        return -1;
    }
    int count = atoi( str );
    m_html_doc.html_free_xpath_object();
    xmlFree( str );
    return count;
}
std::string handle_16fan::getAuthor()
{
	html_node_ptr author_node = m_html_doc.html_xpath_node("//*[@id=\"pid40815\"]/tbody/tr[1]/td[2]/div[1]/div[2]/div[2]/a[1]");
	if ( author_node == NULL ) {
		return "";
	}
	char *str = m_html_doc.html_node_value( author_node );
	string author = (string)str;
	m_html_doc.html_free_xpath_object();
	xmlFree( str );
	return author;
}

std::string handle_16fan::getContent()
{
	html_node_ptr node = m_html_doc.html_xpath_node("//*[@id=\"postmessage_40815\"]");
	if ( node == NULL ) {
		return "";
	}
	char *str = m_html_doc.html_node_value( node );
	string content = (string)str;
	m_html_doc.html_free_xpath_object();
	xmlFree(str);
	return content;
}
