#pragma once
#include<windows.h>
#include "Pages.h"
class outputpage :
    public pages
{
private:
    HWND ophwnd;
    TCHAR  EquipNT[256];
public:
    outputpage(HWND&);
    void CreatePage();
    void HandleEvent(WPARAM, LPARAM);
    void HandleNotifyEvent(WPARAM&, LPARAM&);
    ~outputpage();


};

