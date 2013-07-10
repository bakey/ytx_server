/*******************************************************************************
 *               Copyright (C), 2003-2013, KuaiBo All rights reserved
 -------------------------------------------------------------------------------
 * File Name	:	xml_write.h
 * Version		:	Initial Draft
 * Author		:	yuyong
 * Created		:	2013/5/14
 * Description	:   xml_write类--用来把解析的关键数据写入xml的
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
		// 视频名称
		void write_title(string title);
		// 视频别名
		void write_alias(string alias);
		// 类型
		void write_type(string type);
		// 类别
		void write_kind(string kind);
		// 标签
		void write_tag(string tag);
		// 持续时间
		void write_duration(string duration);
		// 国家地区
		void write_countries(string countries);
		// 发布时间
		void write_release_time(string release_time);
		// 图片url
		void write_post(string post);
		// 导演
		void write_director(string director);
		// 演员
		void write_actor(string actor);
		// 分数
		void write_rating(string rating);
		// 详细描述
		void write_description(string desc);
		// 总集数
		void write_counts(string counts);
		// 来源站点
		void write_web_name(string web_name);
		// 视频被看的总次数
		void write_views(string views);
		// 是否是长视频
		void write_longvideo(string longvideo);
		// 电视剧和电影的播放链接
		void write_play_link(  string url );
		void write_play_link( vector<string> &url );
		void write_magnets();

		void write_seri_begin();
        void write_seri(string seq, string url, string time);
        void write_seri_end();
		
		// 开始 结束
		void write_begin();
		void write_end();
		// 写入磁盘
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
