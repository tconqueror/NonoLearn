#pragma once


// Room_SV dialog

class Room_SV : public CDialogEx
{
	DECLARE_DYNAMIC(Room_SV)

public:
	Room_SV(CWnd* pParent = nullptr);   // standard constructor
	virtual ~Room_SV();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ROOMSV };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
