#pragma once
#include "ClientConnect.h"

// MenuSV dialog
class CNonolearnDlg;
class MenuSV : public CDialogEx
{
	DECLARE_DYNAMIC(MenuSV)

public:
	MenuSV(CWnd* pParent = nullptr);   // standard constructor
	MenuSV( CNonolearnDlg *p,int t_session, CString t_ip, CString t_port);
	virtual ~MenuSV();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SV };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton3();
private:
	int session;
	CString ip;
	CString port;
	CNonolearnDlg* pNonoLogin;
public:
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton1();
	void show();
};
