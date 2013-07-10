/*******************************************************************************
 *               Copyright (C), 2003-2013, KuaiBo All rights reserved
 -------------------------------------------------------------------------------
 * File Name	:	handle_qq.h
 * Version		:	Initial Draft
 * Author		:	yuyong
 * Created		:	2013/5/23
 * Description	:	解析qq视频的类, 主要用于解析qq视频的.
 -------------------------------------------------------------------------------
 * History:
 *		yuyong 2013/5/23	Created
 *******************************************************************************/
#ifndef HANDLE_QQ_H
#define HANDLE_QQ_H
#include <def.h>
#include <html_class.h>
#include <xml_write.h>
#include <utility_class.h>

class handle_qq
{
	public:
		handle_qq(xml_write_ptr);
		~handle_qq();
		bool handle_html(char *url, char *html);
	private:
		bool handle_movie(char *url, html_ptr);
		bool handle_tv(char *url, html_ptr);
		bool handle_video(char *url, char *html);
	private:
		xml_write_ptr m_write_xml;
};


#endif
