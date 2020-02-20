#pragma once

#include <windows.h>
#include "Pages.h"
class loginpage : public pages
{
private:
    HWND lphwnd;
public:
    static bool Authenticated;
    static bool UserAuthenticated;
    static std::string UserEmployeeid;
    loginpage(HWND&);
    void CreatePage();
    void HandleEvent(WPARAM , LPARAM );
    void HandleNotifyEvent(WPARAM&, LPARAM&);
    ~loginpage();
};
