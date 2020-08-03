#pragma once
#include <WinSock2.h>
class Room_GV;
class Client_GV_Room_Connect
{
public:
	Client_GV_Room_Connect(Room_GV *t_p, int session, CString addr, CString port);
	~Client_GV_Room_Connect();
	void SendData(CString msg);
	void Start();
private:
	WSADATA wsa;
	SOCKET s;
	Room_GV* clientroom;
	struct sockaddr_in server;
};

