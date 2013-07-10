/*******************************************************************************
 *               Copyright (C), 2003-2013, KuaiBo All rights reserved
 -------------------------------------------------------------------------------
 * File Name	:	regular.h
 * Version		:	Initial Draft
 * Author		:	yuyong
 * Created		:	2013/4/13
 * Description	:   正则表达式
 -------------------------------------------------------------------------------
 * History:
 *		yuyong 2013/4/25	Created
 *******************************************************************************/
#ifndef __REGULAR_H
#define __REGULAR_H

bool regu_match(char *source, char *pattern, int id, char *dst, int length);
bool match_judge(char *source, char *pattern);
#endif

