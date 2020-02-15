#include<iostream>
#include <tchar.h>
#include <windows.h>
#include "Pages.h"
#include "Resource.h"

#include <commctrl.h>
#include <richedit.h>

#ifndef HOMEPAGES_CPP_INCLUDED
#define HOMEPAGES_CPP_INCLUDED

class homepage : public pages
{

private:
    HWND hphwnd;
public:
    homepage(HWND &hwnd) :pages(5) {
        hphwnd = hwnd;
    }
    void CreatePage() {
        std::cout << "creating homepage" << std::endl;
        pageentries[0] = CreateWindowA("STATIC",
                "DIGITIZATION", 
                WS_VISIBLE | WS_CHILD, 20, 20, 300, 25,
                hphwnd, NULL, NULL, NULL
            );  
        
 /*       pageentries[1] = CreateWindowW(L"SysMonthCal32", NULL,

            WS_VISIBLE | WS_CHILD | WS_TABSTOP,

            20, 60, 225, 160, hphwnd, NULL, NULL, NULL);
            */
    }
    void HandleEvent(WPARAM wParam, LPARAM lParam){ }
    void HandleNotifyEvent(WPARAM &wParam, LPARAM &lParam) {
        //MessageBoxW(hphwnd, L"asdf", L"asdf", MB_OK);
       switch (((LPNMHDR)lParam)->code) {
        case MCN_SELECT:
            
            break;
        default:
            break;
        }


    }
    ~homepage() {
        DestroyPage();
    }
};

#endif