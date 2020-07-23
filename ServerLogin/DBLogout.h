#pragma once
#include "DBManager.h"

class DBManager;
class DBLogout :
    public DBManager
{
public:
    DBLogout();
    ~DBLogout();
    void Logout(int session);
};

