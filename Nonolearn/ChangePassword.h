#pragma once


// ChangePassword dialog

class ChangePassword : public CDialogEx
{
	DECLARE_DYNAMIC(ChangePassword)

public:
	ChangePassword(CWnd* pParent = nullptr);   // standard constructor
	ChangePassword(int t_session, CString t_ip, CString t_port);
	virtual ~ChangePassword();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CHANGEPW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	int session = 0;
	CEdit old_password;
	CEdit new_password_1;
	CEdit new_password_2;
	CString ip, port;
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
