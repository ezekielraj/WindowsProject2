#include "employeeModel.h"

employeeModel::employeeModel() {
    OpenConnection();
    try {
        stmt = con->createStatement();
        stmt->execute("CREATE TABLE IF NOT EXISTS `employee` ( \
            `id` int(10) unsigned NOT NULL AUTO_INCREMENT, \
            `employeenum` varchar(256) NOT NULL, \
            `employeename` varchar(256) NOT NULL, \
            PRIMARY KEY(`id`), \
            UNIQUE KEY unique_empnum (employeenum) \
            ) ENGINE = InnoDB");
        //delete stmt;
    }
    catch (sql::SQLException &e) {

    }
    closeConnection();

}

bool employeeModel::insemployee(std::string &empnum, std::string &empname) {
    try {
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * from " + tablename + " where employeenum = '" + empnum + "'");
        if (!res->next()) {
            stmt = con->createStatement();

            res = stmt->executeQuery("insert into " + tablename + " (employeenum, employeename) values ('" + empnum + "','"+empname+"')");
           // stmt = con->createStatement();

        }
        else {
            return false;
        }
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * from " + tablename + " where employeenum = '" + empnum + "'");
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

std::vector<empobjects> employeeModel::getallemployees() {
    try {
        std::vector<empobjects> emplist;
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * FROM " + tablename);
        while (res->next()) {
            empobjects empobj;
            empobj.id = res->getInt("id");
            empobj.empnum = res->getString("employeenum");
            empobj.empname = res->getString("employeename");
            emplist.push_back(empobj);
        }
        return emplist;
    }
    catch (sql::SQLException &e) {

    }
}

bool employeeModel::deleteemp(std::string &empid) {
    try {
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * from " + tablename + " where id = '" + empid + "'");
        if (res->next()) {
            stmt = con->createStatement();

            res = stmt->executeQuery("delete from " + tablename + " where id = '" + empid + "'");
            //stmt = con->createStatement();

        }
        else {
            return false;
        }
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * from " + tablename + " where id = '" + empid + "'");
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