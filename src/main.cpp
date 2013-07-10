#include <def.h>
#include <log_class.h>
#include <mysql/mysql.h>
#include <config_class.h>
#include <xml_write.h>
#include <regular.h>
#include <html_class.h>
#include <utility_class.h>
#include <handle_letv.h>
#include <mysql_client.h>
#include <direct_traverse.h>
#include <handle_qq.h>
#include "Handler.h"
#include "handler_factory.h"
#include "ul_sign.h"
#include "ul_url.h"
#include "ul_url_sign.h"
#include "ParseCenter.h"
#include "cronoappender.h"
config_ptr g_conf;
log_ptr g_log;
html_c g_html;
static const int DEFAULT_XML_MAX_MEM = 2*1024*1024;
static const int MAX_SQL_COMMAND_LEN = 2048;
int g_db_table_count ;
string g_table_name;

string get_table_name( unsigned long long urlsign )
{
	string name;
	stringstream ss;
	ss << ( urlsign % g_db_table_count );
	name = "tbl_crawle_content_" + ss.str();
	return name;
}
static db_result_t *get_db_res( db_conn_t *g_mysql , int offset , int select_count , 
		unsigned long long sitesign , unsigned long long url_sign = 0 , int url_type = 0 ) {
	char sql_cmd[ MAX_SQL_COMMAND_LEN ];
	if ( url_sign != 0 ) {
		snprintf( sql_cmd , MAX_SQL_COMMAND_LEN , 
				"select url, page from %s where url_sign='%llu'" , g_table_name.c_str() , url_sign );
		if ( db_query( g_mysql , sql_cmd ) != 0  ){
			cout << "db query failed " << endl;
			return NULL;
		}
		db_result_t* db_result = db_store_result(g_mysql);
		return db_result;		
	}
	unsigned long cur_time = time(NULL);
	stringstream ss;
	ss << cur_time;
	string parse_condition = "last_parse_time=0 or last_crawle_time>last_parse_time" ;
	if ( url_type != 0 ) {
		snprintf( sql_cmd , MAX_SQL_COMMAND_LEN , 
				"select url, page from %s where url_type=%d and status=200 and page is not null and (%s) limit %d,%d", 
				g_table_name.c_str() , url_type , parse_condition.c_str() , offset , select_count );
	}else {
		snprintf( sql_cmd , MAX_SQL_COMMAND_LEN , 
				"select url, page from %s where site_sign='%llu' and status=200 and page is not null and (%s) limit %d,%d", 
				g_table_name.c_str() , sitesign , parse_condition.c_str() , offset , select_count );
	}
	com_writelog(COMLOG_DEBUG,"sql = %s" , sql_cmd );
	if ( db_query( g_mysql , sql_cmd ) != 0  ){
		com_writelog( COMLOG_WARNING,"db query failed");
		return NULL;
	}
	db_result_t* db_result = db_store_result(g_mysql);
	return db_result;	
}
static int init_log( const char *confname ) {
	com_registappender("CRONOLOG", 
            comspace::CronoAppender::getAppender, comspace::CronoAppender::tryAppender);
	if (com_loadlog("./", confname) != 0)
    {   
        fprintf(stderr, "confpath: %s\n", confname);
        fprintf(stderr, "fail to initialize com_log\n");
        return -1; 
    } 
	return 0;
}
db_conn_t *g_mysql = NULL;
int main(int argc, char **argv)
{
	if ( argc < 4 ) {
		cout << "Usage: " << argv[0] << "-d [xml data path] -s[site str] -n[parse page quantity] -i[increment process page count]" << endl;
		cout << "Example: ./main_exe -d'../data/letv' -s'letv/qq/funshion/pps'" << endl;
		return -1;
	}
	char ch = -1;
	char datapath[256];
	char flag[256];
	char site[256];
	string config_file;
	int parse_quantity = 0;
	int process_block = 0;
	int current_process = 0;
	unsigned long long input_url_sign = 0 ;
	char *stopstring;
	int cur_table_index = 0;
	while ( (ch = getopt(argc , argv , "d:s:n:c:i:f::u:b:t:")) != -1 ) {
		switch( ch ) {
		case 'd':
			strncpy( datapath , optarg , 256 );
			break;
		case 's':
			strncpy( flag , optarg , 256 );
			break;
		case 'n':
			parse_quantity = atoi( optarg );
			break;
		case 'c':
			config_file = (string)( optarg );
			break;
		case 'i':
			process_block = atoi( optarg );
			break;	
		case 'f':
			current_process = atoi( optarg );
			break;
		case 'u':
			input_url_sign = strtoull( optarg , &stopstring , 10 );
			break;
		case 'b':
			g_db_table_count = atoi( optarg );
			break;
		case 't':
			cur_table_index = atoi( optarg );
			break;
		case '?':
		default:
			cout << "unknown option : " << ch;
			break;	
		}
	}
	if ( init_log( "../conf/log.conf" ) != 0 ) {
		cout << "init log failed " << endl;
		exit(-1);
	}

	
	g_table_name = "tbl_crawle_content_";
	stringstream ss;
	ss << cur_table_index;
	g_table_name += ss.str();
    unsigned long long sitesign = 0;
    unsigned s1 = 0 , s2 = 0;

    if ( strcmp( flag , "letv") == 0 ) {
        ul_get_site_ex2( "so.letv.com/" , site , UL_MAX_SITE_LEN_EX2 );
    }else if ( strcmp( flag , "funshion") == 0 ) {
    	ul_get_site_ex2( "www.funshion.com/" , site , UL_MAX_SITE_LEN_EX2 );
    }else if ( strcmp(flag , "pps") == 0 ) {
		ul_get_site_ex2( "v.pps.tv/" , site , UL_MAX_SITE_LEN_EX2 );
	}else if ( strcmp(flag , "douban") == 0 ) {
		ul_get_site_ex2( "movie.douban.com/" , site , UL_MAX_SITE_LEN_EX2 );
	}else if ( strcmp(flag , "forum") == 0 ) {		
		site[0] = '\0';
	}
	if ( site[0] != '\0' ) {
		creat_sign_f64( site , strlen(site) , &s1 , &s2 );
		sitesign = (unsigned long long)(s2) << 32 | ((unsigned long long)s1); 
	}else {
		sitesign = 0;
	}
	com_writelog(COMLOG_DEBUG,"site %s sign = %llu" , site , sitesign );
	
	g_mysql = db_connect("127.0.0.1", "root", "root", "crawle_db", NULL, 3306);
	if (g_mysql == NULL)
	{
		cout<<"open mysql fail!\n"<<endl;
		return -1;
	}
	
	xml_write_c xml_tmp( 1 , "video" , datapath , DEFAULT_XML_MAX_MEM );
	ParseCenter *pCenter = new ParseCenter ;
	pCenter->loadConfig( config_file.c_str() );
	Handler *myhandler =  HandlerFactory::getHandler( flag , &xml_tmp ) ;
	if ( myhandler == NULL ) {
		cout << "get handler pointer failed " << endl;
		return -2;
	}
	myhandler->setParseCenter( pCenter );

	if ( input_url_sign != 0 ) {
		cout << "url sign = " << input_url_sign << endl;
		stringstream ss;
		ss << ( input_url_sign % g_db_table_count );
		g_table_name = "tbl_crawle_content_" + ss.str() ;
		db_result_t *db_result = get_db_res( g_mysql , 0 , 1 , 0 , input_url_sign );
		void *row_tmp = fetch_next_row(db_result);
		char *url = get_string(row_tmp, 1);
		char *page = get_string(row_tmp, 2);
		com_writelog( COMLOG_DEBUG , "parsing url = %s" ,url );
		myhandler->handle_html(url, page);
		db_close( &g_mysql );
		HandlerFactory::releaseHandler( myhandler );
		if ( pCenter != NULL ) {
			delete pCenter;
		}
		return 0;
	}
	//============================================================
	int offset = current_process;
	current_process = 0;

	while ( current_process < parse_quantity ) {
		int select_count = 0;
		int left_page = parse_quantity - current_process;
		if ( left_page > process_block && process_block > 0 ) {
			select_count = process_block;
		}else {
			select_count = left_page;
		}
		com_writelog( COMLOG_DEBUG , "we will select %d results" , select_count ) ;
		int url_type = 1;
		db_result_t *db_result = get_db_res( g_mysql , offset , select_count , sitesign , input_url_sign , url_type );
		if ( db_result == NULL ) {
			cout << "get db result failed :  " << mysql_error( (MYSQL *)g_mysql->conn ) << endl;
			return -3;
		} 
		int row_num = get_num_rows(db_result);
		com_writelog( COMLOG_DEBUG , "query result count = %d" , row_num );
		if ( row_num <= 0 ) {
			cout << "query no row " << endl;
			db_free_res(&db_result);
			break;
		}
		for (int i = 0; i < row_num; i++)
		{
			void *row_tmp = fetch_next_row(db_result);
			char *url = get_string(row_tmp, 1);
			char *page = get_string(row_tmp, 2);
			com_writelog( COMLOG_DEBUG , "parsing url = %s" , url );
			myhandler->handle_html(url, page);
		}
		current_process += row_num;
		offset += row_num;
		db_free_res(&db_result);
	}
	
	
	db_close( &g_mysql );
	HandlerFactory::releaseHandler( myhandler );
	if ( pCenter != NULL ) {
		delete pCenter;
	}
	
	/*cout << argv[2] << endl;
    html_c        m_html_doc;
    m_html_doc.html_open_file( argv[1] , "utf-8");
    xmlNodeSetPtr node_set = m_html_doc.html_xpath_multi_node( argv[2] );
    if ( node_set != NULL ) {
        for ( int i = 0 ; i < node_set->nodeNr ; i ++ ) {
            xmlNodePtr p = node_set->nodeTab[ i ];
			html_node_ptr children = p->children->next ;
			char *href = m_html_doc.html_node_value( children );
			if ( href != NULL ) 
				cout << href  << endl;
			else
				cout << "no href " << endl;
            //cout << xmlNodeGetContent( p ) << endl;
        }
    }
    /*int res = node == NULL;
    cout << res << endl;
    while ( node != NULL ) {
        string sval = utility_c::trim( m_html_doc.html_node_value( node ) );
        cout << sval << endl;
        node = node->next;
    }*/
	return 0;
}

