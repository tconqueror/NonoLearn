
// ServerLoginDlg.h : header file
//
#include "pch.h"
#include "ServerConnect.h"

#pragma once


// CServerLoginDlg dialog
class CServerLoginDlg : public CDialogEx
{
// Construction
public:
	CServerLoginDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SERVERLOGIN_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	CIPAddressCtrl ip_bind;
	CEdit port_bind;
	static UINT __cdecl StaticThreadFunction(LPVOID pParam);
	CWinThread* cTh;
	UINT ThreadFunc();
	ServerConnect* pConnect;
	bool status = false;
	bool DlgStart();
	bool DlgStop();
public:
	afx_msg void OnBnClickedOk();
};
