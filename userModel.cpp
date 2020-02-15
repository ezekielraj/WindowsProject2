#include "userModel.h"

userModel::userModel() {
    OpenConnection();
    try {
        stmt = con->createStatement();
        stmt->execute("CREATE TABLE IF NOT EXISTS `user` ( \
            `id` int(10) unsigned NOT NULL AUTO_INCREMENT, \
            `username` varchar(256) NOT NULL, \
            `password` varchar(256) NOT NULL, \
            PRIMARY KEY(`id`) \
            ) ENGINE = InnoDB");
        //delete stmt;
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * from user where username = 'admin'");
        //res = stmt->getResultSet();
        if (!res->next()) {
                stmt = con->createStatement();
                stmt->executeQuery("INSERT INTO `user` (username, password) VALUES ('admin', 'YWRtaW4xMjM=')");
            
         }
    }
    catch (sql::SQLException &e) {

    }
    closeConnection();
}

std::string userModel::getPassword(std::string username) {
    try {
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * from " + tablename + " where username = '" + username + "'");
        while (res->next()) {
            return res->getString("password");
        }
    }catch(sql::SQLException &e){
        
        return "failed";
    }
}

