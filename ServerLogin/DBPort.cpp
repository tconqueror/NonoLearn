#include "pch.h"
#include "DBPort.h"

DBPort::DBPort() : DBManager()
{
	strcpy_s(info->host, SIZ, "localhost");
	strcpy_s(info->user, SIZ, "root");
	strcpy_s(info->pass, SIZ, "admin");
	strcpy_s(info->db, SIZ, "cnpm");
	strcpy_s(info->tables[0], SIZ, "Account");
	strcpy_s(info->tables[1], SIZ, "Class");
	strcpy_s(info->tables[2], SIZ, "Study");
	if (setupConnection() == false)
	{
		MessageBox(NULL, L"Lỗi connect db", L"Lỗi", 0);
	}
}
DBPort::~DBPort()
{
	mysql_free_result(m_pResult);
	mysql_close(m_pConn);
	delete m_pResult;
	delete m_pConn;
	delete info;
}

int DBPort::GetPort(int session, int id)
{
	char query[10000] = { 0 };
	sprintf_s(query, 10000, "select * from class where idclass = %d", id);
	doQuery(query);
	if (m_pResult->row_count != 1)
		return -1; // khong ton tai phong
	ZeroMemory(query, 10000);
	sprintf_s(query, 10000, "select port from class where (idclass = (select idclass from study where (idclass=%d && idaccount = (select idaccount from account where session = %d))))", id, session);
	doQuery(query);
	if (m_pResult->row_count == 0)
	{
		return -2; //khong thuoc ve phong
	}
	return atoi(m_pResult->data->data->data[0]);
}
