/*******************************************************************************
 *               Copyright (C), 2003-2013, KuaiBo All rights reserved
 -------------------------------------------------------------------------------
 * File Name	:	mysql_client.h
 * Version		:	Initial Draft
 * Author		:	yuyong
 * Created		:	2013/5/16
 * Description	:	ȫ��ͷ�ļ�����Ҫ����һЩȫ�ֱ���.
 -------------------------------------------------------------------------------
 * History:
 *		yuyong 2013/5/16	Created
 *******************************************************************************/
#ifndef MYSQL_CLIENT_H
#define MYSQL_CLIENT_H
#include <def.h>
#include <mysql/mysql.h>

// ���ݿ����ӽṹ��
typedef struct db_conn_s{
	uint8		flag;		// ����״̬��0Ϊδ���ӣ�1Ϊ������
	void*		conn;		// ���ӽṹ��ָ�루mysqlΪMYSQL*���ͣ� oracleΪOCI_Connection*���ͣ�
	char		db_ip[16];
	char		user_name[16];
	char		passwd[32];
	char		db_name[16];
	uint16		db_port;
	uint8		count;			//	 ��ǰ������ʧ�ܴ��������ӳɹ�ʱ��0��
}db_conn_t;

// ���ݿ��ѯ������ṹ��
// ����ִ��select��ѯ����Ľ����
typedef struct db_result_s{
	void*		res;				// �����ָ�루mysqlΪ MYSQL_RES*����
}db_result_t;

// �������ݿ�
db_conn_t*		db_connect(char* db_ip, char* user_name, char* passwd, char* db_name, char* host, int16 port);
// sql���ִ�к���
int32			db_query(db_conn_t* db, char* sql);
// ȡ�ò�ѯ�����
db_result_t*	db_store_result(db_conn_t* db);
// ȡ�ý������¼����
uint32	get_num_rows(db_result_t* db_result);
// ȡ�ý������¼�ֶ���
uint32	get_num_rols(db_result_t* db_result);
// ȡ�ý��������һ����¼
void*	fetch_next_row(db_result_t* db_result);
// ȡ��һ�м�¼�еĶ�Ӧ�ֶ�ֵ��int�ͣ�
int32	get_int(void* row, uint32 rol_nume);
// ȡ��һ�м�¼�еĶ�Ӧ�ֶ�ֵ��char*�ͣ�
char*	get_string(void* row, uint32 rol_num);
// ȡ��һ�м�¼�еĶ�Ӧ�ֶ�ֵ��double�ͣ�
double	get_double(void* row, uint32 rol_num);
// ȡ�����һ����insert��update���ΪAUTO_INCREMENT�����ɵ�����ֵ
int32 	get_last_insert_id(db_conn_t* db);
// �ͷŽ����
int32	db_free_res(db_result_t** db_result);
// �������ݿ�
int32	db_reconnect(db_conn_t* db);
// �ر����ݿ�
int32	db_close(db_conn_t** db);

#endif

