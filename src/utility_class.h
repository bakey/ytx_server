/*******************************************************************************
 *               Copyright (C), 2003-2013, KuaiBo All rights reserved
 -------------------------------------------------------------------------------
 * File Name	:	utility_class.h
 * Version		:	Initial Draft
 * Author		:	yuyong
 * Created		:	2013/5/17
 * Description	:	工具类.
 -------------------------------------------------------------------------------
 * History:
 *		yuyong 2013/5/17	Created
 *******************************************************************************/
#ifndef UTILITY_CLASS_H
#define UTILITY_CLASS_H
#include <def.h>
#include <string>
using namespace std;
#include "ul_sign.h"
class utility_c
{
	public:
		// 去掉url前面的http://www.
		static bool util_url_format(char *source_url);
		// 查看该URL是否是以HTTP://开头
		static bool util_url_http(char *url);
		// 获取URL的域名
		static bool util_url_domain(char *url, char *domain);
		// 获取URL的.路径
		static bool util_url_pwd(char *url, char *pwd);
		// 获取URL的..路径
		static bool util_url_upper(char *url, char *upper);
		// 根据相对url, 和相对路径, 产生新的URL
		static bool util_url_abs(char *r_url, char *r_path, char *a_url);
        static string trim( const string &str );
		static int   split( const string str , char spliter , vector<string> &element);
		static int   split( const string str , string spliters , vector<string> &element);
		static int dump_file( char *content , int clen );
		static unsigned long long get_url_sign( const char *str , size_t len );
	private:
};

#endif

