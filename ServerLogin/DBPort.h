#pragma once
#include "DBManager.h"
class DBPort :
    public DBManager
{
public:
    DBPort();
    ~DBPort();
public:
    int GetPort(int session, int id);
};

