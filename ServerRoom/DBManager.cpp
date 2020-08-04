#include "pch.h"
#include "DBManager.h"

DBManager::DBManager()
{
	info = new MysqlConnectInfo();
	m_pConn = mysql_init(NULL);
	m_pResult = NULL;
	strcpy_s(info->host, SIZ, "localhost");
	strcpy_s(info->user, SIZ, "root");
	strcpy_s(info->pass, SIZ, "admin");
	strcpy_s(info->db, SIZ, "cnpm");
	strcpy_s(info->tables[0], SIZ, "Account");
	strcpy_s(info->tables[1], SIZ, "Class");
	strcpy_s(info->tables[2], SIZ, "Study");
	if (setupConnection() == false)
	{
		MessageBox(NULL, CString(L"Lỗi connect db"), CString(L"Lỗi"), 0);
	}
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

CString DBManager::GetAccess(int session, CString r_port)
{
	char query[10000] = { 0 };
	char port[10] = { 0 };
	USES_CONVERSION;
	strcpy_s(port, 9, T2CA(r_port));
	sprintf_s(query, "select port from class where (port = %s && idclass = (select idclass from study where (idaccount = (select idaccount from account where session = %d))))", port, session);
	doQuery(query);
	if (m_pResult->row_count != 1)
		return CString(L"");
	ZeroMemory(query, 10000);
	sprintf_s(query, "select name from account where session = %d", session);
	doQuery(query);
	if (m_pResult->row_count != 1)
		return CString(L"");
	return CString(m_pResult->data->data->data[0]);
}
