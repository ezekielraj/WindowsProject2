#pragma once

#include <windows.h>
#include "Pages.h"
class loginpage : public pages
{
private:
    HWND lphwnd;
public:
    static bool Authenticated;
    loginpage(HWND&);
    void CreatePage();
    void HandleEvent(WPARAM , LPARAM );
    void HandleNotifyEvent(WPARAM&, LPARAM&);
    ~loginpage();
};
