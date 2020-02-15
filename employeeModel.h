#pragma once
#include "DBhandler.h"
#include <vector>

struct empobjects
{
    int id;
    std::string empnum;
    std::string empname;
};

class employeeModel :
    public DBhandler
{

    private:
        std::string tablename = "employee";
    public:
        employeeModel();
        bool insemployee(std::string&, std::string&);
        std::vector<empobjects> getallemployees();

        bool deleteemp(std::string&);
};

