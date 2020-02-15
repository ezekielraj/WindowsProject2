#pragma once

#include <windows.h>
#include "Pages.h"
class adminpage :
    public pages
{
private:
    static bool eqeditmode;
    HWND aphwnd;
public:
    adminpage(HWND&);
    void CreatePage();
    void HandleEvent(WPARAM, LPARAM);
    void HandleNotifyEvent(WPARAM&, LPARAM&);
    void fillEquipEntries();
    void fillEmployeeEntries();
    void fillProcessEntries();
    void fillFaultEntries();
    void fillRespEntries();
    ~adminpage();

};

