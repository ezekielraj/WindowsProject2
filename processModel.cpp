#include "processModel.h"

processModel::processModel() {
    OpenConnection();
    try {
        stmt = con->createStatement();
        stmt->execute("CREATE TABLE IF NOT EXISTS `processes` ( \
            `id` int(10) unsigned NOT NULL AUTO_INCREMENT, \
            `processname` varchar(256) NOT NULL, \
            `description` varchar(1024), \
            PRIMARY KEY(`id`), \
            UNIQUE KEY unique_pname (processname) \
            ) ENGINE = InnoDB");
        //delete stmt;
    }
    catch (sql::SQLException &e) {

    }
    closeConnection();
}

bool processModel::insertpname(std::string &pname) {
    try {
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * from " + tablename + " where processname = '" + pname + "'");
        if (!res->next()) {
            stmt = con->createStatement();
            res = stmt->executeQuery("insert into " + tablename + " (processname) values ('" + pname + "')");
            

        }
        else {
            return false;
        }
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * from " + tablename + " where processname = '" + pname + "'");
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

std::vector<processobj> processModel::getallprocess() {
    try {
        std::vector<processobj> processlist;
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * FROM " + tablename);
        while (res->next()) {
            processobj pobj;
            pobj.id = res->getInt("id");
            pobj.processname = res->getString("processname");
            processlist.push_back(pobj);
        }
        return processlist;
    }
    catch (sql::SQLException &e) {

    }
}

bool processModel::deleteprocess(std::string &processid) {
    try {
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * from " + tablename + " where id = '" + processid + "'");
        if (res->next()) {
            stmt = con->createStatement();

            res = stmt->executeQuery("delete from " + tablename + " where id = '" + processid + "'");
            //stmt = con->createStatement();

        }
        else {
            return false;
        }
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * from " + tablename + " where id = '" + processid + "'");
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