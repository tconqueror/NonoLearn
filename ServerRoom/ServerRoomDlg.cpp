
// ServerRoomDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "ServerRoom.h"
#include "ServerRoomDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CServerRoomDlg dialog



CServerRoomDlg::CServerRoomDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SERVERROOM_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CServerRoomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, listClient);
	DDX_Control(pDX, IDC_LIST2, log);
}

BEGIN_MESSAGE_MAP(CServerRoomDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CServerRoomDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CServerRoomDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CServerRoomDlg message handlers

BOOL CServerRoomDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	listClient.InsertColumn(0, L"IP", LVCFMT_CENTER, 100);
	listClient.InsertColumn(1, L"Port", LVCFMT_CENTER, 50);
	listClient.SetExtendedStyle(listClient.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	log.InsertColumn(0, L"Thời gian", LVCFMT_CENTER, 100);
	log.InsertColumn(1, L"Thông tin", LVCFMT_LEFT, 330);
	log.SetExtendedStyle(listClient.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	CString cmd = GetCommandLine();
	int tokenPos = 0;
	CString strtoken = cmd.Tokenize(_T(" "), tokenPos);
	ip = cmd.Tokenize(_T(" "), tokenPos);
	port = cmd.Tokenize(_T(" "), tokenPos);
	SetWindowText(ip + L":" + port);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CServerRoomDlg::OnPaint()
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
HCURSOR CServerRoomDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CServerRoomDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
	if (status)
	{
		if (CServerRoomDlg::DlgStop())
		{
			GetDlgItem(IDOK)->SetWindowTextW(L"Bắt đầu");
			status = false;
		}
		return;
	}
	if (CServerRoomDlg::DlgStart() == 0)
	{
		GetDlgItem(IDOK)->SetWindowTextW(L"Tạm dừng");
		status = true;
	}
}


void CServerRoomDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}

void CServerRoomDlg::showListClientMsg(CString ip, CString port)
{
	int n = listClient.InsertItem(0, ip);
	listClient.SetItemText(n, 1, port);
}

void CServerRoomDlg::updateList(std::vector<psa>vs)
{
	listClient.DeleteAllItems();
	for (auto i : vs)
	{
		showListClientMsg(i.ip, i.port);
	}

}
std::string CServerRoomDlg::DayOfWeek(int code)
{
	switch (code)
	{
	case 0: return (std::string) "[SUNDAY]";
	case 1: return (std::string) "[MONDAY]";
	case 2: return (std::string) "[TUESDAY]";
	case 3: return (std::string) "[WEDNESDAY]";
	case 4: return (std::string) "[THURSDAY]";
	case 5: return (std::string) "[FRIDAY]";
	case 6: return (std::string) "[SATURDAY]";
	}
	return (std::string) "[UNK_DayOfWeek]";
}
void CServerRoomDlg::ShowMessage(CString inf)
{
	SYSTEMTIME t;
	GetLocalTime(&t);
	int day = t.wDay;
	int month = t.wMonth;
	int year = t.wYear;
	int hour = t.wHour;
	int min = t.wMinute;
	int sec = t.wSecond;
	int dayName = t.wDayOfWeek;
	std::stringstream ss;
	ss << DayOfWeek(dayName) + " ";
	ss << day;
	ss << "/";
	ss << month;
	ss << "/";
	ss << year;
	ss << " ";
	ss << hour;
	ss << ":";
	ss << min;
	ss << ":";
	ss << sec;
	ss << " ";
	std::string stemp = ss.str();
	CString temp(stemp.c_str());
	int n = CServerRoomDlg::log.InsertItem(logCount++, temp);
	log.SetItemText(n, 1, inf);
}


bool CServerRoomDlg::DlgStart()
{
	cTh = AfxBeginThread(StaticThreadFunction, this);
	LPDWORD exitcode = 0;
	GetExitCodeThread(cTh, exitcode);
	return exitcode;
}

bool CServerRoomDlg::DlgStop()
{
	delete(pManage);
	listClient.DeleteAllItems();
	ShowMessage(L"Server stopped");
	return true;
}

UINT __cdecl CServerRoomDlg::StaticThreadFunction(LPVOID pParam)
{
	CServerRoomDlg* p = reinterpret_cast<CServerRoomDlg*>(pParam);
	UINT retCode = p->ThreadFunc();
	return retCode;
}

UINT CServerRoomDlg::ThreadFunc()
{
	pManage = new Manage(this);
	return pManage->StartListen(ip, port);
}