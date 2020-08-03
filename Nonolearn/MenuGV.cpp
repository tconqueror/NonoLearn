// MenuGV.cpp : implementation file
//

#include "pch.h"
#include "MenuGV.h"
#include "afxdialogex.h"
#include "resource.h"
#include "ChangePassword.h"
#include "IDRequestGV.h"
// MenuGV dialog

IMPLEMENT_DYNAMIC(MenuGV, CDialogEx)

MenuGV::MenuGV(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_GV, pParent)
{

}

MenuGV::MenuGV(CNonolearnDlg* p, int t_session, CString t_ip, CString t_port) : CDialogEx(IDD_DIALOG_GV, nullptr)
{
	pNonoLogin = p;
	session = t_session;
	ip = t_ip;
	port = t_port;
}
MenuGV::~MenuGV()
{
}

void MenuGV::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MenuGV, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &MenuGV::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &MenuGV::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &MenuGV::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &MenuGV::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &MenuGV::OnBnClickedButton5)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// MenuGV message handlers


void MenuGV::OnClose()
{
	OnBnClickedButton5();
}

void MenuGV::OnBnClickedButton1() //vao phong
{
	this->ShowWindow(SW_HIDE);
	IDRequestGV idrgv(session, ip, port, this);
	idrgv.DoModal();
	this->ShowWindow(SW_SHOW);
}


void MenuGV::OnBnClickedButton2() //lien he
{
	MessageBox(L"Chức năng này đang phát triển", L"Thông báo", 0);
}


void MenuGV::OnBnClickedButton3() // edit data
{
	MessageBox(L"Chức năng này đang phát triển", L"Thông báo", 0);
}


void MenuGV::OnBnClickedButton4() //doi mk
{
	// TODO: Add your control notification handler code here
	ChangePassword cp(session, ip, port);
	cp.DoModal();
}


void MenuGV::OnBnClickedButton5() // dang xuat
{
	// TODO: Add your control notification handler code here
	ClientConnect* cc = new ClientConnect();
	cc->Start(ip, port);
	cc->Logout(session);
	delete cc;
	pNonoLogin->show();
	CDialog::OnOK();
}

void MenuGV::show()
{
	this->ShowWindow(SW_SHOW);
}
