/*******************************************************************************
 *               Copyright (C), 2003-2013, KuaiBo All rights reserved
 -------------------------------------------------------------------------------
 * File Name	:	mysql_client.h
 * Version		:	Initial Draft
 * Author		:	yuyong
 * Created		:	2013/5/16
 * Description	:	全局头文件，主要声明一些全局变量.
 -------------------------------------------------------------------------------
 * History:
 *		yuyong 2013/5/16	Created
 *******************************************************************************/
#ifndef MYSQL_CLIENT_H
#define MYSQL_CLIENT_H
#include <def.h>
#include <mysql/mysql.h>

// 数据库连接结构体
typedef struct db_conn_s{
	uint8		flag;		// 连接状态，0为未连接，1为已连接
	void*		conn;		// 连接结构体指针（mysql为MYSQL*类型， oracle为OCI_Connection*类型）
	char		db_ip[16];
	char		user_name[16];
	char		passwd[32];
	char		db_name[16];
	uint16		db_port;
	uint8		count;			//	 当前已连接失败次数（连接成功时清0）
}db_conn_t;

// 数据库查询结果集结构体
// 保存执行select查询语句后的结果集
typedef struct db_result_s{
	void*		res;				// 结果集指针（mysql为 MYSQL_RES*类型
}db_result_t;

// 连接数据库
db_conn_t*		db_connect(char* db_ip, char* user_name, char* passwd, char* db_name, char* host, int16 port);
// sql语句执行函数
int32			db_query(db_conn_t* db, char* sql);
// 取得查询结果集
db_result_t*	db_store_result(db_conn_t* db);
// 取得结果集记录行数
uint32	get_num_rows(db_result_t* db_result);
// 取得结果集记录字段数
uint32	get_num_rols(db_result_t* db_result);
// 取得结果集中下一条记录
void*	fetch_next_row(db_result_t* db_result);
// 取得一行记录中的对应字段值（int型）
int32	get_int(void* row, uint32 rol_nume);
// 取得一行记录中的对应字段值（char*型）
char*	get_string(void* row, uint32 rol_num);
// 取得一行记录中的对应字段值（double型）
double	get_double(void* row, uint32 rol_num);
// 取得最后一条由insert或update语句为AUTO_INCREMENT列生成的自增值
int32 	get_last_insert_id(db_conn_t* db);
// 释放结果集
int32	db_free_res(db_result_t** db_result);
// 重连数据库
int32	db_reconnect(db_conn_t* db);
// 关闭数据库
int32	db_close(db_conn_t** db);

#endif

