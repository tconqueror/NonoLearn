// ChangePassword.cpp : implementation file
//

#include "pch.h"
#include "ChangePassword.h"
#include "afxdialogex.h"
#include "resource.h"
#include "ClientConnect.h"

// ChangePassword dialog

IMPLEMENT_DYNAMIC(ChangePassword, CDialogEx)

ChangePassword::ChangePassword(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CHANGEPW, pParent)
{

}

ChangePassword::ChangePassword(int t_session, CString t_ip, CString t_port) : CDialogEx(IDD_DIALOG_CHANGEPW, nullptr)
{
	session = t_session;
	ip = t_ip;
	port = t_port;
}

ChangePassword::~ChangePassword()
{
}

void ChangePassword::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, old_password);
	DDX_Control(pDX, IDC_EDIT2, new_password_1);
	DDX_Control(pDX, IDC_EDIT3, new_password_2);
}


BEGIN_MESSAGE_MAP(ChangePassword, CDialogEx)
	ON_BN_CLICKED(IDOK, &ChangePassword::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &ChangePassword::OnBnClickedCancel)
END_MESSAGE_MAP()


// ChangePassword message handlers


void ChangePassword::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CString old, p1, p2;
	old_password.GetWindowTextW(old);
	new_password_1.GetWindowTextW(p1);
	new_password_2.GetWindowTextW(p2);
	ClientConnect* cc = new ClientConnect();
	if (p1.Compare(p2))
	{
		MessageBox(L"Mật khẩu mới không khớp hoặc không hợp lệ", L"Đổi mật khẩu", 0);
		return ;
	}
	cc->Start(ip, port);
	int res = 0;
	if ((res = cc->ChangePassword(session, old, p1)) == 0)
	{
		MessageBox(L"Đổi mật khẩu thành công", L"Đổi mật khẩu", 0);
		CDialogEx::OnOK();
	}
	if (res == 2)
	{
		MessageBox(L"Sai mật khẩu hiện tại", L"Đổi mật khẩu", 0);
	}
}


void ChangePassword::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}
