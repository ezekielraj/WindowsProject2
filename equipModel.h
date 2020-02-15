#pragma once
#include "DBhandler.h"
#include <vector>

struct equipData
{
    int id;
    std::string equipnt;
    std::string description;
};

class equipModel :
    public DBhandler
{
    private:
        std::string tablename = "equipment";
    public:
        equipModel();
        bool insertequipnt(std::string&, std::string&);
        std::vector<std::string> getallequipnt();

        equipData getoneequip(std::string&);

        std::vector<equipData> getallequipnts();

        bool deleteequipnt(std::string&);
        std::string getDescription(std::string&);

        bool updateequip(equipData&);
};

