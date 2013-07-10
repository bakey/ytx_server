/*******************************************************************************
 *               Copyright (C), 2003-2013, KuaiBo All rights reserved
 -------------------------------------------------------------------------------
 * File Name	:	config_class.h
 * Version		:	Initial Draft
 * Author		:	yuyong
 * Created		:	2013/5/2
 * Description	:	≈‰÷√Œƒº˛∂¡»°.
 -------------------------------------------------------------------------------
 * History:
 *		yuyong 2013/5/2	Created
 *******************************************************************************/
#ifndef __CONFIG_CLASS_H
#define __CONFIG_CLASS_H
#include <def.h>
#include <xml_class.h>
#include <log_class.h>

#define MAX_PATH_LENGTH 500

typedef class config_c * config_ptr;

class config_c
{
	public:
		config_c(char *file_name, char *encoding="utf-8");
		~config_c();
		bool config_get();
		bool config_print();
	public:
		char gu_data_path[MAX_PATH_LENGTH];
		char du_data_path[MAX_PATH_LENGTH];
		char du_conf[MAX_PATH_LENGTH];
		char du_xml[MAX_PATH_LENGTH];
		char data_douban[MAX_PATH_LENGTH];
		char data_m1905[MAX_PATH_LENGTH];
		char data_sohu[MAX_PATH_LENGTH];
		char data_qvod[MAX_PATH_LENGTH];
		char data_kankan[MAX_PATH_LENGTH];
		char data_pptv[MAX_PATH_LENGTH];
		char data_cntv[MAX_PATH_LENGTH];
		char data_ku6[MAX_PATH_LENGTH];
		char data_baomihua[MAX_PATH_LENGTH];
		char data_taomee[MAX_PATH_LENGTH];
		char data_douban_2[MAX_PATH_LENGTH];
	private:
		char xml_file[MAX_PATH_LENGTH];
		char xml_encoding[50];
	private:
		bool config_set_str(xml_node_ptr node, char *str);
		bool config_set_uint8(xml_node_ptr node, uint8 *conf_i);
		bool config_set_uint16(xml_node_ptr node, uint16 *conf_i);
		bool config_set_uint32(xml_node_ptr node, uint32 *conf_i);
		bool config_set_uint64(xml_node_ptr node, uint64 *conf_i);
		
		bool config_set_node_str(xml_node_ptr node, char *tag, char *str);
};

#endif
