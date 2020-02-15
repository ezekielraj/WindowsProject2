#pragma once
#include <windows.h>
#include "Pages.h"
class dbbackuppage :
    public pages
{
private:
    static bool eqeditmode;
    HWND dbhwnd;

    void AppendText(HWND &pageentry, std::string newText);
public:
    dbbackuppage(HWND&);
    void CreatePage();
    void HandleEvent(WPARAM, LPARAM);
    void HandleNotifyEvent(WPARAM&, LPARAM&);

    ~dbbackuppage();

};

