#pragma once
#include <WinSock2.h>
#include "pch.h"
#include "NonolearnDlg.h"
//#include <atlstr.h>
class ClientConnect
{
public:
	ClientConnect();
	~ClientConnect();
	int Start(CString addr, CString port);
	pii Login(CString userid, CString password);
	void Logout(int session);
	int ChangePassword(int session, CString old, CString news);
	int GetRoomPort(int session, CString id);
private:
	WSADATA wsa = { 0 };
	SOCKET s = NULL;
	//CNonolearnDlg* CNoNoDlg = NULL;
	struct sockaddr_in server = { 0 };
	void showerror(CString sthing);
};

