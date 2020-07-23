#pragma once
#define SIZ 64
#include <mysql.h>

typedef struct MysqlConnectInfo {
	char host[SIZ];
	char user[SIZ];
	char pass[SIZ];
	char db[SIZ];
	char tables[3][SIZ]; //only one table so far
};
class DBManager
{
public:
	DBManager();
	DBManager(MysqlConnectInfo* pDBInfo);
	~DBManager();
	bool setupConnection();
	void setConnectionInfo(MysqlConnectInfo* pDBInfo);
	void doQuery(char* pQuery);
	char** getNextRow();
	MYSQL* getConnection();
	MYSQL_RES* getResult();
protected:
	MysqlConnectInfo* info;
	MYSQL* m_pConn;
	MYSQL_RES* m_pResult;
};

