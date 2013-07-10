/*******************************************************************************
 *               Copyright (C), 2003-2013, KuaiBo All rights reserved
 -------------------------------------------------------------------------------
 * File Name	:	handle_letv.h
 * Version		:	Initial Draft
 * Author		:	yuyong
 * Created		:	2013/5/16
 * Description	:	全局头文件，主要声明一些全局变量.
 -------------------------------------------------------------------------------
 * History:
 *		yuyong 2013/5/16	Created
 *******************************************************************************/
#ifndef HANDLE_LETV_H
#define HANDLE_LETV_H
#include <def.h>
#include <html_class.h>
#include <xml_write.h>
#include <utility_class.h>
#include "Handler.h"
#include "ParseCenter.h"
#include <string>
using namespace std;

class handle_letv : public Handler
{
	public:
		handle_letv(xml_write_ptr);
		~handle_letv();
		virtual bool handle_html(char *url, char *html);
		const char *getPattern() ;
		const char *getLetvSqlCmd();
		inline virtual void setParseCenter(ParseCenter *center) {
			return ;
		}
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
			return 0;
		}
	private:
		bool handle_movie(char *url, char *html);
		bool handle_tv(char *url, char *html);
	private:
		xml_write_ptr m_write_xml;
		string m_detail_pattern;
		string m_sql;
        int m_proc_movie;
        int m_proc_tv;
        int m_proc_comic;
};


#endif
