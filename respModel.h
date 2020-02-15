#pragma once
#include "DBhandler.h"
#include <vector>

struct respData {
    int id;
    std::string respname;
};

class respModel :
    public DBhandler
{
    private:
        std::string tablename = "responsibility";
    public:
        respModel();
        bool insertresp(std::string&);
        std::vector<respData> getallresp();

        bool deleteresp(std::string&);
};



