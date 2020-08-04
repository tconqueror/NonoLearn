#include "pch.h"
#include "Client_Room_Connect.h"
#include "resource.h"
#include "Room_SV.h"
Client_Room_Connect::Client_Room_Connect(Room_SV* t_p, int session, CString addr, CString port)
{
	//clientroom->GetDlgItem(ID_SEND)->EnableWindow(0);
	Sleep(1000);
	char bufname[10000] = { 0 };
	swprintf_s((wchar_t*)bufname, 5000, L"IP: %s Port: %s", addr, port);
	t_p->SetWindowTextW((wchar_t*)bufname);
	clientroom = t_p;
	clientroom->GetDlgItem(ID_SEND)->EnableWindow(false);
	int i_port = _ttoi(port);
	_bstr_t b(addr);
	char* c = b;
	//
	if (WSAStartup(MAKEWORD(2, 2), &wsa))
	{
		clientroom->GetDlgItem(ID_SEND)->EnableWindow(false);
		CString errcode;
		errcode.Format(_T("%d"), WSAGetLastError());
		AfxMessageBox(L"WSAStartup " + errcode);
		return;
	}
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		clientroom->GetDlgItem(ID_SEND)->EnableWindow(false);
		CString errcode;
		errcode.Format(_T("%d"), WSAGetLastError());
		AfxMessageBox(L"CreateSocket " + errcode);
		return;
	}

	inet_pton(AF_INET, c, &(server.sin_addr));
	server.sin_family = AF_INET;
	server.sin_port = htons(i_port);
	if (connect(s, (struct sockaddr*)&server, sizeof(server)))
	{
		clientroom->GetDlgItem(ID_SEND)->EnableWindow(false);
		CString errcode;
		errcode.Format(_T("%d"), WSAGetLastError());
		AfxMessageBox(L"Connect " + errcode);
		return;
	}
	if (send(s, (char *)&session, 4, 0) == SOCKET_ERROR)
	{
		clientroom->GetDlgItem(ID_SEND)->EnableWindow(false);
		CString errcode;
		errcode.Format(_T("%d"), WSAGetLastError());
		AfxMessageBox(L"Session " + errcode);
		return;
	}
	ZeroMemory(bufname, 10000);
	int recv_size = 0;
	if ((recv_size = recv(s, bufname, 10000, 0)) != SOCKET_ERROR)
	{
		bufname[recv_size] = '\0';
		if (memcmp(bufname, "OK", 2))
		{
			clientroom->GetDlgItem(ID_SEND)->EnableWindow(false);
			clientroom->ShowMessage(L"Wrong Session" + addr + L":" + port + L"\n");
			return;

		}
	}
	clientroom->GetDlgItem(ID_SEND)->EnableWindow(true);
	clientroom->ShowMessage(L"Connect successfully to " + addr + L":" + port + L"\n");
}

Client_Room_Connect::~Client_Room_Connect()
{
	closesocket(s);
	WSACleanup();
	clientroom->GetDlgItem(ID_SEND)->EnableWindow(false);
	clientroom->ShowMessage(L"Disconnected");
}

void Client_Room_Connect::SendData(CString msg)
{
	const char* buf = reinterpret_cast<const char*> (msg.GetBuffer());
	char x[10000] = { 0 };
	memcpy_s(x, 9998, buf, 9998);
	if ((send(s, x, lstrlenW((wchar_t*)x) * 2, 0)) == 0)
	{
		CString errcode;
		errcode.Format(_T("%d"), WSAGetLastError());
		AfxMessageBox(L"Send " + errcode);
		return;
	}
	msg.ReleaseBuffer();
	clientroom->GetDlgItem(IDC_EDIT_CHAT)->SetWindowTextW(L"");
	clientroom->GetDlgItem(IDC_EDIT_CHAT)->SetFocus();
}

void Client_Room_Connect::Start()
{
	int recv_size = 0;
	char buf[10000];
	while ((recv_size = recv(s, buf, 9998, 0)) != SOCKET_ERROR)
	{
		buf[recv_size] = '\0';
		buf[recv_size + 1] = '\0';
		WCHAR* pwchar = reinterpret_cast<WCHAR*>(buf);
		CString cstemp(pwchar);
		clientroom->ShowMessage(cstemp);
	}
	clientroom->ShowMessage(L"Server stopped");
	clientroom->GetDlgItem(ID_SEND)->EnableWindow(false);
}

