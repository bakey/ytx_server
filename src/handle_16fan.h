
#ifndef _HANDLE_16FAN_H
#define _HANDLE_16FAN_H
#include <def.h>

#include <html_class.h>
#include <xml_write.h>
#include <utility_class.h>
#include "Handler.h"
#include "Configuration.h"
#include "ParseCenter.h"
#include "node_type_def.h"

class handle_16fan : public Handler
{
	public:
		handle_16fan(xml_write_ptr );
		virtual ~handle_16fan();
		virtual bool handle_html(char *url, char *html);
        void setParseCenter( ParseCenter *center );
	private:
		string get_table_name( unsigned long long urlsign , int table_count ) {
			stringstream ss;
			ss << ( urlsign % table_count );
			return "tbl_crawle_content_" + ss.str();
		}
	
		bool handle_page(char *url, char *html);	
        int getReplyCount();
        int getHitCount( char *url );
        int getPublicTime();
        int getUpdateTime();

		inline html_node_ptr getNodeByXPath( const char *xpath ) {
			return m_html_doc.html_xpath_node( (char *)xpath );
		}
		html_node_ptr getChildren( html_node_ptr node , int seq ) {
			html_node_ptr cur_node = node->children->next;
			for ( int i = 1 ; i < seq; i ++ ) {
				cur_node = cur_node->next->next;
			}
			return cur_node;
		}
		string getTitle();
		string getAuthor();
		string getContent();
	private:
		html_c 		  m_html_doc;
		
		static string   m_my_sitename;
		static const int MAX_UTF8_HTML_PAGE_LEN = 10*1024*1024;
		ParseCenter     *mPCenter;
};

#endif
