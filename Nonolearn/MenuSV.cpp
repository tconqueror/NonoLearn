// MenuSV.cpp : implementation file
//

#include "pch.h"
#include "MenuSV.h"
#include "afxdialogex.h"
#include "resource.h"
#include "ChangePassword.h"
#include "IDrequestSV.h"

// MenuSV dialog

IMPLEMENT_DYNAMIC(MenuSV, CDialogEx)

MenuSV::MenuSV(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SV, pParent)
{

}

MenuSV::MenuSV(CNonolearnDlg* p, int t_session, CString t_ip, CString t_port) : CDialogEx(IDD_DIALOG_SV, nullptr)
{
	pNonoLogin = p;
	session = t_session;
	ip = t_ip;
	port = t_port;
}

MenuSV::~MenuSV()
{
}

void MenuSV::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MenuSV, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &MenuSV::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &MenuSV::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &MenuSV::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON5, &MenuSV::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON1, &MenuSV::OnBnClickedButton1)
END_MESSAGE_MAP()


// MenuSV message handlers


void MenuSV::OnBnClickedButton2()
{
	MessageBox(L"Chức năng này đang phát triển", L"Thông báo", 0);
}

void MenuSV::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here
	MessageBox(L"Chức năng này đang phát triển", L"Thông báo", 0);
}


void MenuSV::OnBnClickedButton3() //Change password
{
	// TODO: Add your control notification handler code here
	//MessageBox(L"Chức năng này đang phát triển", L"Thông báo", 0);
	ChangePassword cp(session,ip,port);
	cp.DoModal();
}


void MenuSV::OnBnClickedButton5()
{
	ClientConnect* cc = new ClientConnect();
	cc->Start(ip, port);
	cc->Logout(session);
	delete cc;
	pNonoLogin->show();
	CDialog::OnOK();
}


void MenuSV::OnBnClickedButton1() // vao phong
{
	this->ShowWindow(SW_HIDE);
	IDrequestSV idrsv(session, ip, port, this);
	idrsv.DoModal();
	this->ShowWindow(SW_SHOW);
}

void MenuSV::show()
{
	this->ShowWindow(SW_SHOW);
}
