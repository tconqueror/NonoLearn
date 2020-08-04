#pragma once
class CServerRoomDlg;
class Manage
{
public:
	Manage(CServerRoomDlg* p);
	~Manage();
	UINT StartListen(CString s_ip, CString s_port);
private:
	CServerRoomDlg* dlg;
	SOCKET s, news;
	WSADATA wsa;
	void error(const WCHAR*);
	struct sockaddr_in server, client;
	static UINT __cdecl StaticDataFunc(LPVOID pParam);
	UINT DataFunction();
	std::vector<psa> vs;
	CString cc_ip, cc_port;
	std::vector<CWinThread*> vt;
};
