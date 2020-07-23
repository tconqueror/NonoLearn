// IDrequestSV.cpp : implementation file
//

#include "pch.h"
#include "IDrequestSV.h"
#include "afxdialogex.h"
#include "resource.h"
#include "MenuSV.h"
#include "ClientConnect.h"
#include "Room_SV.h"

// IDrequestSV dialog

IMPLEMENT_DYNAMIC(IDrequestSV, CDialogEx)

IDrequestSV::IDrequestSV(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_IDREQUEST_SV, pParent)
{

}

IDrequestSV::IDrequestSV(int t_session, CString t_ip, CString t_port, MenuSV* t_p) : CDialogEx(IDD_DIALOG_IDREQUEST_SV, nullptr)
{
	session = t_session;
	ip = t_ip;
	port = t_port;
	p = t_p;
}

IDrequestSV::~IDrequestSV()
{
}

void IDrequestSV::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, ID_control);
}


BEGIN_MESSAGE_MAP(IDrequestSV, CDialogEx)
	ON_BN_CLICKED(IDOK, &IDrequestSV::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &IDrequestSV::OnBnClickedCancel)
END_MESSAGE_MAP()


// IDrequestSV message handlers


void IDrequestSV::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	ClientConnect* cc = new ClientConnect();
	cc->Start(ip,port);
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
	Room_SV rsv;
	rsv.DoModal();
	p->show();
	CDialogEx::OnOK();
}


void IDrequestSV::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}
