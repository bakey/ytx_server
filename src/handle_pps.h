#ifndef _HANDLE_PPS_H_
#define _HANDLE_PPS_H_
#include <def.h>

#include <html_class.h>
#include <xml_write.h>
#include <utility_class.h>
#include "Handler.h"
#include "Configuration.h"
#include "ParseCenter.h"
#include "node_type_def.h"

class handle_pps : public Handler
{
	public:
		handle_pps(xml_write_ptr );
		virtual ~handle_pps();
		virtual bool handle_html(char *url, char *html);
        void setParseCenter( ParseCenter *center );
		inline virtual int get_proc_movie_count() {
            return m_proc_movie;
        }
        inline virtual int get_proc_tv_count() {
            return m_proc_tv;
        }
        inline virtual int get_proc_comic_count() {
            return m_proc_comic;
        }
		inline virtual int get_proc_variety_count() {
			return m_proc_variety;
		}
	private:
		bool write_xml(char *url, char *html , char *type , Configuration *config );
		bool handle_tv(char *url, html_ptr);
		bool handle_video(char *url, char *html);
		bool write_single_node( const nodePatternMap::const_iterator &pit );
		bool write_list_node( const nodePatternMap::const_iterator &pit );
		bool write_empty_node( const nodePatternMap::const_iterator &pit );
		bool write_static_node( const nodePatternMap::const_iterator &pit );
		bool write_href_node( const nodePatternMap::const_iterator &pit );
		bool write_play_link( const nodePatternMap::const_iterator &pit );
		bool write_src_link( const nodePatternMap::const_iterator &pit );
		bool write_keyword_filter( const nodePatternMap::const_iterator &pit );
		inline html_node_ptr getNodeByXPath( const char *xpath ) {
			return m_html_doc.html_xpath_node( (char *)xpath );
		}
	private:
		enum {
			PAGE_TYPE_MOVIE   = 1,
			PAGE_TYPE_TV      = 2,
			PAGE_TYPE_VARIETY = 3,
			PAGE_TYPE_COMIC   = 4,
		};
		int m_proc_movie;
        int m_proc_tv;
		int m_proc_comic;
		int m_proc_variety;
		xml_write_ptr m_write_xml;
		html_c 		  m_html_doc;
		vector<string>  m_page_patterns;
		vector<string>  m_page_patterns_value;
		vector<int>     m_pattern_map_type;
        vector<Configuration *> m_pattern_conf;
		ParseCenter     *mPCenter;
		char              *m_page_buffer;
		int               m_cur_page_buffer_len;
		static string   m_my_sitename;
		static const int MAX_UTF8_HTML_PAGE_LEN = 10*1024*1024;
};

#endif
