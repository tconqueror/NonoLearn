#include "pch.h"
#include "DBLogin.h"
//#include "stdio.h"
#include <random>

DBLogin::DBLogin() : DBManager()
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

DBLogin::~DBLogin()
{
	mysql_free_result(m_pResult);
	mysql_close(m_pConn);
	delete m_pResult;
	delete m_pConn;
	delete info;
}

pii DBLogin::Login(LPCSTR username, LPCSTR password)
{
	char query[10000] = { 0 };
	sprintf_s(query, 10000, "select role from Account where (username = \"%s\" && password = \"%s\")", username, password);
	doQuery(query);
	if (m_pResult->row_count  != 1)
	{
		return pii(0,0);
	}
	int role = (int)(((*(char*)m_pResult->data->data->data[0])) - 48);
	ZeroMemory(query, 10000);
	std::random_device rd;
	std::mt19937 rng(rd());
	int session = rng() - MAXDWORD32;
	sprintf_s(query, 10000, "update Account set session = %d where username = \"%s\"", session, username);
	doQuery(query);
	ZeroMemory(query, 10000);
	//sprintf_s(query, 10000, sele)
	//int role = 2;
	return pii(session, role);
}
