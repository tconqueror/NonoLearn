#pragma once
#include "DBLogin.h"
#include "DBLogout.h"
#include "DBChangePw.h"
#include "DBPort.h"

class CServerLoginDlg;
class ServerConnect
{
public:
	ServerConnect(CServerLoginDlg *p);
	~ServerConnect();
	int Start(DWORD ip, int port);
private:
	CServerLoginDlg* pServerLoginDlg = NULL;
	SOCKET s, news;
	WSADATA wsa;
	void showerror(CString mes);
	struct sockaddr_in server, client;
};

