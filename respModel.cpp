#include "respModel.h"

respModel::respModel()
{
    OpenConnection();
    try {
        stmt = con->createStatement();
        stmt->execute("CREATE TABLE IF NOT EXISTS `responsibility` ( \
            `id` int(10) unsigned NOT NULL AUTO_INCREMENT, \
            `respname` varchar(256) NOT NULL, \
            PRIMARY KEY(`id`), \
            UNIQUE KEY unique_respname (respname) \
            ) ENGINE = InnoDB");
        //delete stmt;
    }
    catch (sql::SQLException &e) {

    }
    closeConnection();
}

bool respModel::insertresp(std::string &respname) {
    try {
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * from " + tablename + " where respname = '" + respname + "'");
        if (!res->next()) {
            stmt = con->createStatement();

            res = stmt->executeQuery("insert into " + tablename + " (respname) values ('" + respname + "')");
            //stmt = con->createStatement();

        }
        else {
            return false;
        }
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * from " + tablename + " where respname = '" + respname + "'");
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


std::vector<respData> respModel::getallresp() {
    try {
        std::vector<respData> resplist;
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * FROM " + tablename);
        while (res->next()) {
            respData rpdata;
            rpdata.id = res->getInt("id");
            rpdata.respname = res->getString("respname");

            resplist.push_back(rpdata);
        }
        return resplist;
    }
    catch (sql::SQLException &e) {

    }
}

bool respModel::deleteresp(std::string &respid) {
    try {
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * from " + tablename + " where id = '" + respid + "'");
        if (res->next()) {
            stmt = con->createStatement();

            res = stmt->executeQuery("delete from " + tablename + " where id = '" + respid + "'");
            //stmt = con->createStatement();

        }
        else {
            return false;
        }
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * from " + tablename + " where id = '" + respid + "'");
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