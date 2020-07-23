
// NonolearnDlg.h : header file
//

#pragma once


// CNonolearnDlg dialog
class CNonolearnDlg : public CDialogEx
{
// Construction
public:
	CNonolearnDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NONOLEARN_DIALOG };
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
public:
	afx_msg void OnBnClickedOk();
private:
	CString ip;
	CString port;
	CEdit ip_control;
	CEdit password_control;
	CEdit port_control;
	CEdit id_control;
	pii data;
public:
	afx_msg void OnBnClickedButtonforgot();
	void show();
};
