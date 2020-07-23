#pragma once


// IDrequestSV dialog
class MenuSV;
class IDrequestSV : public CDialogEx
{
	DECLARE_DYNAMIC(IDrequestSV)

public:
	IDrequestSV(CWnd* pParent = nullptr);   // standard constructor
	IDrequestSV(int t_session, CString t_ip, CString t_port, MenuSV* t_p);
	virtual ~IDrequestSV();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_IDREQUEST_SV };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	CEdit ID_control;
	MenuSV* p = NULL;
	CString ip, port;
	int session= 0 ;
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
