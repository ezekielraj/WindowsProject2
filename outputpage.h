#pragma once
#include<windows.h>
#include "Pages.h"
class outputpage :
    public pages
{
private:
    HWND ophwnd;
public:
    outputpage(HWND&);
    void CreatePage();
    void HandleEvent(WPARAM, LPARAM);
    void HandleNotifyEvent(WPARAM&, LPARAM&);
    ~outputpage();


};

