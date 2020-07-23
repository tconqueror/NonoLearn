#pragma once


// Room_GV dialog

class Room_GV : public CDialogEx
{
	DECLARE_DYNAMIC(Room_GV)

public:
	Room_GV(CWnd* pParent = nullptr);   // standard constructor
	virtual ~Room_GV();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ROOMGV };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
