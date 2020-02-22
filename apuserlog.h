#pragma once
#include <windows.h>
#include "Pages.h"

class apuserlog :
    public pages
{
private:
    HWND ulhwnd;
public:
    apuserlog(HWND&);
    void CreatePage();
    void HandleEvent(WPARAM, LPARAM);
    void HandleNotifyEvent(WPARAM&, LPARAM&);

    ~apuserlog();


};

