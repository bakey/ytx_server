#include <mysql_client.h>

static db_conn_t* cc_mysql_connect(char* db_ip, char* user_name, char* passwd, char* db_name,int16 port);
static int32  cc_mysql_query(db_conn_t* db, char* sql);
static db_result_t*	cc_mysql_store_result(db_conn_t* db);
static uint32 cc_mysql_get_num_rows(db_result_t* db_result);
static uint32 cc_mysql_get_num_rols(db_result_t* db_result);
static void* cc_mysql_fetch_next_row(db_result_t* db_result);
static int32 cc_mysql_get_int(void* row, uint32 rol_num);
static char* cc_mysql_get_string(void* row, uint32 rol_num);
static double cc_mysql_get_double(void* row, uint32 rol_num);
static int32 cc_mysql_insert_id(db_conn_t* db);
static int32 cc_mysql_reconnect(db_conn_t* db);
static int32 cc_mysql_free_res(db_result_t** db_result);
static int32 cc_mysql_close(db_conn_t** db);


// �������ݿ⺯���� �������ӽṹ�壬����ʧ�ܷ���NULL
db_conn_t* db_connect(char* db_ip, char* user_name, char* passwd, char* db_name, char* host, int16 port)
{
	return cc_mysql_connect(db_ip, user_name, passwd, db_name, port);
}

// sql���ִ�к���������ִ�н����0ִ�гɹ���-1ִ��ʧ��
int32	db_query(db_conn_t* db, char* sql)
{
	return cc_mysql_query(db, sql);
}

// ȡ�ò�ѯ����� ����ִ��select���֮��ִ�У�����ȡʧ�ܷ���NULL
db_result_t* db_store_result(db_conn_t* db)
{
	return cc_mysql_store_result(db);
}

// ȡ�ý������¼����������oracle, ���ص�ǰ��fetch���ļ�¼������
uint32 get_num_rows(db_result_t* db_result)
{
	return cc_mysql_get_num_rows(db_result);
}

// ȡ�ý������¼�ֶ���
uint32 get_num_rols(db_result_t* db_result)
{
	return cc_mysql_get_num_rols(db_result);
}

// ȡ�ý��������һ����¼������void*ָ��
// �����ø�ָ����ȡ�ñ�����¼���ֶε�ֵ
void* fetch_next_row(db_result_t* db_result)
{
	return cc_mysql_fetch_next_row(db_result);
}

// ȡ��һ�м�¼�еĶ�Ӧ�ֶ�ֵ��int�ͣ���rowָ��Ϊfetch_next_row��������
// rol_num Ӧ������get_num_rols�����ķ���ֵ�����������ڴ�Խ��
int32 get_int(void* row, uint32 rol_num)
{
	return cc_mysql_get_int(row, rol_num);
}

// ȡ��һ�м�¼�еĶ�Ӧ�ֶ�ֵ��char*�ͣ���rowָ��Ϊfetch_next_row��������
// rol_num Ӧ������get_num_rols�����ķ���ֵ�����������ڴ�Խ��
char* get_string(void* row, uint32 rol_num)
{
	return cc_mysql_get_string(row, rol_num);
}

double get_double(void* row, uint32 rol_num)
{		 	 	 	  
	return cc_mysql_get_double(row, rol_num);
}


// ȡ�����һ����insert��update���ΪAUTO_INCREMENT�����ɵ�����ֵ
// ��ʱû���ṩORACLE�ù��ܣ�ORACLE MODE�¾�����-1
int32 get_last_insert_id(db_conn_t* db)
{
	return cc_mysql_insert_id(db);
}

// �����������ݿ⺯��������ʧ�ܷ���ERR
int32 db_reconnect(db_conn_t* db)
{
	return cc_mysql_reconnect(db);
}


// �ͷŽ������ ���������db_store_result����
// ���ڽ����ʹ����Ϻ�Ҫ���ñ������ͷŽ����
int32 db_free_res(db_result_t** db_result)
{
	return cc_mysql_free_res(db_result);
}

// �ر����ݿ�
int32 db_close(db_conn_t** db)
{
	return cc_mysql_close(db);
}


static db_conn_t* cc_mysql_connect(char* db_ip, char* user_name, char* passwd, char* db_name,int16 port)
{
	db_conn_t* conn_tmp = (db_conn_t*)malloc(sizeof(db_conn_t));
	memset(conn_tmp, 0, sizeof(db_conn_t));

	MYSQL *mysql = NULL;
	mysql = (MYSQL*)malloc(sizeof(MYSQL));
	if (mysql == NULL)
	{
		fprintf(stderr, "malloc mysql error!\n");
		return NULL;
	}

	mysql_library_init(0, NULL, NULL);
	mysql_init(mysql);
	mysql_options(mysql, MYSQL_READ_DEFAULT_GROUP, "mysql");
	mysql_options(mysql, MYSQL_SET_CHARSET_NAME, "utf8");

	if (!mysql_real_connect(mysql, db_ip, user_name, passwd, db_name, port, NULL, 0))
	{
		fprintf(stderr, "mysql connect: Failed to connect to DB: [ %s ]", mysql_error(mysql));
		db_close(&conn_tmp);
		return NULL;
	}
	
	conn_tmp->conn = (void*)mysql;
	conn_tmp->flag = 1;
	conn_tmp->db_port = port;
	conn_tmp->count = 0;

	strncpy(conn_tmp->db_ip, db_ip, sizeof(conn_tmp->db_ip));
	strncpy(conn_tmp->user_name, user_name, sizeof(conn_tmp->user_name));
	strncpy(conn_tmp->passwd, passwd, sizeof(conn_tmp->passwd));
	strncpy(conn_tmp->db_name, db_name, sizeof(conn_tmp->db_name));

	return conn_tmp;	
}

static int32  cc_mysql_query(db_conn_t* db, char* sql)
{
	MYSQL*	mysql = (MYSQL*)(db->conn);
	uint32 	err = 0;

	if (mysql_real_query(mysql, sql, strlen(sql)) != 0)
	{
		err = mysql_errno(mysql);
		fprintf(stderr, "db query fails(mysql). Errno: %d , Error : %s", err, mysql_error(mysql));	
		fprintf(stderr, "Error sql : %s", sql);	
		if (err == 2006 || err == 2003 || err == 2013)
		{
			while (db->count < 2)  
			{
				if (db_reconnect(db) == -1)
				{	
					db->count++;			
				}else
				{
					db->count = 0;
					break;
				}
			}
			
			if (db->count) return -1;

			mysql = (MYSQL*)(db->conn);
			if (mysql_real_query(mysql, sql, strlen(sql)) != 0)
			{
				err = mysql_errno(mysql);
				fprintf(stderr, "db query fails(mysql). Errno: %d , Error : %s", err, mysql_error(mysql));	
				if (err == 2006)  db->flag = 0;	
				return -1;
			}
		}else
		{
			return -1;
		}
	}
	return 0;
}


static db_result_t*	cc_mysql_store_result(db_conn_t* db)
{
	db_result_t* db_result = NULL;
	MYSQL_RES*	 res1 = NULL;
	MYSQL*			 mysql = (MYSQL*)(db->conn);
		
	res1 = mysql_store_result(mysql);
	if (res1 == NULL)
	{
		fprintf(stderr, "store result fails. Error : %s", mysql_error(mysql));
		return NULL;
	}
	
	db_result = (db_result_t*)malloc(sizeof(db_result_t));
	if (db_result == NULL)
	{
		fprintf(stderr, "malloc db_result error!\n");
		return NULL;
	}
	memset(db_result, 0, sizeof(db_result_t));
	db_result->res = (void*)res1;
	
	return db_result;
}


static uint32 cc_mysql_get_num_rows(db_result_t* db_result)
{
	uint32 n = 0;
	
	n = mysql_num_rows((MYSQL_RES*)db_result->res);
	
	return n;
}


static uint32 cc_mysql_get_num_rols(db_result_t* db_result)
{
	uint32 n = 0;
	
	n = mysql_num_fields((MYSQL_RES*)db_result->res);
	
	return n;
}

static int32 cc_mysql_insert_id(db_conn_t* db)
{
	MYSQL* mysql = (MYSQL*)(db->conn);
	
	int32 n = 0;
	
	n = mysql_insert_id(mysql);
	
	if ((my_ulonglong)n == (my_ulonglong)(-1))
	{
		fprintf(stderr, "get insert id fails(mysql). Error : %s", mysql_error(mysql));
		return -1;	
	}
	
	return n;	
}

static void* cc_mysql_fetch_next_row(db_result_t* db_result)
{
	MYSQL_ROW mysql_row;
	MYSQL_RES*	  mysql_res = (MYSQL_RES*)(db_result->res);

	mysql_row = mysql_fetch_row(mysql_res);

	if (mysql_row == NULL)
	{
		return NULL;
	}
	
	return (void*)mysql_row;
}

static int32 cc_mysql_get_int(void* row, uint32 rol_num)
{
	MYSQL_ROW	mysql_row = (MYSQL_ROW)row;
	
	if (mysql_row[rol_num -1] == NULL)
	{
		return 0;
	}

	return atoi(mysql_row[rol_num - 1]);	
}

static char* cc_mysql_get_string(void* row, uint32 rol_num)
{
	MYSQL_ROW	mysql_row = (MYSQL_ROW)row;
	
	if (mysql_row[rol_num -1] == NULL)
	{
		return NULL;
	}

	return mysql_row[rol_num - 1];
}

static double cc_mysql_get_double(void* row, uint32 rol_num)
{
	MYSQL_ROW	mysql_row = (MYSQL_ROW)row;
	
	if (mysql_row[rol_num -1] == NULL)
	{
		return 0;
	}

	return atof(mysql_row[rol_num - 1]);
}

static int32 cc_mysql_reconnect(db_conn_t* db)
{
	if (db == NULL) 
	{
		fprintf(stderr, "db is NULL! [cc_mysql_reconnect]");	
		return -1;
	}

	if (db->conn)
	{
		//mysql_close((MYSQL*)(db->conn));
		free(db->conn);
		db->conn = NULL;
	}
	
	MYSQL *mysql = NULL;
	mysql = (MYSQL*)malloc(sizeof(MYSQL));
	if (mysql == NULL)
	{
		fprintf(stderr, "malloc mysql error!\n");
		return -1;
	}

	mysql_library_init(0, NULL, NULL);
	mysql_init(mysql);
	mysql_options(mysql, MYSQL_READ_DEFAULT_GROUP, "mysql");
	mysql_options(mysql, MYSQL_SET_CHARSET_NAME, "utf8");

	if (!mysql_real_connect(mysql, db->db_ip, db->user_name, db->passwd, 
			db->db_name, db->db_port, NULL, 0))
	{
		fprintf(stderr, "mysql reconnect: Failed to connect to DB: [ %s ]", mysql_error(mysql));
		return -1;
	}
	
	db->conn = (void*)mysql;
	return 0;
}

static int32 cc_mysql_free_res(db_result_t** db_result)
{
	if (*db_result)
	{
		if ((*db_result)->res)
		{
			mysql_free_result((MYSQL_RES*)((*db_result)->res));
		}
		free(*db_result);
		*db_result = NULL;
	}
	return 0;
}

static int32 cc_mysql_close(db_conn_t** db)
{
	if (*db)
	{
		if ((*db)->conn)
		{
			mysql_close((MYSQL*)((*db)->conn));
			free((*db)->conn);
			(*db)->conn = NULL;
		}
		free(*db);
		(*db) = NULL;
	}
	return 0;
}

