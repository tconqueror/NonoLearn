#pragma once
#include "DBManager.h"
class DBChangePw :
    public DBManager
{
public:
    DBChangePw();
    ~DBChangePw();
    int ChangePassword(int session, char* old, char* news);
};

