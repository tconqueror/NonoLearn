
// NonolearnDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Nonolearn.h"
#include "NonolearnDlg.h"
#include "afxdialogex.h"
#include "ClientConnect.h"
#include "MenuSV.h"
#include "MenuGV.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNonolearnDlg dialog



CNonolearnDlg::CNonolearnDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NONOLEARN_DIALOG, pParent)
	, ip(_T("192.168.197.1"))
	, port(_T("12345"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNonolearnDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ip, ip);
	DDX_Text(pDX, IDC_EDIT_port, port);
	DDX_Control(pDX, IDC_EDIT_ip, ip_control);
	DDX_Control(pDX, IDC_EDIT_password, password_control);
	DDX_Control(pDX, IDC_EDIT_port, port_control);
	DDX_Control(pDX, IDC_EDIT_userid, id_control);
}

BEGIN_MESSAGE_MAP(CNonolearnDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CNonolearnDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_forgot, &CNonolearnDlg::OnBnClickedButtonforgot)
END_MESSAGE_MAP()


// CNonolearnDlg message handlers

BOOL CNonolearnDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CNonolearnDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CNonolearnDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CNonolearnDlg::OnBnClickedOk()
{
	ClientConnect *cc = new ClientConnect();
	CString temp_ip, temp_port;
	ip_control.GetWindowTextW(temp_ip);
	port_control.GetWindowTextW(temp_port);
	if (cc->Start(temp_ip, temp_port))
		return;

	CString temp_id, temp_pw;
	id_control.GetWindowTextW(temp_id);
	password_control.GetWindowTextW(temp_pw);
	if ((data = cc->Login(temp_id, temp_pw)).first)
	{
		delete cc;
		if (data.second == 2)
		{
			this->ShowWindow(SW_HIDE);
			MenuSV sv(this, data.first, temp_ip, temp_port);
			INT_PTR response = sv.DoModal();
		}
		else
			if (data.second == 1)
			{
				this->ShowWindow(SW_HIDE);
				MenuGV gv(this, data.first, temp_ip, temp_port);
				INT_PTR response = gv.DoModal();
			}
	}
	else delete cc;
}


void CNonolearnDlg::OnBnClickedButtonforgot()
{
	MessageBox(L"Chức năng này đang phát triển", L"Thông báo", 0);
}

void CNonolearnDlg::show()
{
	this->ShowWindow(SW_SHOW);
}
