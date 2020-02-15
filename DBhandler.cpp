#include "DBhandler.h"

void DBhandler::OpenConnection() {
    try{
        driver = get_driver_instance();
        con = driver->connect("tcp://127.0.0.1:55555", "root", "123456");
        /* Connect to the MySQL test database */
        con->setSchema("digitization");
    }
    catch (sql::SQLException &e) {
        
    }
}

void DBhandler::testInsert() {
    try{
        pstmt = con->prepareStatement("INSERT INTO digitization.motorlist (motorname) VALUES (?)");
        pstmt->setString(1,"hi");
        pstmt->executeUpdate();
    }
    catch (sql::SQLException &e) {

    }
}

void DBhandler::closeConnection() {
    try {

        delete res;
        delete stmt;
        delete con;
        delete pstmt;
    }
    catch (sql::SQLException &e) {

    }
}