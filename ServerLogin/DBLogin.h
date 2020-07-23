#pragma once
#include "DBManager.h"

class DBManager;
class DBLogin :
    public DBManager
{
public:
    DBLogin();
    ~DBLogin();
    pii Login(LPCSTR username, LPCSTR password);
};

