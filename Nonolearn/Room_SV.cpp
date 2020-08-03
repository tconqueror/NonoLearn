// Room_SV.cpp : implementation file
//

#include "pch.h"
#include "Room_SV.h"
#include "afxdialogex.h"
#include "resource.h"

// Room_SV dialog

IMPLEMENT_DYNAMIC(Room_SV, CDialogEx)

Room_SV::Room_SV(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ROOMSV, pParent)
{

}

Room_SV::Room_SV(int t_session, CString t_ip, CString t_port) : CDialogEx(IDD_DIALOG_ROOMSV, nullptr)
{
	//crc = new Client_Room_Connect(this, t_session, t_ip, t_port);
	session = t_session;
	ip = t_ip;
	port = t_port;
	cTh = AfxBeginThread(StaticThreadFunc, this);
}

Room_SV::~Room_SV()
{
	//delete crc;
}

void Room_SV::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_CHAT, chat_control);
	DDX_Control(pDX, IDC_EDIT_MSG, msg_control);
}



BEGIN_MESSAGE_MAP(Room_SV, CDialogEx)
	ON_BN_CLICKED(ID_SEND, &Room_SV::OnBnClickedOk)
	ON_BN_CLICKED(ID_QUIT, &Room_SV::OnBnClickedCancel)
END_MESSAGE_MAP()


// Room_SV message handlers


UINT Room_SV::ThreadFunc()
{
	crc = new Client_Room_Connect(this, session, ip, port);
	crc->Start();
	return 0;
}

UINT __cdecl Room_SV::StaticThreadFunc(LPVOID pParam)
{
	Room_SV* pYourClass = reinterpret_cast <Room_SV*> (pParam);
	UINT retCode = pYourClass->ThreadFunc();
	return retCode;
}

void Room_SV::AppendText(CString msg)
{
	int len = msg_control.GetWindowTextLengthW(); 
	msg_control.SetSel(len, len);
	msg_control.ReplaceSel(msg);
}

void Room_SV::OnBnClickedOk() // sendmsg
{
	CString s_msg;
	if (chat_control.GetWindowTextLengthW() == 0)
		return;
	chat_control.GetWindowTextW(s_msg);
	crc->SendData(s_msg);
}


void Room_SV::OnBnClickedCancel() // quit
{
	delete crc;
	TerminateThread(cTh->m_hThread, 0);
	CDialogEx::OnCancel();
}

void Room_SV::ShowMessage(char* pos)
{
	CString* msg = reinterpret_cast<CString*> (pos);
	CString strline;
	strline.Format(_T("%s\r\n"), *msg);
	AppendText(strline);
}

void Room_SV::ShowMessage(CString cs)
{
	CString strline;
	strline.Format(_T("%s\r\n"), cs);
	AppendText(strline);
}
