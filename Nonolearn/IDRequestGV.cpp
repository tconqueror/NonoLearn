// IDRequestGV.cpp : implementation file
//

#include "pch.h"
#include "IDRequestGV.h"
#include "afxdialogex.h"
#include "resource.h"
#include "ClientConnect.h"
#include "MenuGV.h"
#include "Room_GV.h"

// IDRequestGV dialog

IMPLEMENT_DYNAMIC(IDRequestGV, CDialogEx)

IDRequestGV::IDRequestGV(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_IDREQUEST_GV, pParent)
{

}

IDRequestGV::IDRequestGV(int t_session, CString t_ip, CString t_port, MenuGV* t_p) : CDialogEx(IDD_DIALOG_IDREQUEST_GV, nullptr)
{
	session = t_session;
	ip = t_ip;
	port = t_port;
	p = t_p;
}

IDRequestGV::~IDRequestGV()
{
}

void IDRequestGV::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(IDRequestGV, CDialogEx)
	ON_BN_CLICKED(IDOK, &IDRequestGV::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &IDRequestGV::OnBnClickedCancel)
END_MESSAGE_MAP()


// IDRequestGV message handlers


void IDRequestGV::OnBnClickedOk()
{
	ClientConnect* cc = new ClientConnect();
	cc->Start(ip, port);
	CString id;
	GetDlgItemText(IDC_EDIT1, id);
	int res = 0;
	if ((res = cc->GetRoomPort(session, id)) == -1)
	{
		MessageBox(L"Không có quyền vào phòng", L"Vào phòng", 1);
		return;
	}
	if (res == -2)
	{
		MessageBox(L"Phòng không tồn tại", L"Vào phòng", 1);
		return;
	}
	CString r_port;
	r_port.Format(L"%d", res);
	Room_GV rgv(session, ip, r_port);
	rgv.DoModal();
	p->show();
	CDialogEx::OnOK();
}


void IDRequestGV::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}
