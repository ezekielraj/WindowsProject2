#pragma once
#include "DBhandler.h"
#include <windows.h>
#include "jdbc/mysql_connection.h"

#include <jdbc/cppconn/driver.h>
#include <jdbc/cppconn/exception.h>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/cppconn/statement.h>
#include <jdbc/cppconn/prepared_statement.h>


class DBhandler
{
    public:
        static HWND dbhwnd;
        void OpenConnection();
        void closeConnection();
        void testInsert();



    protected:
        sql::Driver *driver;
        sql::Connection *con;
        sql::Statement *stmt;
        sql::ResultSet *res;
        sql::PreparedStatement *pstmt;

};

