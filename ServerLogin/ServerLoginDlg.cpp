
// ServerLoginDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "ServerLogin.h"
#include "ServerLoginDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CServerLoginDlg dialog



CServerLoginDlg::CServerLoginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SERVERLOGIN_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CServerLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS1, ip_bind);
	DDX_Control(pDX, IDC_EDIT1, port_bind);
}

BEGIN_MESSAGE_MAP(CServerLoginDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CServerLoginDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CServerLoginDlg message handlers

BOOL CServerLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CServerLoginDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CServerLoginDlg::OnPaint()
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
HCURSOR CServerLoginDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



UINT __cdecl CServerLoginDlg::StaticThreadFunction(LPVOID pParam)
{
	CServerLoginDlg* p = reinterpret_cast<CServerLoginDlg*> (pParam);
	UINT retcode = p->ThreadFunc();
	return retcode;
}

UINT CServerLoginDlg::ThreadFunc()
{
	DWORD ip;
	ip_bind.GetAddress(ip);
	CString c_port;
	port_bind.GetWindowTextW(c_port);
	int port = _ttoi(c_port);
	ServerConnect* pServerConnect = new ServerConnect(this);
	return pServerConnect->Start(ip, port);
}

bool CServerLoginDlg::DlgStart()
{
	cTh = AfxBeginThread(StaticThreadFunction, this);
	LPDWORD exitcode = 0;
	GetExitCodeThread(cTh, exitcode);
	return exitcode;
}

bool CServerLoginDlg::DlgStop()
{
	delete(pConnect);
	return true;
}

void CServerLoginDlg::OnBnClickedOk()
{
	if (status)
	{
		if (DlgStop())
		{
			GetDlgItem(IDOK)->SetWindowTextW(L"OK");
			status = false;
		}
		return;
	}
	if (DlgStart() == 0)
	{
		GetDlgItem(IDOK)->SetWindowTextW(L"Dừng");
		status = true;
	}
}
