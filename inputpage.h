#pragma once
#include <windows.h>
#include "Pages.h"

class inputpage :
    public pages
{
private:
    static bool EditMode;
    HWND iphwnd;
    TCHAR  EquipNT[256];
    TCHAR  NoRR[256];
    //TCHAR  TimeDetail[256];
    TCHAR  TimeDescSelect[256];
    TCHAR  ProcessScope[256];
    TCHAR  AttendeeName[256];
    TCHAR  Responsibility[256];
    TCHAR  FaultType[256];
    bool equipdesc = false;
public:
    inputpage(HWND&);
    void CreatePage();
    void HandleEvent(WPARAM, LPARAM);
    void HandleNotifyEvent(WPARAM&, LPARAM&);
    void fillallDataentries();
    ~inputpage();

};

