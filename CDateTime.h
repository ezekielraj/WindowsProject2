#pragma once
#include<iostream>
#include<string>

const int monthDays[12] = { 31, 28, 31, 30, 31, 30,
                       31, 31, 30, 31, 30, 31 };

class CDateTime
{
public:
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
    std::string getMysqlString();
    friend std::string getSubHours(CDateTime&, CDateTime&);
    friend int countLeapYears(CDateTime&);
    friend int getDifference(CDateTime&, CDateTime&);
    CDateTime getcdatetime(std::string&);
    std::string getinpformat();
//    CDateTime operator=(const CDateTime&);
};

