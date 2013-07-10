/*******************************************************************************
 *               Copyright (C), 2003-2013, KuaiBo All rights reserved
 -------------------------------------------------------------------------------
 * File Name	:	log_class.h
 * Version		:	Initial Draft
 * Author		:	yuyong
 * Created		:	2013/4/22
 * Description	:   log类--用来打印日志的,封装log4cpp
 -------------------------------------------------------------------------------
 * History:
 *		yuyong 2013/4/22	Created
 *******************************************************************************/
#ifndef __LOG_H
#define __LOG_H
#include <log4cpp/Category.hh>
#include <log4cpp/PropertyConfigurator.hh>
#include <def.h>
typedef log4cpp::CategoryStream log_stream;
typedef class log_c *log_ptr;
class log_c
{
	public:
		log_c();
		bool log_init(char *config);
		log_stream debug_stream();
		log_stream info_stream();
		log_stream notice_stream();
		log_stream warn_stream();
		log_stream error_stream();
		log_stream crit_stream();
		log_stream alert_stream();
		log_stream fatal_stream();
		~log_c();
	private:
		log4cpp::Category *m_log;
};

#endif
