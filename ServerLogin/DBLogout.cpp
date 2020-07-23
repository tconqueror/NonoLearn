#include "pch.h"
#include "DBLogout.h"
//#include "stdio.h"

DBLogout::DBLogout() : DBManager()
{
	strcpy_s(info->host, SIZ, "localhost");
	strcpy_s(info->user, SIZ, "root");
	strcpy_s(info->pass, SIZ, "admin");
	strcpy_s(info->db, SIZ, "cnpm");
	strcpy_s(info->tables[0], SIZ, "Account");
	if (setupConnection() == false)
	{
		MessageBox(NULL, L"Lỗi connect db", L"Lỗi", 0);
	}
}

DBLogout::~DBLogout()
{
	mysql_free_result(m_pResult);
	mysql_close(m_pConn);
	delete m_pResult;
	delete m_pConn;
	delete info;
}

void DBLogout::Logout(int session)
{
	char query[10000] = { 0 };
	sprintf_s(query, 10000, "update Account set session = NULL where session = %d", session);
	doQuery(query);
}

