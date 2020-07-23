#include "pch.h"
#include "ServerConnect.h"

ServerConnect::ServerConnect(CServerLoginDlg* p)
{
	this->pServerLoginDlg = p;

}

ServerConnect::~ServerConnect()
{
	closesocket(s);
	WSACleanup();
}

int ServerConnect::Start(DWORD ip, int port)
{
	if (WSAStartup(MAKEWORD(2, 2), &wsa))
	{
		showerror(L"WSAStartup");
		return 1;
	}
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		showerror(L"socket");
		WSACleanup();
		return 2;
	}
	server.sin_family = AF_INET;
	unsigned long r_ip = (ip >> 24) + (((ip >> 16) & 0xff) << 8) + (((ip >> 8) & 0xff) << 16) + ((ip & 0xff) << 24);
	server.sin_addr.s_addr = r_ip;
	server.sin_port = htons(port);
	if (bind(s, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
	{
		showerror(L"bind");
		closesocket(s);
		WSACleanup();
		return 3;
	}
	listen(s, 5);
	int c = sizeof(struct sockaddr_in);
	DBLogin* db = new DBLogin();
	DBLogout* dbl = new DBLogout();
	DBChangePw* dbc = new DBChangePw();
	DBPort* dbp = new DBPort();
	while ((news = accept(s, (struct sockaddr*)&client, &c)) != INVALID_SOCKET)
	{
		char buf[1000] = { 0 };
		sprintf_s(buf, 1000, "hello\0");
		if (send(news, buf, 6, 0) == 0)
		{
			closesocket(news);
			showerror(L"send");
			continue;
		}
		int recv_size;
		ZeroMemory(buf, 1000);
		if ((recv_size = recv(news, buf, 1000, 0))!= SOCKET_ERROR)
		{
			char* token = NULL;
			char* next_token = NULL;
			token = strtok_s(buf, "\x1", &next_token);
			//MessageBoxA(NULL, pch, pch, 1);
			if (!strcmp("Login", token))
			{
				token = strtok_s(NULL, "\x1", &next_token);
				char username[32] = { 0 };
				strcpy_s(username, 32, token);
				token = strtok_s(NULL, "\x1", &next_token);
				char password[32] = { 0 };
				strcpy_s(password, 32, token);
				//check
				
				pii val = db->Login(username, password);
				if (!val.first)
				{
					sprintf_s(buf, 1000, "Wrong");
					send(news, buf, 5, 0);
					closesocket(news);
					continue;
				}
				if (val.second == 1)
				{
					sprintf_s(buf, 1000, "GV\0");
				}
				else sprintf_s(buf, 1000, "SV\0");
				memcpy_s(buf + 3, 996, &(val.first), 4);
				send(news, buf, 7, 0);
				closesocket(news);
			}
			else
				if (!strcmp("Logout", token))
				{
					dbl->Logout(*(int*)(buf + 7));
					closesocket(news);
				}
				else 
					if (!strcmp("ChangePW", token))
					{
						token = strtok_s(buf + 13, "\x1", &next_token);
						char old[33] = { 0 };
						char newss[33] = { 0 };
						memcpy_s(old, 33, token, strlen(token));
						token = strtok_s(NULL, "\x1", &next_token);
						memcpy_s(newss, 33, token, strlen(token));
						int res = 0;
						if ((res = dbc->ChangePassword(*(int*)(buf + 9), old, newss)) == 1)
						{
							ZeroMemory(buf, 1000);
							sprintf_s(buf, 1000, "ChangeFail");
							send(news, buf, 11, 0);
							closesocket(news);
						}
						if (res == 0)
						{
							ZeroMemory(buf, 1000);
							sprintf_s(buf, 1000, "ChangeOK");
							send(news, buf, 9, 0);
							closesocket(news);
						}
					}
					else 
						if (!strcmp("Port", token))
						{
							int session, id;
							memcpy_s(&session, 4, buf + 5, 4);
							memcpy_s(&id, 4, buf + 9, 4);
							int res = 0;
							if ((res = dbp->GetPort(session, id)) == -1)
							{
								ZeroMemory(buf, 1000);
								sprintf_s(buf, 1000, "NULL");
								send(news, buf, 5, 0);
								closesocket(news);
							}
							if (res == -2)
							{
								ZeroMemory(buf, 1000);
								sprintf_s(buf, 1000, "Privilege");
								send(news, buf, 10, 0);
								closesocket(news);
							}
							ZeroMemory(buf, 1000);
							sprintf_s(buf, 1000, "repPort\0");
							memcpy_s(buf + 8, 992, &res, 4);
							send(news, buf, 12, 0);
							closesocket(news);
						}
		}
	}
	delete db;
	delete dbl;
	delete dbc;
	return 0;
}

void ServerConnect::showerror(CString sthing)
{
	CString errcode;
	errcode.Format(_T("%d"), WSAGetLastError());
	AfxMessageBox(sthing + L" " + errcode);
}

