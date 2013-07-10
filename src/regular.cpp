#include <regular.h>
#include <pcre/pcre.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

bool regu_match(char *source, char *pattern, int id, char *dst, int length)
{
	pcre * pcre_ptr = NULL;
	int ovector[40];
	
	char *err_msg = NULL;
	int offset = -1;
	pcre_ptr = pcre_compile(pattern, 0, (const char**)&err_msg, (int *)&offset, NULL);
	if (pcre_ptr == NULL)
	{
		fprintf(stderr, "regular match err_msg=%s, offset=%d\n", err_msg, offset);
		return false;
	}
	
	if (pcre_exec(pcre_ptr, NULL, source, strlen(source), 0, 0, ovector, 40) < 0)
	{
		//fprintf(stderr, "can not match, source is %s, pattern is %s\n", source, pattern);
		pcre_free(pcre_ptr);
		return false;
	}
	
	if (id >= 20)
	{
		fprintf(stderr, "id shoule be < 20\n");
		return false;
	}
	
	int re_length = ovector[2 * id + 1] - ovector[2 * id];
	if (re_length + 1 > length)
	{
		fprintf(stderr, "length is too small, need %d\n", re_length + 1);
		pcre_free(pcre_ptr);
		return false;
	}
	char *re_ch = source + ovector[2 * id];
	memcpy(dst, re_ch, re_length);
	dst[re_length] = 0;
	pcre_free(pcre_ptr);
	return true;
}

bool match_judge(char *source, char *pattern)
{
	if (source == NULL || pattern == NULL)
	{
		return false;
	}
	pcre * pcre_ptr = NULL;
	int ovector[40];
	
	char *err_msg = NULL;
	int offset = -1;
	pcre_ptr = pcre_compile(pattern, 0, (const char**)&err_msg, (int *)&offset, NULL);
	if (pcre_ptr == NULL)
	{
		fprintf(stderr, "regular match err_msg=%s, offset=%d\n", err_msg, offset);
		return false;
	}
	
	if (pcre_exec(pcre_ptr, NULL, source, strlen(source), 0, 0, ovector, 40) < 0)
	{
		//fprintf(stderr, "can not match, source is %s, pattern is %s\n", source, pattern);
		pcre_free(pcre_ptr);
		return false;
	}
	pcre_free( pcre_ptr );

	return true;
}

