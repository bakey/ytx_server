/*******************************************************************************
 *               Copyright (C), 2003-2013, KuaiBo All rights reserved
 -------------------------------------------------------------------------------
 * File Name	:	md5.h
 * Version		:	Initial Draft
 * Author		:	yuyong
 * Created		:	2013/4/23
 * Description	:   md5函数--用来求字符串的md5值
 -------------------------------------------------------------------------------
 * History:
 *		yuyong 2013/4/23	Created
 *******************************************************************************/
#ifndef __MD5_H
#define __MD5_H

#include <inttypes.h>

bool md5_value(char *str, uint64_t *ptr);

#endif

