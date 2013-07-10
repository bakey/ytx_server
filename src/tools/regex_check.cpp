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

int main(int argc, char **argv)
{
	if ( match_judge( argv[1], argv[2]) ) {
		cout << "[" << argv[1] << "] match [" << argv[2] << "]" << endl;
	}else {
		cout << "not match" << endl;
	}
	return 0;
}

