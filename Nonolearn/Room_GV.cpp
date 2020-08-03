// Room_GV.cpp : implementation file
//

#include "pch.h"
#include "Room_GV.h"
#include "afxdialogex.h"
#include "resource.h"

// Room_GV dialog

IMPLEMENT_DYNAMIC(Room_GV, CDialogEx)

Room_GV::Room_GV(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ROOMGV, pParent)
{

}

Room_GV::Room_GV(int t_session, CString t_ip, CString t_port) : CDialogEx(IDD_DIALOG_ROOMGV, nullptr)
{
	session = t_session;
	ip = t_ip;
	port = t_port;
	cTh = AfxBeginThread(StaticThreadFunc, this);
}

Room_GV::~Room_GV()
{
}

void Room_GV::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_MSG, msg_control);
	DDX_Control(pDX, IDC_EDIT_CHAT, chat_control);
}


BEGIN_MESSAGE_MAP(Room_GV, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON3, &Room_GV::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON1, &Room_GV::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Room_GV::OnBnClickedButton2)
	ON_BN_CLICKED(ID_SEND, &Room_GV::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &Room_GV::OnBnClickedCancel)
END_MESSAGE_MAP()


// Room_GV message handlers

UINT Room_GV::ThreadFunc()
{
	crc = new Client_GV_Room_Connect(this, session, ip, port);
	crc->Start();
	return 0;
}
UINT __cdecl Room_GV::StaticThreadFunc(LPVOID pParam)
{
	Room_GV* pYourClass = reinterpret_cast <Room_GV*> (pParam);
	UINT retCode = pYourClass->ThreadFunc();
	return retCode;
}
void Room_GV::AppendText(CString msg)
{
	int len = msg_control.GetWindowTextLengthW();
	msg_control.SetSel(len, len);
	msg_control.ReplaceSel(msg);
}
void Room_GV::OnBnClickedButton3()
{
	MessageBox(L"Chức năng này đang phát triển", L"Thông báo", 0);
}


void Room_GV::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
}


void Room_GV::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
}

void Room_GV::ShowMessage(char* pos)
{
	CString* msg = reinterpret_cast<CString*> (pos);
	CString strline;
	strline.Format(_T("%s\r\n"), *msg);
	AppendText(strline);
}

void Room_GV::ShowMessage(CString cs)
{
	CString strline;
	strline.Format(_T("%s\r\n"), cs);
	AppendText(strline);
}


void Room_GV::OnBnClickedOk()
{
	CString s_msg;
	if (chat_control.GetWindowTextLengthW() == 0)
		return;
	chat_control.GetWindowTextW(s_msg);
	crc->SendData(s_msg);
}


void Room_GV::OnBnClickedCancel()
{
	delete crc;
	TerminateThread(cTh->m_hThread, 0);
	CDialogEx::OnCancel();
}

void Room_GV::active(bool val)
{
	//GetDlgItem(ID_)
}

void Room_GV::ban(bool val)
{
	if (val)
		return SetDlgItemText(IDC_BUTTON3, L"Bỏ cấm sinh viên chat"), (void)0;
	SetDlgItemText(IDC_BUTTON3, L"Cấm sinh viên chat");
}


