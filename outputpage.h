#pragma once
#include<windows.h>
#include "Pages.h"
#include "dataModel.h"

class outputpage :
    public pages
{
private:
    HWND ophwnd;
    TCHAR  EquipNT[256];
    void filltenentries(int);
    std::vector<dataobject> datalist;
    int ctp;
public:

    outputpage(HWND&);
    void CreatePage();
    void HandleEvent(WPARAM, LPARAM);
    void HandleNotifyEvent(WPARAM&, LPARAM&);
    ~outputpage();


};

