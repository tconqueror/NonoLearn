#include "pch.h"
#include "ClientConnect.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
ClientConnect::ClientConnect()
{

}

ClientConnect::~ClientConnect()
{
	closesocket(s);
	WSACleanup();
}

int ClientConnect::Start(CString addr, CString port)
{
	int i_port = _ttoi(port);
	_bstr_t add(addr);
	char* c = add;
	if (WSAStartup(MAKEWORD(2, 2), &wsa))
	{
		showerror(L"Startup fail");
		WSACleanup();
		return 1;
	}
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		showerror(L"Socket fail");
		WSACleanup();
		return 1;
	}
	inet_pton(AF_INET, c, &(server.sin_addr));
	//server.sin_addr.s_addr = inet_addr(c);
	server.sin_family = AF_INET;
	server.sin_port = htons(i_port);
	if (connect(s, (struct sockaddr*)&server, sizeof(server)))
	{
		showerror(L"Connect fail");
		closesocket(s);
		WSACleanup();
		return 2;
	}
	int recv_size = 0;
	char buf[10000];
	if ((recv_size = recv(s, buf, 9999, 0)) != SOCKET_ERROR)
	{
		if (strcmp(buf, "hello"))
		{
			showerror(L"Wrong");
			closesocket(s);
			WSACleanup();
			return 3;
		}
	}
	return 0;
}

pii ClientConnect::Login(CString userid, CString password)
{
	_bstr_t uid(userid);
	_bstr_t pw(password);
	char* c_uid = uid;
	char* c_pw = pw;
	char loginForm[1000] = { 0 };
	sprintf_s(loginForm, "Login\x1%s\x1%s", c_uid, c_pw);
	if (send(s, loginForm, strlen(loginForm), 0) == 0)
	{
		showerror(L"Login");
		closesocket(s);
		WSACleanup();
		return pii(0,0);
	}
	int recv_size = 0;
	if ((recv_size = recv(s, loginForm, 1000, 0)) != SOCKET_ERROR)
	{
		loginForm[recv_size] = '\0';
		if (strcmp(loginForm, "Wrong") == 0)
		{
			MessageBox(NULL, L"Sai tài khoản hoặc mật khẩu", L"Đăng nhập", 1);
			closesocket(s);
			WSACleanup();
			return pii(0,0);
		}
		//int a = strcmp("OK",loginForm);
		if (strcmp("GV",loginForm) == 0)
		{
			closesocket(s);
			WSACleanup();
			int res;
			memcpy_s(&res, 4, loginForm + 3, 4);
			return pii(res, 1);
		}
		if (strcmp("SV", loginForm) == 0)
		{
			closesocket(s);
			WSACleanup();
			int res = 0;
			memcpy_s(&res, 4, loginForm + 3, 4);
			return pii(res,2);
		}
		MessageBox(NULL, L"Lỗi", L"Đăng nhập", 1);
		closesocket(s);
		WSACleanup();
	}
	return pii(0,0);
}

void ClientConnect::Logout(int session)
{
	char buf[1000] = { 0 };
	sprintf_s(buf, 1000, "Logout\0");
	memcpy_s(buf + 7, 992, &session, 4);
	if (send(s, buf, 11, 0) == 0)
	{
		showerror(L"Logout Failed");
		closesocket(s);
		WSACleanup();
		return;
	}
}
int ClientConnect::ChangePassword(int session, CString old, CString news)
{
	char buf[10000] = { 0 };
	USES_CONVERSION;
	char old_pw[33] = { 0 };
	char new_pw[33] = { 0 };
	strcpy_s(old_pw, 33, T2CA(old));
	strcpy_s(new_pw, 33, T2CA(news));
	sprintf_s(buf, 10000, "ChangePW\x1\x1\x1\x1\x1%s\x1%s", old_pw, new_pw);
	memcpy_s(buf + 9, 9991, &session, 4);
	if (send(s, buf, 14 + old.GetLength() + news.GetLength(), 0) == 0)
	{
		showerror(L"Change password Failed");
		closesocket(s);
		WSACleanup();
		return 1;
	}
	ZeroMemory(buf, 10000);
	int recv_size = 0;
	if ((recv_size = recv(s, buf, 10000, 0)) != SOCKET_ERROR)
	{
		if (strcmp(buf, "ChangeOK") == 0)
		{
			return 0; // ok
		}
		return 2; // sai mat khau
	}
}
int ClientConnect::GetRoomPort(int session, CString id)
{
	char buf[10000] = { 0 };
	int i_id = _wtoi(id);
	sprintf_s(buf, 10000, "Port\x1\x1\x1\x1\x1\x1\x1\x1\x1");
	memcpy_s(buf + 5, 9995, &session, 4);
	memcpy_s(buf + 9, 9995, &i_id, 4);
	if (send(s, buf, 13, 0) == SOCKET_ERROR)
	{
		showerror(L"Get Room port failed");
		closesocket(s);
		WSACleanup();
		return 0;
	}
	ZeroMemory(buf, 10000);
	int recv_size = 0;
	if ((recv_size = recv(s, buf, 10000, 0)) != SOCKET_ERROR)
	{
		if (strcmp(buf, "repPort") == 0)
		{
			int res = 0;
			memcpy_s(&res, 4, buf + 8, 4);
			return res;
		}
		else
			if (strcmp(buf, "Privilege") == 0)
			{
				return -1; // khong co quyen
			}
		return -2; // phong khong ton tai
	}
}
void ClientConnect::showerror(CString sthing)
{
	CString errcode;
	errcode.Format(_T("%d"), WSAGetLastError());
	AfxMessageBox(sthing + L" " + errcode);
}