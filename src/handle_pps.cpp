#include <handle_pps.h>
#include <regular.h>
#include <global.h>
#include "uconv.h"

string handle_pps::m_my_sitename = "pps";
handle_pps::handle_pps(xml_write_ptr ptr )
{
	m_write_xml = ptr;
	mPCenter = NULL;
	m_page_buffer = NULL;
	m_proc_movie = m_proc_tv = m_proc_comic = m_proc_variety = 0;
}
handle_pps::~handle_pps()
{
	m_write_xml = NULL;
	if ( m_page_buffer != NULL ) {
		delete []m_page_buffer;
		m_page_buffer = NULL;
	}
	for ( size_t i = 0 ; i < m_pattern_conf.size() ; ++ i ) {
		if ( m_pattern_conf[i] != NULL ) {
			delete m_pattern_conf[i];
		}
	}
}

bool handle_pps::handle_html(char *url, char *html)
{
	if (url == NULL || html == NULL)
	{
		return false;
	}	
	utility_c::util_url_format(url);
	string urlPattern = mPCenter->getMainConfig()->getString("douban_url_pattern" , "");
	if ( urlPattern != "" && match_judge(url, (char*)urlPattern.c_str() ) )
	{
		return handle_video(url, html);	
	}
	return false;
}
void handle_pps::setParseCenter( ParseCenter *center ) {
    mPCenter = center;
  Configuration *config = mPCenter->getMainConfig();
  int pagePatternCnt = config->getInt("pps_page_pattern_count");
  for( int i = 0 ; i < pagePatternCnt ; ++ i ) { 
        char key[128];
        snprintf( key , 128 , "pps_page_pattern_xpath_%d" , i );
        string pattern = config->getString( key , "");
        m_page_patterns.push_back( pattern );
        snprintf( key , 128 , "pps_page_pattern_value_%d" , i );
        string pvalue = config->getString( key , "" );
        m_page_patterns_value.push_back( pvalue );
        snprintf( key , 128 , "pps_page_pattern_map_type_%d" , i );
        int mtype = config->getInt( key , 0 );
        m_pattern_map_type.push_back( mtype );

        snprintf( key , 128 , "pps_page_pattern_file_%d" , i );
        string type_conf_name = config->getString( key , "" );
        assert( type_conf_name != "" );
        Configuration *config = new Configuration;
        assert( config->loadPagePattern( type_conf_name.c_str() , type_conf_name.length() ) );
        m_pattern_conf.push_back( config );
    } 
  	m_page_buffer = new char[ MAX_UTF8_HTML_PAGE_LEN ];
	m_cur_page_buffer_len = MAX_UTF8_HTML_PAGE_LEN;
}
bool handle_pps::write_single_node( const nodePatternMap::const_iterator &pit )
{
	html_node_ptr node = m_html_doc.html_xpath_node( (char *)pit->second._XPathPattern.c_str() );
	if ( node == NULL ) {
        cout << "find node failed for : " << pit->first << " , pattern = " << pit->second._XPathPattern << endl;
        m_write_xml->write_node( pit->first , "" );
		return false;
	}
	char *value = m_html_doc.html_node_value( node );
	if ( value == NULL ) {
        cout << "get value of node failed in : " << pit->first << ",pattern = " << pit->second._XPathPattern << endl;
        m_write_xml->write_node( pit->first , "" );
		xmlFree( value );
		m_html_doc.html_free_xpath_object();
		return false;
	}
	string ultimate_content = utility_c::trim( value );
	if ( pit->first == "pub_date" ) {
		ultimate_content += "年";
	}
	m_write_xml->write_node( pit->first , ultimate_content );
	xmlFree( value );
	m_html_doc.html_free_xpath_object();
	return true;
}

bool handle_pps::write_list_node( const nodePatternMap::const_iterator &pit )
{
	html_node_ptr node = m_html_doc.html_xpath_node( (char *)pit->second._XPathPattern.c_str() );
	if ( node == NULL ) {
        cout << "find node failt for " << pit->first << ",pattern = " << pit->second._XPathPattern << endl;
        m_write_xml->write_node(pit->first , "" );
		return false;
	}
	string tstr = "";
	string res_str = "";
	int count = 0;
	char *pValue = NULL;
	while ( node != NULL ) {
		string tmpstr = (pValue = m_html_doc.html_node_value( node )) == NULL ? 
									(string)"" : (string)pValue ;
		tmpstr = utility_c::trim( tmpstr );
		if ( tmpstr != "" ) {
			tstr += tmpstr;
			tstr += "/";
			++ count;
		}
		node = m_html_doc.html_node_next( node );
		if ( pValue != NULL ) {
			xmlFree( pValue );
		}
	}
	vector<string> elements;
	utility_c::split( tstr , "|/" , elements );
	for( size_t i = 0 ; i < elements.size() ; i ++ ) {
		res_str += elements[ i ];
		if ( i < elements.size() -1 ) {
			res_str += "/";
		}
	}
	m_html_doc.html_free_xpath_object();
	m_write_xml->write_node(pit->first , res_str );
	return true;
}
bool handle_pps::write_empty_node( const nodePatternMap::const_iterator &pit )
{
	m_write_xml->write_node(pit->first , "" );
	return true;
}

bool handle_pps::write_static_node( const nodePatternMap::const_iterator &pit )
{
	m_write_xml->write_node( pit->first , pit->second._XPathPattern.c_str() );
	return true;
}

bool handle_pps::write_href_node( const nodePatternMap::const_iterator &pit )
{
	html_node_ptr node = m_html_doc.html_xpath_node( (char *)pit->second._XPathPattern.c_str() );
	if ( node == NULL ) {
		return false;
	}
	char *href = m_html_doc.html_node_prop( node , "href" );
	if ( href == NULL ) {
		m_html_doc.html_free_xpath_object();
		return false;
	}
	m_write_xml->write_node( pit->first , href );	
	xmlFree(href);
	m_html_doc.html_free_xpath_object();
	return true;
}
bool handle_pps::write_play_link( const nodePatternMap::const_iterator &pit )
{
    string play_link_str = "";
	html_node_ptr node = m_html_doc.html_xpath_node( (char *)pit->second._XPathPattern.c_str() );
	if ( node == NULL ) {
        play_link_str = "\n<playLink>\n<seq></seq>\n<duration></duration>\n<defaultUrl>\n</defaultUrl>\n</playLink>\n";
        m_write_xml->write_node( "playList" , play_link_str );
		return false;
	}
    vector<string> play_link;
	while ( node != NULL ) {
        html_node_ptr anchor_node = node->children;
        if ( anchor_node != NULL && strncmp( (char *)anchor_node->name , "text" , 4 ) == 0 ) {
            anchor_node = anchor_node->next;
        }
        if ( anchor_node != NULL && strncmp( (char *)anchor_node->name , "a" , 1 ) == 0 ) {
            char *href = m_html_doc.html_node_prop( anchor_node , "href" );
            if ( href != NULL ) {
                string link = href;
                play_link.push_back( link );
            }
			xmlFree( href );
        }
        node = m_html_doc.html_node_next( node );
    }
	if ( play_link.size() <= 0 ) {
		cout << "get empty play link " << endl;
	}
    int seq = 1;
    for( vector<string>::iterator it = play_link.begin() ; it != play_link.end() ; ++ it ) {
        play_link_str += "\n    <playLink>\n    <seq>";
        stringstream ss;
        ss << seq;
        play_link_str += ss.str() ;
        play_link_str += "</seq>\n";
        play_link_str += "    <duration></duration>\n";
        play_link_str += "    <defaultUrl>\n";
        play_link_str += "        " + *it + "\n";
        play_link_str += "    </defaultUrl>\n    </playLink>\n";
        ++ seq;
    }
    m_write_xml->write_node( "playList" , play_link_str );
	stringstream ss;
	ss << play_link.size();
	m_write_xml->write_node("total" , ss.str() );
	m_write_xml->write_node("upInfo" , ss.str() );
	m_html_doc.html_free_xpath_object();
    return true;
}
bool handle_pps::write_src_link( const nodePatternMap::const_iterator &pit )
{
    html_node_ptr node = m_html_doc.html_xpath_node( (char *)pit->second._XPathPattern.c_str() );
    if ( node == NULL ) { 
        return false;
    }
    char *src_link = m_html_doc.html_node_prop( node , "src" );
    if ( src_link != NULL ) {
        string lk = ( string) src_link;
        lk = utility_c::trim( lk );
        if ( lk != "" ) {
            m_write_xml->write_node( pit->first , lk );
			xmlFree( src_link );
			m_html_doc.html_free_xpath_object();
            return true;
        }
    }
	m_html_doc.html_free_xpath_object();
    return false;
}
bool handle_pps::write_keyword_filter( const nodePatternMap::const_iterator &pit )
{
	html_set_ptr node_set = m_html_doc.html_xpath_multi_node( 
			(char *)pit->second._XPathPattern.c_str() );
	string res_str = "";
	vector<string> elements;
	elements.clear();
	if ( node_set == NULL ) {
		m_write_xml->write_node( pit->first , "" );
		return true;
	}
	for ( int i = 0 ; i < node_set->nodeNr ; i ++ ) {
		html_node_ptr children = node_set->nodeTab[ i ]->children->next ;
		if ( children != NULL && 
			strcmp((char *)children->name , pit->second._ChildPath.c_str() ) == 0 ) {
			char *value = m_html_doc.html_node_value( children );
			string tstr = "";
			string value_str = value;
			xmlFree( value );
			if ( strstr( value_str.c_str() , pit->second._keyWord.c_str() ) != NULL ) {
				html_node_ptr node = children->next ;
				while ( node != NULL ) {
					if ( strcmp((char *)node->name , "a") == 0 ) {
						string tmpstr = (value = m_html_doc.html_node_value( node )) == NULL ? 
						(string)"" : (string)value ;
						tmpstr = utility_c::trim( tmpstr );
						if ( tmpstr != "" ) {
							tstr += tmpstr;
							tstr += "/";
						}
						if ( value != NULL ) {
							xmlFree( value );
						}
					}
					node = m_html_doc.html_node_next( node );
				}
				utility_c::split( tstr , "|/" , elements );
				for( size_t i = 0 ; i < elements.size() ; i ++ ) {
					res_str += elements[ i ];
					if ( i < elements.size() -1 ) {
						res_str += "/";
					}
				}
			}
		}
	}
	if ( pit->first == "pub_date" ) {
		res_str += "年";
	}
	m_write_xml->write_node( pit->first , res_str );
	m_html_doc.html_free_xpath_object();
	return true;
}
bool handle_pps::write_xml(char *url, char *html , char *type , Configuration *config ){
	m_write_xml->write_begin();
	m_write_xml->write_node( "web_name" , "pps.tv" );
	m_write_xml->write_node( "type" , type );
	/*Configuration *myPageConf = mPCenter->getConfigBySite( m_my_sitename );
	if ( myPageConf == NULL ) {
		return false;
	}*/
	const nodePatternMap &pmap = config->getNodePatternMap();

	nodePatternMap::const_iterator it = pmap.begin();
	for(  ; it != pmap.end() ; ++ it ) {
		switch( it->second._pathType )
		{
		case NODE_TYPE_SINGLE_VALUE:
			write_single_node( it );
			break;
		case NODE_TYPE_LIST_VALUE:
			write_list_node( it );
			break;
		case NODE_TYPE_EMPTY_CONTENT:
			write_empty_node( it );
			break;
		case NODE_TYPE_STATIC_VALUE:
			write_static_node( it );
			break;
		case NODE_TYPE_HREF:
			write_href_node( it );
			break;
        case NODE_TYPE_PLAYLINK:
            write_play_link( it );
            break;
        case NODE_TYPE_SRC_LINK:
            write_src_link( it );
            break;
		case NODE_TYPE_KEYWORD_FILTER:
			write_keyword_filter( it );
			break;
		default :
			cout << "unknown pattern map type " << endl;
			break;

		}
	}
	m_write_xml->write_magnets();
    m_write_xml->write_end();
    return true ;
}

bool handle_pps::handle_video(char *url, char *html)
{	
	int src_len = strlen( html );
	int dst_len = src_len * 3;
	if ( dst_len > m_cur_page_buffer_len) {
		m_cur_page_buffer_len = dst_len;
		delete []m_page_buffer;
		m_page_buffer = new char[ m_cur_page_buffer_len ];
	}
	if ( !is_utf8( html , src_len , 1 ) ) {
		dst_len = gbk_to_utf8( html , src_len , m_page_buffer , m_cur_page_buffer_len , 0 );
	}else {
		memcpy( m_page_buffer , html , src_len );
		dst_len = src_len;
	}
	if (!m_html_doc.html_read_mem( m_page_buffer , "utf-8"))
	{
		return false;
	}
    int pagePatternCnt = m_page_patterns_value.size();
	for ( int i = 0 ; i < pagePatternCnt ; i ++ ) {
		html_node_ptr node = m_html_doc.html_xpath_node( (char *)m_page_patterns[i].c_str() );
		if ( node == NULL ) {
			continue;
		}
		char *node_val = m_html_doc.html_node_value(node);
		if ( node_val == NULL ) {
			m_html_doc.html_free_xpath_object();
			continue;
		}
		string s = utility_c::trim( node_val );
		if ( s == "" ) {
			xmlFree( node_val );
			m_html_doc.html_free_xpath_object();
			continue;
		}
		xmlFree( node_val );
		m_html_doc.html_free_xpath_object();
        Configuration *config = m_pattern_conf[i];
		if ( s == m_page_patterns_value[i] ) {
			int mtype = m_pattern_map_type[ i ];
			switch ( mtype )
			{
			case PAGE_TYPE_MOVIE:
                ++ m_proc_movie;
				return write_xml(url , m_page_buffer , "movie" , config );
				break;
			case PAGE_TYPE_TV:
                ++ m_proc_tv;
				return write_xml( url , m_page_buffer , "tv" , config );
				break;
			case PAGE_TYPE_COMIC:
                ++ m_proc_comic;
                return write_xml( url , m_page_buffer , "cartoon" , config );
				break;
			case PAGE_TYPE_VARIETY:
                ++ m_proc_variety;
                return write_xml( url , m_page_buffer , "show" , config );
				break;
			default:
				cout << "unknown page type" << endl;
				break;
			}
		}
	}	
	return true;
}

