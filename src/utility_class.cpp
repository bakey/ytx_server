#include <utility_class.h>
bool utility_c::util_url_format(char *source_url)
{
	if (source_url == NULL)
	{
		return false;
	}
	
	int length_source = strlen(source_url);
	
	char *url = "http://www.";
	int length = strlen(url);
	int i;
	bool flag = true;;
	if (length_source > length)
	{
		i = 0;
		flag = true;
		for (i = 0; i < length; i++)
		{
			if (source_url[i] != url[i])
			{
				flag = false;
				break;
			}
		} 
		
		if (flag)
		{
			memmove(source_url, source_url + strlen(url), strlen(source_url) - strlen(url));
			source_url[strlen(source_url) - strlen(url)] = 0;
			return true;
		}
	}
	
	url = "http://";
	length = strlen(url);
	if (length_source >= length)
	{
		flag = true;
		for (i = 0; i < length; i++)
		{
			if (source_url[i] != url[i])
			{
				flag = false;
				break;
			}
		}
		
		if (flag)
		{
			memmove(source_url, source_url + length, strlen(source_url) - length);
			source_url[strlen(source_url) - strlen(url)] = 0;
			return true;
		}
	}
	
	url = "www.";
	length = strlen(url);
	if (length_source >= length)
	{
		flag = true;
		for (i = 0; i < length; i++)
		{
			if (source_url[i] != url[i])
			{
				flag = false;
				break;
			}
		}
		
		if (flag)
		{
			memmove(source_url, source_url + length, strlen(source_url) - length);
			source_url[strlen(source_url) - strlen(url)] = 0;
			return true;
		}
	}
	
	return false;
}

bool utility_c::util_url_http(char *url)
{
	if (url == NULL)
	{
		return false;
	}
	
	if ((url[0]||32 == 'h') && (url[1] || 32 == 't') && (url[2] || 32 == 't') &&
			(url[3]||32 == 'p') && (url[4] == ':') && (url[5] == '/') && (url[6] == '/'))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool utility_c::util_url_domain(char *url, char *domain)
{
	if (url == NULL || domain == NULL)
	{
		return false;
	}
	
	if (util_url_http(url))
	{
		url = url + strlen("http://");
	}
	while (*url != '/' && *url != '?' && *url != '\0')
	{
		*domain = *url;
		domain++;
		url++;
	}
	
	*domain = '\0';
	
	return true;
}

bool utility_c::util_url_pwd(char *url, char *pwd)
{
	if (url == NULL || pwd == NULL)
	{
		return false;	
	}
	
	char *url_tmp = url;
	
	url = url + strlen(url) - 1;
	
	if (util_url_http(url_tmp))
	{
		url_tmp = url_tmp + strlen("http://");
	}
	
	while (url > url_tmp && *url != '/')
	{
		url--;	
	}
	
	if (url == url_tmp)
	{
		strcpy(pwd, url_tmp);
		strcat(pwd, "/");
	}
	else
	{
		while (url_tmp != url)
		{
			*pwd = *url_tmp;
			url_tmp++;
			pwd++;
		}
		*pwd = '/';
		pwd++;
		*pwd = 0;
	}
	
	return true;
}

bool utility_c::util_url_upper(char *url, char *upper)
{
	if (url == NULL || upper == NULL)
	{
		return false;
	}
	
	if (util_url_http(url))
	{
		url = url + strlen("http://");
	}
	
	char pwd[800] = { 0 };
	util_url_pwd(url, pwd);
	
	char *url_tmp = pwd + strlen(pwd) - 2;
	while (*url_tmp != '/' && url_tmp > pwd)
	{
		url_tmp--;
	}
	
	if (url_tmp == pwd)
	{
		return false;
	}
	else
	{
		url_tmp++;
		*url_tmp = 0;
		strcpy(upper, pwd);
		return true;
	}
	
	return true;
}

bool utility_c::util_url_abs(char *r_url, char *r_path, char *a_url)
{
	if (r_url == NULL || r_path == NULL || a_url == NULL)
	{
		return false;
	}
	
	if (*r_path == '/')
	{
		char domain[800] = { 0 };
		util_url_domain(r_url, domain);
		strcat(a_url, domain);
		strcat(a_url, r_path);
	}
	else if (r_path[0] == '.' && r_path[1] == '.' && r_path[2] == '/')
	{
		char domain[800] = { 0 };
		util_url_upper(r_url, domain);
		strcat(a_url, domain);
		strcat(a_url, r_path + 3);
	}
	else if (r_path[0] == '.' && r_path[1] == '/')
	{
		char domain[800] = { 0 };
		util_url_pwd(r_url, domain);
		strcat(a_url, domain);
		strcat(a_url, r_path + 2);
	}
	
	return true;
}
string utility_c::trim( const string &str )
{
    string ret = "";
    for ( size_t i = 0 ; i < str.length(); ++ i ) {
        if ( str[i] == '\n' || str[i] == '\t' || str[i] == ' ' || str[i] == '\r') {
            continue;
        }else {
            ret += str[i];
        }
    }
    return ret;
}
int utility_c::split( const string str , char spliter , vector<string> &element)
{
	size_t start_pos = 0;
	size_t next_pos = 0;
	while ( ( next_pos = str.find( spliter , start_pos )) != string::npos ) {
		element.push_back( str.substr( start_pos , next_pos - start_pos ) ) ;
		start_pos = next_pos + 1;
	}
	element.push_back( str.substr( start_pos , str.length() - start_pos ));
	return (int)element.size();
}

int utility_c::split( const string str , string spliters , vector<string> &element )
{
	size_t start_pos = 0;
	//size_t next_pos = 0;
	size_t current = 0;
	while ( current < str.size() ) {
		if ( spliters.find( str[current] ) != string::npos ) {
            string sstr = str.substr( start_pos , current-start_pos );
            if ( sstr.length() > 0 ) {
    			element.push_back( str.substr( start_pos , current-start_pos ) );
            }
			start_pos = current + 1;
		}
		++ current;
	}
	return (int)element.size();
}

int utility_c::dump_file( char *content , int clen )
{
	FILE *fp = fopen( "test.html" , "wb" );
	if ( fp != NULL ) {
		return fwrite( content , clen , 1 , fp );
	}else {
		return -1;
	}

}
unsigned long long utility_c::get_url_sign( const char *str , size_t len )
{
	unsigned s1 = 0 , s2 = 0;
	creat_sign_f64( (char *)str , len , &s1 , &s2 );
	unsigned long long url_sign = 0;
	url_sign = 	(unsigned long long)(s2) << 32 | ((unsigned long long)s1);
	return url_sign;
}




