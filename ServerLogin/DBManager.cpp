#include "pch.h"
#include "DBManager.h"
DBManager::DBManager()
{
	info = new MysqlConnectInfo();
	m_pConn = mysql_init(NULL);
	m_pResult = NULL;
	strcpy_s(info->host, SIZ, "\0");
	strcpy_s(info->user, SIZ, "\0");
	strcpy_s(info->pass, SIZ, "\0");
	strcpy_s(info->db, SIZ, "\0");
	strcpy_s(info->tables[0], SIZ, "\0");
	strcpy_s(info->tables[1], SIZ, "\0");
	strcpy_s(info->tables[2], SIZ, "\0");
}

DBManager::DBManager(MysqlConnectInfo* pDBInfo)
{
	setConnectionInfo(pDBInfo);
	strcpy_s(info->db, SIZ, pDBInfo->db);
	strcpy_s(info->host, SIZ, pDBInfo->host);
	strcpy_s(info->pass, SIZ, pDBInfo->pass);
	strcpy_s(info->tables[1], SIZ, pDBInfo->tables[1]);
	strcpy_s(info->tables[0], SIZ, pDBInfo->tables[0]);
	strcpy_s(info->tables[2], SIZ, pDBInfo->tables[2]);
	strcpy_s(info->user, SIZ, pDBInfo->user);

	m_pConn = mysql_init(NULL);
	m_pResult = NULL;
}

DBManager::~DBManager()
{
	mysql_free_result(m_pResult);
	mysql_close(m_pConn);
	delete m_pResult;
	delete m_pConn;
	delete info;
}

bool DBManager::setupConnection()
{
	if (!mysql_real_connect(m_pConn, info->host, info->user, info->pass, info->db, 0, NULL, 0))
	{
		return false;
	}
	return true;
}

void DBManager::setConnectionInfo(MysqlConnectInfo* pDBInfo)
{
	info = pDBInfo;
}

void DBManager::doQuery(char* pQuery)
{
	mysql_free_result(m_pResult);
	if (mysql_query(m_pConn, pQuery))
	{
		m_pResult = NULL;
		exit(1);
	}
	else
	{
		m_pResult = mysql_store_result(m_pConn);
	}
}

char** DBManager::getNextRow()
{
	if (!(m_pResult == NULL))
		return mysql_fetch_row(m_pResult);
	else
		return NULL;
}

MYSQL* DBManager::getConnection()
{
	return m_pConn;
}

MYSQL_RES* DBManager::getResult()
{
	return m_pResult;
}
