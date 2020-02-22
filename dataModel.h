#pragma once
#include "DBhandler.h"
#include "CDateTime.h"
#include<vector>
/*  1.	Date(calendar selection type.)
      2.	Equipment name / tag(to be selected from drop down menu)
      3.	NO run reason(fault / maintenance / Greasing / main equip run)
      4.	Time description select(delay / downtime) (time format HH : MM: SS)
      5.	If Fault then Type of fault(breakdown, tripping) (TRIP TYPE CLIENT SCOPE)
      6.	Description of(fault / maintenance)
      7.	Process(Process  CLIENT SCOPE)
      8.	Effect on process. (Individual process stop / Wind volume reduction / NA)
      9.	Attended by Name Unique ID number.
      10.	Remarks
      11.   Responsibility
*/

struct dataobject {
    int id;
    std::string date;
    std::string equipnt;
    std::string equipdes;
    std::string norunreason;
    std::string timedesc;
    CDateTime starttime;
    CDateTime stoptime;
    std::string timedeschh;
    std::string timedescmm;
    std::string timedescss;
    std::string faulttype;
    std::string faultdesc;
    std::string processname;
    std::string processeffect;
    std::string attendeename;
    std::string responsibility;
    std::string remarks;
    std::string created_by;
    std::string updated_by;
};

class dataModel :
    public DBhandler
{
    private:
        std::string tablename = "maindata_new2";
    public:
        dataModel();
        bool insertdata(dataobject&);
        bool updatedata(dataobject&);
        std::vector<dataobject> getalldatas();

        std::vector<dataobject> getalldata();

        dataobject getOnedata(std::string&);

        std::vector<std::string> equipDelaytime(std::string&);
        std::vector<std::string> equipDowntime(std::string&);
        std::vector<dataobject> getspecificdata(std::string, std::string);
        std::vector<std::string> getUserDetails(std::string);

        bool deletedata(std::string&);
};

