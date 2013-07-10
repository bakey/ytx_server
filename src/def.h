/*******************************************************************************
 *               Copyright (C), 2003-2013, KuaiBo All rights reserved
 -------------------------------------------------------------------------------
 * File Name	:	def.h
 * Version		:	Initial Draft
 * Author		:	yuyong
 * Created		:	2013/4/23
 * Description	:	公共头文件
 -------------------------------------------------------------------------------
 * History:
 *		yuyong 2013/4/23 	Created
 *******************************************************************************/
#ifndef __DEF_H
#define __DEF_H

#include <dirent.h>
#include <assert.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <strings.h>
#include <string>
#include <stdbool.h>
#include <stdint.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <wait.h>
#include <sys/file.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <fcntl.h>
#include <time.h>
#include <sys/time.h>
#include <semaphore.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <vector>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/select.h>
#include <map>
#include <fstream>
#include <sys/timeb.h>
#include <pthread.h>
#include <iostream>
#include <sstream>
#include <list>
#include <vector>
#include <md5.h>
#include <stdint.h>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/HTMLparser.h>

using namespace std;

typedef int8_t			int8;
typedef int16_t			int16;
typedef int32_t			int32;
typedef int64_t			int64;
typedef u_int8_t		uint8;
typedef u_int16_t		uint16;
typedef u_int32_t		uint32;
typedef u_int64_t		uint64;
typedef unsigned char 	uchar;
#define INT32_MAX 		(2147483647L)
#define UINT32_MAX 		(4294967295UL)
#define INT64_MAX 		(9223372036854775807LL)
#define UINT64_MAX 		(18446744073709551615ULL)
#define UINT8_MAX 		(255)
#define INT8_MAX		(128)
#define INT16_MAX		(32767)
#define UINT16_MAX		(65535U)

#define MAX_URL_LENGTH 4096000

#define ERROR_HEAD "<file:"<<__FILE__<<">"<<"<function:"<< \
					__FUNCTION__<<">"<<"<line:"<<__LINE__<<">"
#define NEW_CHECK(param)  do { \
			if (param == NULL) \
			{					\
				g_log->crit_stream()<<ERROR_HEAD<<"new error!"; \
				exit(-1);			\
			}					\
		}while(0)
static const int VIDEO_TYPE_MOVIE = 1;
static const int 			VIDEO_TYPE_TV    = 2;
static const int 			VIDEO_TYPE_COMIC = 3;
static const int 			VIDEO_TYPE_VARIETY  = 4;
static const int 			VIDEO_TYPE_ENT     = 5;
#endif



