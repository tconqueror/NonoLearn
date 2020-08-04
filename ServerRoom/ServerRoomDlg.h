
// ServerRoomDlg.h : header file
//

#pragma once
#include "Manage.h"

// CServerRoomDlg dialog
class CServerRoomDlg : public CDialogEx
{
// Construction
public:
	CServerRoomDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SERVERROOM_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	CListCtrl listClient;
	CListCtrl log;
	CString ip, port;
	bool status = false;
	bool DlgStart();
	bool DlgStop();
	static UINT __cdecl StaticThreadFunction(LPVOID);
	CWinThread* cTh;
	Manage* pManage;
	UINT ThreadFunc();
	std::string DayOfWeek(int);
	int logCount = 0;
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	void showListClientMsg(CString ip, CString port);
	void updateList(std::vector<psa> vs);
	void ShowMessage(CString inf);
};
