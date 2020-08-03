#pragma once
#include <WinSock2.h>
class Room_SV;
class Client_Room_Connect
{
public:
	Client_Room_Connect(Room_SV* t_p, int session, CString addr, CString port);
	~Client_Room_Connect();
	void SendData(CString msg);
	void Start();
private:
	WSADATA wsa;
	SOCKET s;
	Room_SV* clientroom;
	struct sockaddr_in server;
};

