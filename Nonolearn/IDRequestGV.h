#pragma once


// IDRequestGV dialog
class MenuGV;
class IDRequestGV : public CDialogEx
{
	DECLARE_DYNAMIC(IDRequestGV)

public:
	IDRequestGV(CWnd* pParent = nullptr);   // standard constructor
	IDRequestGV(int t_session, CString t_ip, CString t_port, MenuGV* t_p);
	virtual ~IDRequestGV();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_IDREQUEST_GV };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
private:
	CEdit ID_control;
	MenuGV* p = NULL;
	CString ip, port;
	int session = 0;
};
