#pragma once
#include "Client_GV_Room_Connect.h"

// Room_GV dialog

class Room_GV : public CDialogEx
{
	DECLARE_DYNAMIC(Room_GV)

public:
	Room_GV(CWnd* pParent = nullptr);   // standard constructor
	Room_GV(int t_session, CString t_ip, CString t_port);
	virtual ~Room_GV();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ROOMGV };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton3();
private:
	CEdit msg_control;
	CEdit chat_control;
	UINT ThreadFunc();
	static UINT __cdecl StaticThreadFunc(LPVOID pParam);
	void AppendText(CString msg);
	CWinThread* cTh;
	int session;
	CString ip, port;
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	void ShowMessage(char* pos);
	void ShowMessage(CString cs);
	Client_GV_Room_Connect* crc;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	void active(bool val);
	void ban(bool val);		
};
