#include "faultModel.h"

faultModel::faultModel() {
    OpenConnection();
    try {
        stmt = con->createStatement();
        stmt->execute("CREATE TABLE IF NOT EXISTS `faulttypes` ( \
            `id` int(10) unsigned NOT NULL AUTO_INCREMENT, \
            `faulttype` varchar(256) NOT NULL, \
            `description` varchar(1024), \
            PRIMARY KEY(`id`), \
            UNIQUE KEY unique_fname (faulttype) \
            ) ENGINE = InnoDB");
        //delete stmt;
    }
    catch (sql::SQLException &e) {

    }
    closeConnection();
}

bool faultModel::insertftype(std::string &ftype) {
    try {
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * from " + tablename + " where faulttype = '" + ftype + "'");
        if (!res->next()) {
            stmt = con->createStatement();

            res = stmt->executeQuery("insert into " + tablename + " (faulttype) values ('" + ftype + "')");
            //stmt = con->createStatement();

        }
        else {
            return false;
        }
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * from " + tablename + " where faulttype = '" + ftype + "'");
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

std::vector<faultobj> faultModel::getallfaults() {
    try {
        std::vector<faultobj> faultlist;
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * FROM " + tablename);
        while (res->next()) {
            faultobj pobj;
            pobj.id = res->getInt("id");
            pobj.faulttype = res->getString("faulttype");
            faultlist.push_back(pobj);
        }
        return faultlist;
    }
    catch (sql::SQLException &e) {

    }
}

bool faultModel::deletefault(std::string &faultid) {
    try {
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * from " + tablename + " where id = '" + faultid + "'");
        if (res->next()) {
            stmt = con->createStatement();

            res = stmt->executeQuery("delete from " + tablename + " where id = '" + faultid + "'");
            //stmt = con->createStatement();

        }
        else {
            return false;
        }
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * from " + tablename + " where id = '" + faultid + "'");
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