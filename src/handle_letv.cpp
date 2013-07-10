#include <handle_letv.h>
#include <regular.h>

handle_letv::handle_letv(xml_write_ptr ptr)
{
	m_write_xml = ptr;
	m_detail_pattern = "so.letv.com/%";
    m_proc_movie = m_proc_tv = m_proc_comic = 0;
}

handle_letv::~handle_letv()
{
	m_write_xml = NULL;
}
bool handle_letv::handle_movie(char *url, char *html)
{
	if (url == NULL || html == NULL)
	{
		return false;
	}
	
	html_c html_doc;
	if (!html_doc.html_read_mem(html, "utf-8"))
	{
		return false;
	}
	
	m_write_xml->write_begin();
	html_node_ptr node = html_doc.html_xpath_node("/html/body/div[2]/div[2]/div/dl/dd/p/a");
	if (node != NULL ) {
		m_write_xml->write_title(html_doc.html_node_value(node));
	}else {
		cerr << "get title failed : " << url << endl;
	}
	
	m_write_xml->write_kind("movie");
	m_write_xml->write_longvideo("1");

	string director = "";
	node = html_doc.html_xpath_node("/html/body/div[2]/div[2]/div/dl/dd/p[2]/span/a");
    bool add_separator = false;
    int director_cnt = 0;
	while ( node != NULL)
	{
        string tmp = html_doc.html_node_value(node);
        string s = utility_c::trim( tmp );
        if ( s != "") {
            if ( director_cnt > 0 ) {
                director += "/";
            }
		    director += s ;
            director_cnt ++;
        }
		node = html_doc.html_node_next( node );
	}
	if ( director != "" ) {
		m_write_xml->write_director( director );
	}else {
		cerr << "get director failed : " << url << endl;
	}
	
	if ((node = html_doc.html_xpath_node("/html/body/div[2]/div[2]/div/dl/dd/p[4]/span")) != NULL)
	{
		m_write_xml->write_duration(html_doc.html_node_value(node));
	}else {
		cerr << "get duration failed : " << url << endl;
	}
	
	if ((node = html_doc.html_xpath_node("/html/body/div[2]/div[2]/div/dl/dd/p[5]/span/a")) != NULL)
	{
		m_write_xml->write_countries(html_doc.html_node_value(node));
	} else {
		cerr << "get countries failed : " << url << endl;
	}
	
	if ((node = html_doc.html_xpath_node("/html/body/div[2]/div[2]/div/dl/dd/p[7]/span/a")) != NULL)
	{
		m_write_xml->write_release_time(html_doc.html_node_value(node));
	} else {
		cerr << "get release time failed : " << url << endl;		
	}
	
	if ((node = html_doc.html_xpath_node("/html/body/div[2]/div[2]/div/dl/dd/p[10]")) != NULL)
	{
		m_write_xml->write_description(html_doc.html_node_value(node));
	}else {
		cerr << "get description failed : " << url << endl;
	}
	
	if ((node = html_doc.html_xpath_node("/html/body/div[2]/div[2]/div/dl/dt/p[2]/a")) != NULL)
	{
		m_write_xml->write_seri_begin();
		m_write_xml->write_seri("0", html_doc.html_node_prop(node, "href"), "");
		m_write_xml->write_seri_end();
	}else {
		cerr << "get seri failed : " << url << endl;		
	}
	
	if ((node = html_doc.html_xpath_node("/html/body/div[3]/div/div/a/img")) != NULL)
	{
		m_write_xml->write_post(html_doc.html_node_prop(node, "src"));
	}else {
		cerr << "get post failed : " << url << endl;
	}
	
	
	m_write_xml->write_web_name("letv.com");
	
	int i = 0;
	bool is_first = true;
	char actor[800] = { 0 };
	for (i = 0; i < 100; i++)
	{
		char tmp[500] = { 0 };
		snprintf(tmp, sizeof(tmp) - 1, "/html/body/div[2]/div[2]/div/dl/dd/p[3]/a[%d]", i + 1);
		if ((node = html_doc.html_xpath_node(tmp)) != NULL)
		{
			if (!is_first)
			{
				snprintf(actor + strlen(actor), sizeof(actor) - strlen(actor) - 1, "/");
			}
			snprintf(actor + strlen(actor), sizeof(actor) - strlen(actor) - 1, "%s", 
					html_doc.html_node_value(node));
			is_first = false;
		}
		else
		{
			break;
		}
	}
	m_write_xml->write_actor(actor);
	
	m_write_xml->write_end();
	return true;
}

bool handle_letv::handle_tv(char *url, char *html)
{
	
	if (url == NULL || html == NULL)
	{
		return false;
	}
	
	html_c html_doc;
	if (!html_doc.html_read_mem(html, "utf-8"))
	{
		return false;
	}
	
	m_write_xml->write_begin();
	html_node_ptr node = html_doc.html_xpath_node("/html/body/div[2]/div/div[3]/dl/dt");
	if (node != NULL)
	{
		m_write_xml->write_title(html_doc.html_node_value(node));
	}
	
	if ((node = html_doc.html_xpath_node("/html/body/div[3]/div/div/div/div[2]/i[2]")) != NULL)
	{
        string tmp = html_doc.html_node_value(node);
        string s = utility_c::trim( tmp );
        if ( s != "" ) {
    		m_write_xml->write_counts( s );
        }else {
            cout << "no counts , url : " << url << endl;
        }
	}
	
	m_write_xml->write_kind("tv");
	m_write_xml->write_longvideo("1");
	
	if ((node = html_doc.html_xpath_node("/html/body/div[2]/div/div[3]/dl/dd/p/a")) != NULL)
	{
		m_write_xml->write_director(html_doc.html_node_value(node));
	}
	
	if ((node = html_doc.html_xpath_node("/html/body/div[2]/div/div[3]/dl/dd/p[3]/a")) != NULL)
	{
		m_write_xml->write_countries(html_doc.html_node_value(node));
	}
	
	if ((node = html_doc.html_xpath_node("/html/body/div[2]/div/div[3]/dl/dd/p[4]/a")) != NULL)
	{
		m_write_xml->write_release_time(html_doc.html_node_value(node));
	}
	
	if ((node = html_doc.html_xpath_node("/html/body/div[2]/div/div[3]/dl/dd/p[7]")) != NULL)
	{
		m_write_xml->write_description(html_doc.html_node_value(node));
	}
	
	if ((node = html_doc.html_xpath_node("/html/body/div[3]/div/div/a/img")) != NULL)
	{
		m_write_xml->write_post(html_doc.html_node_prop(node, "src"));
	}
	 
	
	m_write_xml->write_web_name("letv.com");
	
	
	int i = 0;
	bool is_first = true;
	char actor[800] = { 0 };
	for (i = 0; i < 100; i++)
	{
		char tmp[500] = { 0 };
		snprintf(tmp, sizeof(tmp) - 1, "/html/body/div[2]/div/div[3]/dl/dd/p[2]/a[%d]", i + 1);
		if ((node = html_doc.html_xpath_node(tmp)) != NULL)
		{
			if (!is_first)
			{
				snprintf(actor + strlen(actor), sizeof(actor) - strlen(actor) - 1, "/");
			}
			snprintf(actor + strlen(actor), sizeof(actor) - strlen(actor) - 1, "%s", 
					html_doc.html_node_value(node));
			is_first = false;
		}
		else
		{
			break;
		}
	}
	m_write_xml->write_actor(actor);
	
	is_first = true;
	memset(actor, 0, sizeof(actor));
	for (i = 0; i < 100; i++)
	{
		char tmp[500] = { 0 };
		snprintf(tmp, sizeof(tmp) - 1, "/html/body/div[2]/div/div[3]/dl/dd/p[5]/a[%d]", i + 1);
		if ((node = html_doc.html_xpath_node(tmp)) != NULL)
		{
			if (!is_first)
			{
				snprintf(actor + strlen(actor), sizeof(actor) - strlen(actor) - 1, "/");
			}
			snprintf(actor + strlen(actor), sizeof(actor) - strlen(actor) - 1, "%s", 
					html_doc.html_node_value(node));
			is_first = false;
		}
		else
		{
			break;
		}
	}
	m_write_xml->write_tag(actor);
	
	
	
	is_first = true;
	m_write_xml->write_seri_begin();
	for (i = 0; i < 1000; i++)
	{
		char tmp[500] = { 0 };
		snprintf(tmp, sizeof(tmp) - 1, "/html/body/div[2]/div[2]/div/div[2]/div/div[2]/dl[%d]/dd/p/a", i + 1);
		if ((node = html_doc.html_xpath_node(tmp)) != NULL)
		{
			m_write_xml->write_seri(html_doc.html_node_value(node), html_doc.html_node_prop(node, "href"), "");	
			is_first = false;
		}
		else
		{
			break;
		}
	}
	m_write_xml->write_seri_end();
	
	m_write_xml->write_end();
	return true;
}

bool handle_letv::handle_html(char *url, char *html)
{
	if (url == NULL || html == NULL)
	{
		cerr << "invalid input params" << endl;
		return false;
	}
	
	utility_c::util_url_format(url);
	if (match_judge(url, "^so.letv.com/film/*"))
	{
        ++ m_proc_movie ;
		return handle_movie(url, html);	
	}
	else if (match_judge(url, "^so.letv.com/tv/*"))
	{
        ++ m_proc_tv;
		return handle_tv(url, html);
	}
    else if ( match_judge( url , "^so.letv.com/comic/*") ) {
        ++ m_proc_comic ;
        return true;
    }	
	return false;
}
const char *handle_letv::getPattern(){
	return m_detail_pattern.c_str();
}
const char *handle_letv::getLetvSqlCmd() {
	return NULL;	
}


