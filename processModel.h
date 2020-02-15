#pragma once
#include "DBhandler.h"
#include<vector>

struct processobj
{
    int id;
    std::string processname;
};

class processModel :
    public DBhandler
{
    private:
        std::string tablename = "processes";
    public:
        processModel();
        bool insertpname(std::string&);
        std::vector<processobj> getallprocess();

        bool deleteprocess(std::string&);

};

