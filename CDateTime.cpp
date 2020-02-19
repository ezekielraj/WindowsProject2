#include "CDateTime.h"
#include<windows.h>
#include<iostream>
#include<string>
std::string CDateTime::getMysqlString() {
    return std::to_string(year) + "-" + std::to_string(month) + "-" + std::to_string(day) \
        + " " + std::to_string(hour) + ":" + std::to_string(minute) + ":" + std::to_string(second);
}

std::string getSubHours(CDateTime &dt1,  CDateTime &dt2) {
    

    int totaldays = getDifference(dt1, dt2);
   std::string td = std::to_string(totaldays);
    OutputDebugString(std::wstring(td.begin(), td.end()).c_str());
    long int totalhours = totaldays * 24 + dt2.hour;
    long int totalminutes = dt2.minute;
    long int totalseconds = dt2.second;
    td = std::to_string(totalhours);
    OutputDebugString(std::wstring(td.begin(), td.end()).c_str());
    totalhours = totalhours - (dt1.hour);
    totalminutes = totalminutes + (60 - dt1.minute);
    totalseconds = totalseconds + (60 - dt1.second);
    td = std::to_string(totalhours);
    OutputDebugString(std::wstring(td.begin(), td.end()).c_str());
    if (totalseconds >= 60) {
        totalseconds = totalseconds - 60;
        totalminutes = totalminutes + 1;
    }
    if (totalseconds < 60) {
        totalminutes = totalminutes - 1;
        //totalseconds = 60 - totalseconds;
    }

    if (totalminutes >= 60) {
        totalminutes = totalminutes - 60;
        totalhours = totalhours + 1;
    }
    if (totalminutes < 60) {
        totalhours = totalhours - 1;
       // totalminutes = 60 - totalminutes;
    }

    return std::to_string(totalhours) + ":" + std::to_string(totalminutes) + ":" + std::to_string(totalseconds);
}

int countLeapYears(CDateTime &d)
{
    int years = d.year;
    if (d.month <= 2)
        years--;
    return years / 4 - years / 100 + years / 400;
}

int getDifference(CDateTime &dt1, CDateTime &dt2)
{
    long int n1 = dt1.year * 365 + dt1.day;
    for (int i = 0; i < dt1.month - 1; i++)
        n1 += monthDays[i];
    n1 += countLeapYears(dt1);
    long int n2 = dt2.year * 365 + dt2.day;
    for (int i = 0; i < dt2.month - 1; i++)
        n2 += monthDays[i];
    n2 += countLeapYears(dt2);
    return (n2 - n1);
}

CDateTime CDateTime::getcdatetime(std::string &dt) {
    CDateTime cdt;
    std::string delim = " ";
    std::string timedelim = ":";
    std::string datedelim = "-";
    
    size_t pos = 0;
    std::string cdate;
    pos = dt.find(delim);
    cdate = dt.substr(0, pos);

    dt.erase(0, pos + delim.length());

    std::string ctime = dt;

    ///getting time
    pos = 0;
    std::string token;
    pos = ctime.find(timedelim);
    token = ctime.substr(0, pos);
    //            std::cout << token << std::endl;
    cdt.hour = stoi(token);
    ctime.erase(0, pos + timedelim.length());

    pos = ctime.find(timedelim);
    token = ctime.substr(0, pos);
    cdt.minute = stoi(token);
    ctime.erase(0, pos + timedelim.length());

    cdt.second = stoi(ctime);

    //getting date
    pos = 0;
    std::string token1;
    pos = cdate.find(datedelim);
    token1 = cdate.substr(0, pos);
    //            std::cout << token << std::endl;
    cdt.year = stoi(token1);
    cdate.erase(0, pos + datedelim.length());

    pos = cdate.find(datedelim);
    token1 = cdate.substr(0, pos);
    cdt.month = stoi(token1);
    cdate.erase(0, pos + datedelim.length());

    cdt.day = stoi(cdate);

    return cdt;

}