#include <xml_write.h>

xml_write_c::xml_write_c(int32 file_num, string file_prefix, string file_path, int32 max_memory)
{
	m_max_memory = max_memory;
	m_file_num = file_num;
	m_file_prefix = file_prefix;
	m_file_path = file_path;
	if (m_file_path[m_file_path.length() - 1] == '/')
	{
		m_file_path[m_file_path.length() - 1] = 0;
	}
	m_content.str("");
	m_content<< "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"; 
	m_content<<"<item_set>\n";
}

xml_write_c::~xml_write_c()
{
	if (m_content.str().length() > 10)
	{
		char file_name[500];
		snprintf(file_name, sizeof(file_name) - 1, 
				"%s/%s_%d", m_file_path.c_str(), m_file_prefix.c_str(), m_file_num);
		m_file_num++;
		fstream file_p;
		file_p.open(file_name, ios::out);
		if (file_p.is_open())
		{
			m_content<<"</item_set>\n";
			file_p<<m_content.str().c_str();
			file_p.close();
			m_content.str("");
			m_content<< "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n";
			m_content<<"<item_set>\n";
		}
		else
		{
			cout<<"open file fail!"<<errno<<":"<<strerror(errno)<<endl;
		}
	}
}
void xml_write_c::write_node( const string &node , const string &node_value )
{
	m_content << "<" << node << ">" << node_value << "</" << node << ">\n";
}
void xml_write_c::write_title(string title)
{
	m_content<<"<title>"<<title<<"</title>\n";
	return ;
}
void xml_write_c::write_alias(string alias)
{
	m_content<<"<alias>"<<alias<<"</alias>\n";
}
void xml_write_c::write_countries(string countries)
{
	m_content<<"<countries>"<<countries<<"</countries>\n";
}
void xml_write_c::write_release_time(string release_time)
{
	m_content<<"<pub_date>"<<release_time<<"</pub_date>\n";
}
void xml_write_c::write_post(string post)
{
	m_content<<"<post>"<<post<<"</posst>\n";
}
void xml_write_c::write_director(string director)
{
	m_content<<"<director>"<<director<<"</director>\n";
}

void xml_write_c::write_tag(string tag)
{
	m_content<<"<tag>"<<tag<<"</tag>\n";
}

void xml_write_c::write_type(string type)
{
	m_content<<"<type>"<<type<<"</type>\n";
}
void xml_write_c::write_duration(string duration)
{
	m_content<<"<duration>"<<duration<<"</duration>\n";
}
void xml_write_c::write_actor(string actor)
{
	m_content<<"<actor>"<<actor<<"</actor>\n";
}
void xml_write_c::write_rating(string rating)
{
	m_content<<"<rating>"<<rating<<"</rating>\n";
}
void xml_write_c::write_description(string desc)
{
	m_content<<"<desc>"<<desc<<"</desc>\n";
}
void xml_write_c::write_views(string views)
{
	m_content<<"<views>"<<views<<"</views>\n";
}
void xml_write_c::write_kind(string kind)
{
	m_content<<"<kind>"<<kind<<"</kind>\n";
}
void xml_write_c::write_longvideo(string longvideo)
{
	m_content<<"<longvideo>"<<longvideo<<"</longvideo>\n";
}
void xml_write_c::write_counts(string counts)
{
	m_content<<"<counts>"<<counts<<"</counts>\n";
}
void xml_write_c::write_web_name(string web_name)
{
	m_content<<"<web_name>"<<web_name<<"</web_name>\n";
}

void xml_write_c::write_play_link( string url )
{
	m_content << "<playList>\n";
	m_content<<"<playLink>\n";
	m_content << "<seq>1</seq>\n" ;
	m_content << "<duration>" << "</duration>\n";
	m_content<<"<defaultUrl>"<<url<<"</defaultUrl>\n";
	m_content<<"</playLink>\n";
	m_content << "</playList>\n";
}
void xml_write_c::write_play_link( vector<string> &url ) {
	m_content << "<playList>\n";
	size_t n = url.size();
//	size_t link_seq = url.size() - 1;
	for ( size_t i = 0 ; i < n ; i ++ ) {
		m_content << "<playLink>\n";
		m_content << "<seq>" << i+1 << "</seq>\n";
		m_content << "<duration>" << "</duration>\n";
		m_content << "<defaultUrl>\n" << url[i] << "</defaultUrl>\n";
		m_content << "</playLink>\n";		
	}
	m_content << "</playList>\n";	
}
void xml_write_c::write_magnets() {
	m_content << "<magnets>\n    <url></url>\n</magnets>\n";
}


void xml_write_c::write_seri_begin()
{
    m_content<<"<playlist>\n";
}
void xml_write_c::write_seri(string seq, string url, string time)
{
    m_content<<"<play>\n";
    m_content<<"<seq>"<<seq<<"</seq>\n";
    if (time.length() > 0)
    {
        m_content<<"<time>"<<time<<"</time>\n";
    }
    m_content<<"<url>"<<url<<"</url>\n";
    m_content<<"</play>\n";
}
void xml_write_c::write_seri_end()
{
    m_content<<"</playlist>\n";
}

void xml_write_c::write_try_dump()
{
	if (m_content.str().length() > (unsigned long)m_max_memory && m_content.str().length() > 10)
	{
		char file_name[500];
		snprintf(file_name, sizeof(file_name) - 1, 
				"%s/%s_%d", m_file_path.c_str(), m_file_prefix.c_str(), m_file_num);
		m_file_num++;
		fstream file_p;
		file_p.open(file_name, ios::out);
		if (file_p.is_open())
		{
			m_content<<"</item_set>\n";
			file_p<<m_content.str().c_str();
			file_p.close();
			m_content.str("");
			m_content<< "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"; 
			m_content<<"<item_set>\n";
		}
		else
		{
			cout<<"open file fail!"<<errno<<":"<<strerror(errno)<<endl;
		}
	}
}
void xml_write_c::write_dump()
{
	if (m_content.str().length() > 10)
	{
		char file_name[500];
		snprintf(file_name, sizeof(file_name) - 1, 
				"%s/%s_%d", m_file_path.c_str(), m_file_prefix.c_str(), m_file_num);
		m_file_num++;
		fstream file_p;
		file_p.open(file_name, ios::out);
		if (file_p.is_open())
		{
			m_content<<"</url_set>\n";
			file_p<<m_content.str().c_str();
			file_p.close();
			m_content.str("");
			m_content<<"<url_set>\n";
		}
		else
		{
			cout<<"open file fail!"<<errno<<":"<<strerror(errno)<<endl;
		}
	}
}

void xml_write_c::write_begin()
{
	m_content<<"<item>\n";
}
void xml_write_c::write_end()
{
	m_content<<"</item>\n";
	write_try_dump();
}
