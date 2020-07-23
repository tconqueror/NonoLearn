#pragma once

#include "ClientConnect.h"
// MenuGV dialog

class MenuGV : public CDialogEx
{
	DECLARE_DYNAMIC(MenuGV)

public:
	MenuGV(CWnd* pParent = nullptr);   // standard constructor
	MenuGV(CNonolearnDlg* p, int t_session, CString t_ip, CString t_port);
	virtual ~MenuGV();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_GV };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	int session;
	CString ip;
	CString port;
	CNonolearnDlg* pNonoLogin;
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	void show();
};
