#include "equipModel.h"
#include "base64.h"
#include "windows.h"
equipModel::equipModel()
{
    OpenConnection();
    try {
        stmt = con->createStatement();
        stmt->execute("CREATE TABLE IF NOT EXISTS `equipment` ( \
            `id` int(10) unsigned NOT NULL AUTO_INCREMENT, \
            `equipnt` varchar(256) NOT NULL, \
            `description` varchar(1024), \
            PRIMARY KEY(`id`), \
            UNIQUE KEY unique_equipnt (equipnt) \
            ) ENGINE = InnoDB");
        //delete stmt;
    }
    catch (sql::SQLException &e) {

    }
    closeConnection();
}

bool equipModel::deleteequipnt(std::string &equipid) {
    try {
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * from " + tablename + " where id = '" + equipid + "'");
        if (res->next()) {
            stmt = con->createStatement();

            res = stmt->executeQuery("delete from " + tablename + " where id = '" + equipid + "'");
            //stmt = con->createStatement();

        }
        else {
            return false;
        }
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * from " + tablename + " where id = '" + equipid + "'");
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

bool equipModel::insertequipnt(std::string &equipnt, std::string &equipdes) {
    try {
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * from " + tablename + " where equipnt = '" + equipnt + "'");// and description = '"+ base64_encode(reinterpret_cast<const unsigned char*>(equipdes.c_str()), equipdes.length()) +"'");
        if (!res->next()) {
            stmt = con->createStatement();

            res = stmt->executeQuery("insert into " + tablename + " (equipnt, description) values ('" + equipnt + "','"+ base64_encode(reinterpret_cast<const unsigned char*>(equipdes.c_str()), equipdes.length()) +"')");
            //stmt = con->createStatement();
        
        }
        else {
            return false;
        }
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * from " + tablename + " where equipnt = '" + equipnt + "'");// and description = '" + base64_encode(reinterpret_cast<const unsigned char*>(equipdes.c_str()), equipdes.length()) + "'");
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

std::vector<std::string> equipModel::getallequipnt() {
    try {
        std::vector<std::string> equiplist;
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * FROM " + tablename);
        while (res->next()) {
            equiplist.push_back(res->getString("equipnt"));
        }
        return equiplist;
    }
    catch (sql::SQLException &e) {

    }
}

std::vector<equipData> equipModel::getallequipnts() {
    try {
        std::vector<equipData> equiplist;
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * FROM " + tablename);
        while (res->next()) {
            equipData eqdata;
            eqdata.id = res->getInt("id");
            eqdata.equipnt = res->getString("equipnt");
            eqdata.description = base64_decode(res->getString("description"));

            equiplist.push_back(eqdata);
        }
        return equiplist;
    }
    catch (sql::SQLException &e) {

    }
}

std::string equipModel::getDescription(std::string &equipnt) {
    try {
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * FROM " + tablename + " where equipnt = '" + equipnt + "'");
        while (res->next()) {
            return res->getString("description");
        }
        return "";
    }
    catch (sql::SQLException &e) {

    }
}

equipData equipModel::getoneequip(std::string &id) {
    try {
        stmt = con->createStatement();
        equipData ed;
        res = stmt->executeQuery("SELECT * FROM " + tablename + " where id = '" + id + "'");
        while (res->next()) {
            ed.equipnt = res->getString("equipnt");
             ed.description = base64_decode(res->getString("description"));
        }
        return ed;
    }
    catch (sql::SQLException &e) {

    }
}

bool equipModel::updateequip(equipData &ed) {
    try {
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * FROM " + tablename + " where id = '" + std::to_string(ed.id) + "'");
        if (res->next()) {
            stmt = con->createStatement();
            res = stmt->executeQuery("UPDATE " + tablename + " SET equipnt='"+ed.equipnt+"', description ='"+ base64_encode(reinterpret_cast<const unsigned char*>(ed.description.c_str()), ed.description.length()) +"' where id = '" + std::to_string(ed.id) + "'");
            
        }
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * FROM " + tablename + " where id = '" + std::to_string(ed.id) + "'");
        if (res->next()) {
            return true;
        }
        else {
            return false;
        }
    }
    catch (sql::SQLException &e) {

    }
}