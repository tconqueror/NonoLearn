#include "pch.h"
#include "DBChangePw.h"
//#include "stdio.h"

DBChangePw::DBChangePw() : DBManager()
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

DBChangePw::~DBChangePw()
{
	mysql_free_result(m_pResult);
	mysql_close(m_pConn);
	delete m_pResult;
	delete m_pConn;
	delete info;
}

int DBChangePw::ChangePassword(int session, char* old, char* news)
{
	char query[10000] = { 0 };
	sprintf_s(query, 10000, "select * from Account where (session = %d && password = \"%s\")", session, old);
	doQuery(query);
	if (m_pResult->row_count != 1)
	{
		return 1;
	}
	ZeroMemory(query, 10000);
	sprintf_s(query, 10000, "update account set password = \"%s\" where(session = %d && password = \"%s\")", news, session, old);
	doQuery(query);
	return 0;
}

