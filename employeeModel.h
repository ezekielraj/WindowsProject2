#pragma once
#include "DBhandler.h"
#include <vector>

struct empobjects
{
    int id;
    std::string empnum;
    std::string empname;
    std::string password;
};

class employeeModel :
    public DBhandler
{

    private:
        std::string tablename = "employee";
    public:
        employeeModel();
        bool insemployee(std::string&, std::string&, std::string&);
        std::vector<empobjects> getallemployees();
        empobjects getoneEmployee(std::string&);
        bool updateemployee(empobjects&);
        bool deleteemp(std::string&);
};

