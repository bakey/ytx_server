#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "direct_traverse.h"

/* 判断是否为目录 */
static int IS_DIR(const char *path)
{
	struct stat st;
	lstat(path, &st);
	return S_ISDIR(st.st_mode);
}

static int direct_traverse_core(const char *path, int recurs, int (*visit)(char *file, void *handle_ptr, void *bak_path), 
				void *handle_ptr, void *bak_path)
{
	DIR *pdir;
	struct dirent *pdirent;
	char temp[256];
	pdir = opendir(path);
	if (pdir)
	{
		while (pdirent = readdir(pdir))
		{
			if (strcmp(pdirent->d_name, ".") == 0 ||
						strcmp(pdirent->d_name, "..") == 0)
				continue;
			if (strlen(path) == 1 && path[0] == '/')
			{
				snprintf(temp, 256, "%s%s", path, pdirent->d_name);
			}
			else
			{
				snprintf(temp, 256, "%s/%s", path, pdirent->d_name);
			}
			
			if (IS_DIR(temp) && recurs)
			{
				direct_traverse_core(temp, recurs, visit, handle_ptr, bak_path);
			}
			else
			{
				visit(temp, handle_ptr, bak_path);
			}
		}
	}
	else
	{
		fprintf(stderr, "opendir error: %s\n", path);
		return -1;
	}
	closedir(pdir);
	return 0;
}

int direct_traverse(const char *direct, int recurs, int (*visit)(char *file, void *handle_ptr, void *bak_path), 
			void *handle_ptr, void *bak_path)
{
	if (direct == NULL || strlen(direct) < 1)
	{
		return -1;
	}
	int len;
	char temp[256];
	
	/* 去掉末尾的'/' */
	len = strlen(direct);
	strcpy(temp, direct);
	if (temp[len - 1] == '/' && len != 1)
		temp[len - 1] = '\0';
	
	if (IS_DIR(temp))
	{
		direct_traverse_core(temp, recurs, visit, handle_ptr, bak_path);
	}
	else
	{
		visit(temp, handle_ptr, bak_path);
	}
	
	return 0;
}
