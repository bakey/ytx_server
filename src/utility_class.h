/*******************************************************************************
 *               Copyright (C), 2003-2013, KuaiBo All rights reserved
 -------------------------------------------------------------------------------
 * File Name	:	utility_class.h
 * Version		:	Initial Draft
 * Author		:	yuyong
 * Created		:	2013/5/17
 * Description	:	������.
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
		// ȥ��urlǰ���http://www.
		static bool util_url_format(char *source_url);
		// �鿴��URL�Ƿ�����HTTP://��ͷ
		static bool util_url_http(char *url);
		// ��ȡURL������
		static bool util_url_domain(char *url, char *domain);
		// ��ȡURL��.·��
		static bool util_url_pwd(char *url, char *pwd);
		// ��ȡURL��..·��
		static bool util_url_upper(char *url, char *upper);
		// �������url, �����·��, �����µ�URL
		static bool util_url_abs(char *r_url, char *r_path, char *a_url);
        static string trim( const string &str );
		static int   split( const string str , char spliter , vector<string> &element);
		static int   split( const string str , string spliters , vector<string> &element);
		static int dump_file( char *content , int clen );
		static unsigned long long get_url_sign( const char *str , size_t len );
	private:
};

#endif

