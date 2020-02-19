#include "dataModel.h"
#include "base64.h"
#include<windows.h>
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
*/

dataModel::dataModel() {
    OpenConnection();
    try {
        stmt = con->createStatement();
        stmt->execute("CREATE TABLE IF NOT EXISTS `maindata_new2` ( \
            `id` int(100) unsigned NOT NULL AUTO_INCREMENT, \
            `date` varchar(256) NOT NULL, \
            `equipmenttag` varchar(512), \
            `equipmentdesc` varchar(1024), \
            `norunreason` varchar(512), \
            `timedetail` varchar(512), \
            `starttime` timestamp, \
            `stoptime` timestamp, \
            `timedesc` varchar(512), \
            `typeoffault` varchar(512), \
            `fmdesc` varchar(512), \
            `process` varchar(512), \
            `effectonprocess` varchar(512), \
            `attendeename` varchar(512), \
            `responsibility` varchar(512), \
            `remarks` varchar(1024), \
            `created_at` timestamp not null default now(), \
            `created_by` varchar(512), \
            `updated_at` timestamp not null default now() on update now(), \
            `updated_by` varchar(512), \
            PRIMARY KEY(`id`) \
            ) ENGINE = InnoDB");
        //delete stmt;
    }
    catch (sql::SQLException &e) {

    }
    closeConnection();
}

bool dataModel::insertdata(dataobject &dm) {
    try {


        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * from " + tablename + " where date = '" + dm.date + "' \
                                        AND equipmenttag = '"+dm.equipnt +"' \
                                        AND equipmentdesc = '"+dm.equipdes+"' \
                                        AND norunreason = '"+dm.norunreason +"' \
                                        AND timedetail = '"+dm.timedesc+"' \
                                        AND starttime = '"+dm.starttime.getMysqlString()+"' \
                                        AND stoptime = '"+dm.stoptime.getMysqlString()+"' \
                                        AND timedesc = '"+ getSubHours(dm.starttime, dm.stoptime) + "' \
                                        AND typeoffault = '"+dm.faulttype+"' \
                                        AND fmdesc = '"+ base64_encode(reinterpret_cast<const unsigned char*>(dm.faultdesc.c_str()), dm.faultdesc.length()) +"' \
                                        AND process = '"+dm.processname+"' \
                                        AND effectonprocess = '"+ base64_encode(reinterpret_cast<const unsigned char*>(dm.processeffect.c_str()), dm.processeffect.length()) +"' \
                                        AND attendeename = '"+dm.attendeename+"' \
                                        AND responsibility = '"+dm.responsibility+"' \
                                        AND remarks = '"+ base64_encode(reinterpret_cast<const unsigned char*>(dm.remarks.c_str()), dm.remarks.length()) +"'");

//        base64_encode(reinterpret_cast<const unsigned char*>(strpass.c_str()), strpass.length())
        if (!res->next()) {
            //OutputDebugString(L"hihihi");
            stmt = con->createStatement();
            std::string querystring = "insert into " + tablename + " (date,equipmenttag,equipmentdesc, norunreason, timedetail, starttime, stoptime, timedesc, typeoffault, \
                           fmdesc, process, effectonprocess, attendeename, responsibility, created_by, remarks ) values ('" + dm.date + "' \
                                        ,'" + dm.equipnt + "' \
                                        ,'"+dm.equipdes+"' \
                                        ,'" + dm.norunreason + "' \
                                        ,'" + dm.timedesc +"' \
                                        ,'" + dm.starttime.getMysqlString()+ "' \
                                        ,'" + dm.stoptime.getMysqlString() + "' \
                                        ,'" + getSubHours(dm.starttime, dm.stoptime) + "' \
                                        ,'" + dm.faulttype + "' \
                                        ,'" + base64_encode(reinterpret_cast<const unsigned char*>(dm.faultdesc.c_str()), dm.faultdesc.length()) + "' \
                                        ,'" + dm.processname + "' \
                                        ,'" + base64_encode(reinterpret_cast<const unsigned char*>(dm.processeffect.c_str()), dm.processeffect.length()) + "' \
                                        ,'" + dm.attendeename + "' \
                                        ,'" + dm.responsibility + "' \
                                        ,'" + dm.created_by + "' \
                                        ,'" + base64_encode(reinterpret_cast<const unsigned char*>(dm.remarks.c_str()), dm.remarks.length()) + "')";
            //std::wstring To(querystring.begin(), querystring.end());
            //LPCWSTR Last = To.c_str();
            //OutputDebugString(Last);


                                        res = stmt->executeQuery(querystring);
        }
        else {
            return false;
        }
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * from " + tablename + " where date = '" + dm.date + "' \
                                        AND equipmenttag = '" + dm.equipnt + "' \
                                        AND equipmentdesc = '" + dm.equipdes + "' \
                                        AND norunreason = '" + dm.norunreason + "' \
                                        AND timedetail = '" + dm.timedesc + "' \
                                        AND starttime = '" + dm.starttime.getMysqlString() + "' \
                                        AND stoptime = '" + dm.stoptime.getMysqlString() + "' \
                                        AND timedesc = '" + getSubHours(dm.starttime, dm.stoptime) + "' \
                                        AND typeoffault = '" + dm.faulttype + "' \
                                        AND fmdesc = '" + base64_encode(reinterpret_cast<const unsigned char*>(dm.faultdesc.c_str()), dm.faultdesc.length()) + "' \
                                        AND process = '" + dm.processname + "' \
                                        AND effectonprocess = '" + base64_encode(reinterpret_cast<const unsigned char*>(dm.processeffect.c_str()), dm.processeffect.length()) + "' \
                                        AND attendeename = '" + dm.attendeename + "' \
                                        AND responsibility = '" + dm.responsibility + "' \
                                        AND remarks = '" + base64_encode(reinterpret_cast<const unsigned char*>(dm.remarks.c_str()), dm.remarks.length()) + "'");
        if (!res->next()) {
            return false;
        }
        else {
            return true;
        }

    }
    catch (sql::SQLException &e) {

    }
}

bool dataModel::updatedata(dataobject &dm) {
    try {
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * from " + tablename + " where id = '" + std::to_string(dm.id) + "'");
        if (res->next()) {

            stmt = con->createStatement();
            res = stmt->executeQuery("UPDATE " + tablename + " SET date = '" + dm.date + "' \
                                        , equipmenttag = '" + dm.equipnt + "' \
                                        , equipmentdesc = '" + dm.equipdes + "' \
                                        , norunreason = '" + dm.norunreason + "' \
                                        , timedetail = '" + dm.timedesc + "' \
                                        , starttime = '" + dm.starttime.getMysqlString() + "' \
                                        , stoptime = '" +dm.stoptime.getMysqlString()+ "' \
                                        , timedesc = '" + getSubHours(dm.starttime, dm.stoptime) + "' \
                                        , typeoffault = '" + dm.faulttype + "' \
                                        , fmdesc = '" + base64_encode(reinterpret_cast<const unsigned char*>(dm.faultdesc.c_str()), dm.faultdesc.length()) + "' \
                                        , process = '" + dm.processname + "' \
                                        , effectonprocess = '" + base64_encode(reinterpret_cast<const unsigned char*>(dm.processeffect.c_str()), dm.processeffect.length()) + "' \
                                        , attendeename = '" + dm.attendeename + "' \
                                        , responsibility = '" + dm.responsibility + "' \
                                        , updated_by = '" +dm.updated_by+ "' \
                                        , remarks = '" + base64_encode(reinterpret_cast<const unsigned char*>(dm.remarks.c_str()), dm.remarks.length()) + "' \
                                        WHERE id = '" + std::to_string(dm.id) + "'");

        }
        else {
            return false;
        }

        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * from " + tablename + " where date = '" + dm.date + "' \
                                        AND equipmenttag = '" + dm.equipnt + "' \
                                        AND norunreason = '" + dm.norunreason + "' \
                                        AND timedetail = '" + dm.timedesc + "' \
                                        AND starttime = '" + dm.starttime.getMysqlString() + "' \
                                        AND stoptime = '" + dm.stoptime.getMysqlString() + "' \
                                        AND timedesc = '" + getSubHours(dm.starttime, dm.stoptime) + "' \
                                        AND typeoffault = '" + dm.faulttype + "' \
                                        AND fmdesc = '" + base64_encode(reinterpret_cast<const unsigned char*>(dm.faultdesc.c_str()), dm.faultdesc.length()) + "' \
                                        AND process = '" + dm.processname + "' \
                                        AND effectonprocess = '" + base64_encode(reinterpret_cast<const unsigned char*>(dm.processeffect.c_str()), dm.processeffect.length()) + "' \
                                        AND attendeename = '" + dm.attendeename + "' \
                                        AND responsibility = '" + dm.responsibility + "' \
                                        AND remarks = '" + base64_encode(reinterpret_cast<const unsigned char*>(dm.remarks.c_str()), dm.remarks.length()) + "'");
        if (!res->next()) {
            return false;
        }
        else {
            return true;
        }
    }
    catch (sql::SQLException) {

    }
}


std::vector<dataobject> dataModel::getalldatas() {
    try {
        std::vector<dataobject> datalist;
        stmt = con->createStatement();
        //select * from maindata order by id desc limit 2;
        res = stmt->executeQuery("SELECT * FROM " + tablename + " order by id desc limit 5;");
        while (res->next()) {
            dataobject dao;
            dao.id = res->getInt("id");
            dao.date = res->getString("date");
            dao.equipnt = res->getString("equipmenttag");
            dao.equipdes = base64_decode(res->getString("equipmentdesc"));
            dao.norunreason = res->getString("norunreason");

            dao.timedesc = res->getString("timedetail");
            
            std::string stt = res->getString("starttime");
            std::string spt = res->getString("stoptime");
            
            CDateTime cus;
            dao.starttime = cus.getcdatetime(stt);
            dao.starttime = cus.getcdatetime(spt);

            
            std::string s = res->getString("timedesc");
            std::string delimiter = ":";

            

            size_t pos = 0;
            std::string token;
            pos = s.find(delimiter);
            token = s.substr(0, pos);
//            std::cout << token << std::endl;
            dao.timedeschh = token;
            s.erase(0, pos + delimiter.length());
            
            pos = s.find(delimiter);
            token = s.substr(0, pos);
            dao.timedescmm = token;
            std::cout << token << std::endl;
            s.erase(0, pos + delimiter.length());
            
            dao.timedescss = s;
            //std::cout << s << std::endl;
            
//res->getString("timedesc").substr(0, res->getString("timedesc").find(":"));
            
//            dao.timedescss = res->getString("timedesc");
            
            dao.faulttype = res->getString("typeoffault");
            dao.faultdesc = base64_decode(res->getString("fmdesc"));
            dao.processname = res->getString("process");
            dao.processeffect = base64_decode(res->getString("effectonprocess"));
            dao.attendeename = res->getString("attendeename");
            dao.responsibility = res->getString("responsibility");
            dao.remarks = base64_decode(res->getString("remarks"));
            dao.created_by = res->getString("created_by");
            dao.updated_by = res->getString("updated_by");
            datalist.push_back(dao);
        }
        return datalist;
    }
    catch (sql::SQLException &e) {

    }
}

std::vector<dataobject> dataModel::getalldata() {
    try {
        std::vector<dataobject> datalist;
        stmt = con->createStatement();
        //select * from maindata order by id desc limit 2;
        res = stmt->executeQuery("SELECT * FROM " + tablename + ";");
        while (res->next()) {
            dataobject dao;
            dao.id = res->getInt("id");
            dao.date = res->getString("date");
            dao.equipnt = res->getString("equipmenttag");
            dao.equipdes = base64_decode(res->getString("equipmentdesc"));
            dao.norunreason = res->getString("norunreason");

            dao.timedesc = res->getString("timedetail");

            std::string stt = res->getString("starttime");
            std::string spt = res->getString("stoptime");

            CDateTime cus;
            dao.starttime = cus.getcdatetime(stt);
            dao.starttime = cus.getcdatetime(spt);

            std::string s = res->getString("timedesc");
            std::string delimiter = ":";


            size_t pos = 0;
            std::string token;
            pos = s.find(delimiter);
            token = s.substr(0, pos);
            //            std::cout << token << std::endl;
            dao.timedeschh = token;
            s.erase(0, pos + delimiter.length());

            pos = s.find(delimiter);
            token = s.substr(0, pos);
            dao.timedescmm = token;
            std::cout << token << std::endl;
            s.erase(0, pos + delimiter.length());

            dao.timedescss = s;
            //std::cout << s << std::endl;

//res->getString("timedesc").substr(0, res->getString("timedesc").find(":"));

//            dao.timedescss = res->getString("timedesc");

            dao.faulttype = res->getString("typeoffault");
            dao.faultdesc = base64_decode(res->getString("fmdesc"));
            dao.processname = res->getString("process");
            dao.processeffect = base64_decode(res->getString("effectonprocess"));
            dao.attendeename = res->getString("attendeename");
            dao.responsibility = res->getString("responsibility");
            dao.remarks = base64_decode(res->getString("remarks"));
            dao.created_by = res->getString("created_by");
            dao.updated_by = res->getString("updated_by");
            datalist.push_back(dao);
        }
        return datalist;
    }
    catch (sql::SQLException &e) {

    }
}

dataobject dataModel::getOnedata(std::string &editid) {
    try {
        dataobject dao;
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * FROM " + tablename + " where id = '" + editid + "';");
        while (res->next()) {

            dao.id = res->getInt("id");
            dao.date = res->getString("date");
            dao.equipnt = res->getString("equipmenttag");
            dao.equipdes = base64_decode(res->getString("equipmentdesc"));
            dao.norunreason = res->getString("norunreason");

            dao.timedesc = res->getString("timedetail");
            std::string stt = res->getString("starttime");
            std::string spt = res->getString("stoptime");

            CDateTime cus;
            dao.starttime = cus.getcdatetime(stt);
            dao.starttime = cus.getcdatetime(spt);
            std::string s = res->getString("timedesc");
            std::string delimiter = ":";


            size_t pos = 0;
            std::string token;
            pos = s.find(delimiter);
            token = s.substr(0, pos);
            //            std::cout << token << std::endl;
            dao.timedeschh = token;
            s.erase(0, pos + delimiter.length());

            pos = s.find(delimiter);
            token = s.substr(0, pos);
            dao.timedescmm = token;
            std::cout << token << std::endl;
            s.erase(0, pos + delimiter.length());

            dao.timedescss = s;
            //std::cout << s << std::endl;

//res->getString("timedesc").substr(0, res->getString("timedesc").find(":"));

//            dao.timedescss = res->getString("timedesc");

            dao.faulttype = res->getString("typeoffault");
            dao.faultdesc = base64_decode(res->getString("fmdesc"));
            dao.processname = res->getString("process");
            dao.processeffect = base64_decode(res->getString("effectonprocess"));
            dao.attendeename = res->getString("attendeename");
            dao.responsibility = res->getString("responsibility");
            dao.remarks = base64_decode(res->getString("remarks"));
            dao.created_by = res->getString("created_by");
            dao.updated_by = res->getString("updated_by");
        
        }

        return dao;
    }
    catch (sql::SQLException &e) {

    }
}

std::vector<std::string> dataModel::equipDelaytime(std::string &equip) {
    try {
        std::vector<std::string> timedesc;
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT timedesc FROM " + tablename + " where timedetail = 'delay' and equipmenttag = '" + equip + "';");
        while (res->next()) {
        
            timedesc.push_back(res->getString("timedesc"));
        }
        return timedesc;
    }
    catch (sql::SQLException &e) {

    }
}
std::vector<std::string> dataModel::equipDowntime(std::string &equip) {
    try {
        std::vector<std::string> timedesc;
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT timedesc FROM " + tablename + " where timedetail = 'downtime' and equipmenttag = '" + equip + "';");
        while (res->next()) {

            timedesc.push_back(res->getString("timedesc"));
        }
        return timedesc;
    }
    catch (sql::SQLException &e) {

    }
}

bool dataModel::deletedata(std::string &dataid) {
    try {
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * from " + tablename + " where id = '" + dataid + "'");
        if (res->next()) {
            stmt = con->createStatement();

            res = stmt->executeQuery("delete from " + tablename + " where id = '" + dataid + "'");
            //stmt = con->createStatement();

        }
        else {
            return false;
        }
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * from " + tablename + " where id = '" + dataid + "'");
        if (!res->next()) {
            return true;
        }
        else {
            return false;
        }

    }
    catch (sql::SQLException &e) {

    }
}
