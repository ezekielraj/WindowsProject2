#pragma once
#include "DBhandler.h"
#include<vector>

struct faultobj
{
    int id;
    std::string faulttype;
};
class faultModel :
    public DBhandler
{
    private:
        std::string tablename = "faulttypes";
    public:
        faultModel();
        bool insertftype(std::string&);
        std::vector<faultobj> getallfaults();
        bool deletefault(std::string&);
};

