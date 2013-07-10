/*******************************************************************************
 *               Copyright (C), 2003-2013, KuaiBo All rights reserved
 -------------------------------------------------------------------------------
 * File Name	:	xml_write.h
 * Version		:	Initial Draft
 * Author		:	yuyong
 * Created		:	2013/5/14
 * Description	:   xml_write��--�����ѽ����Ĺؼ�����д��xml��
 -------------------------------------------------------------------------------
 * History:
 *		yuyong 2013/5/14	Created
 *******************************************************************************/
#ifndef __XML_WRITE_H
#define __XML_WRITE_H
#include <def.h>
typedef class xml_write_c *xml_write_ptr;

class xml_write_c
{
	public:
		xml_write_c(int32 file_num, string file_prefix, string file_path, int32 max_memory);
		~xml_write_c();
		void write_node( const string &node , const string &node_value );
		// ��Ƶ����
		void write_title(string title);
		// ��Ƶ����
		void write_alias(string alias);
		// ����
		void write_type(string type);
		// ���
		void write_kind(string kind);
		// ��ǩ
		void write_tag(string tag);
		// ����ʱ��
		void write_duration(string duration);
		// ���ҵ���
		void write_countries(string countries);
		// ����ʱ��
		void write_release_time(string release_time);
		// ͼƬurl
		void write_post(string post);
		// ����
		void write_director(string director);
		// ��Ա
		void write_actor(string actor);
		// ����
		void write_rating(string rating);
		// ��ϸ����
		void write_description(string desc);
		// �ܼ���
		void write_counts(string counts);
		// ��Դվ��
		void write_web_name(string web_name);
		// ��Ƶ�������ܴ���
		void write_views(string views);
		// �Ƿ��ǳ���Ƶ
		void write_longvideo(string longvideo);
		// ���Ӿ�͵�Ӱ�Ĳ�������
		void write_play_link(  string url );
		void write_play_link( vector<string> &url );
		void write_magnets();

		void write_seri_begin();
        void write_seri(string seq, string url, string time);
        void write_seri_end();
		
		// ��ʼ ����
		void write_begin();
		void write_end();
		// д�����
		void write_try_dump();
		void write_dump();
	private:
		int32 m_max_memory;
		string m_file_prefix;
		int32 m_file_num;
		string m_file_path;
		
		stringstream m_content;
};

#endif
