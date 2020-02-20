#include "employeeModel.h"
#include "Base64.h"

employeeModel::employeeModel() {
    OpenConnection();
    try {
        stmt = con->createStatement();
        stmt->execute("CREATE TABLE IF NOT EXISTS `employee` ( \
            `id` int(10) unsigned NOT NULL AUTO_INCREMENT, \
            `employeenum` varchar(256) NOT NULL, \
            `employeename` varchar(256) NOT NULL, \
            `password` varchar(512) NOT NULL, \
            PRIMARY KEY(`id`), \
            UNIQUE KEY unique_empnum (employeenum) \
            ) ENGINE = InnoDB");
        //delete stmt;
        stmt = con->createStatement();
        res = stmt->executeQuery("show columns from `employee` like 'password'");
        if (!res->next()) {
            stmt = con->createStatement();
            stmt->execute("alter table `employee` add password varchar(512) not null after `employeename`");
        }
    }
    catch (sql::SQLException &e) {

    }
    closeConnection();

}

bool employeeModel::insemployee(std::string &empnum, std::string &empname, std::string &emppass) {
    try {
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * from " + tablename + " where employeenum = '" + empnum + "'");
        if (!res->next()) {
            stmt = con->createStatement();

            res = stmt->executeQuery("insert into " + tablename + " (employeenum, employeename, password) values ('" + empnum + "','"+empname+"', \
                '"+ base64_encode(reinterpret_cast<const unsigned char*>(emppass.c_str()), emppass.length()) +"')");
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

empobjects employeeModel::getoneEmployee(std::string &id) {
    try {
        empobjects empobj;
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * FROM " + tablename + " where id = '"+id+"'");
        if (res->next()) {
            empobj.id = res->getInt("id");
            empobj.empnum = res->getString("employeenum");
            empobj.empname = res->getString("employeename");
            empobj.password = base64_decode(res->getString("password"));
        }
        return empobj;
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

bool employeeModel::updateemployee(empobjects &eo) {
    try {
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * FROM " + tablename + " where id = '" + std::to_string(eo.id) + "'");
        if (res->next()) {
            stmt = con->createStatement();
            res = stmt->executeQuery("UPDATE " + tablename + " SET employeenum='" + eo.empnum + "', employeename = '"+eo.empname+"',password ='" + base64_encode(reinterpret_cast<const unsigned char*>(eo.password.c_str()), eo.password.length()) + "' where id = '" + std::to_string(eo.id) + "'");

        }
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * FROM " + tablename + " where id = '" + std::to_string(eo.id) + "'");
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

std::string employeeModel::getPassword(std::string &username) {
    try {
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT password FROM " + tablename + " where employeenum = '" + username + "' or employeename = '"+username+"'");

        if (res->next()) {
            return res->getString("password");
        }
        return "";
    }
    catch (sql::SQLException &e) {

    }
}