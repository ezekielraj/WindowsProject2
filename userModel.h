#pragma once
#include "DBhandler.h"

class userModel :
    public DBhandler
{
    private:
        std::string tablename = "user";
    public:
        userModel();
        std::string getPassword(std::string);
 
};

