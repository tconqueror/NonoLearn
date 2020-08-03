#pragma once
#include "Client_Room_Connect.h"

// Room_SV dialog

class Room_SV : public CDialogEx
{
	DECLARE_DYNAMIC(Room_SV)

public:
	Room_SV(CWnd* pParent = nullptr);   // standard constructor
	Room_SV(int t_session, CString t_ip, CString t_port);
	virtual ~Room_SV();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ROOMSV };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()
private:
	CEdit chat_control;
	CEdit msg_control;
	UINT ThreadFunc();
	static UINT __cdecl StaticThreadFunc(LPVOID pParam);
	void AppendText(CString msg);
	CWinThread* cTh;
	int session;
	CString ip, port;

public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	void ShowMessage(char* pos);
	void ShowMessage(CString cs);
	Client_Room_Connect* crc;
	
};
