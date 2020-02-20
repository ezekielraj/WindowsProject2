#pragma once 
        
#include <iostream>
#include <windows.h>
#include "Pages.h"
#include "DBhandler.h"
#include "userModel.h"
#include "base64.h"
#include "loginpage.h"

#define IDM_ADMIN_PAGE 6005

#ifndef LOGINPAGES_CPP_INCLUDED
#define LOGINPAGES_CPP_INCLUDED
#define LOGINEVENT 5000

    loginpage::loginpage(HWND &hwnd) : pages(7) {
        lphwnd = hwnd;
        
    }
    void loginpage::CreatePage() {
        std::cout << "creating loginpage" << std::endl;

        pageentries[0] = CreateWindowA("STATIC",
            "LOGIN PAGE",
            WS_VISIBLE | WS_CHILD,
            20, 20, 300, 25,
            lphwnd,
            NULL, NULL, NULL
        );

        pageentries[1] = CreateWindowA("STATIC",
            "Username :",
            WS_VISIBLE | WS_CHILD,
            40, 60, 150, 25,
            lphwnd,
            NULL, NULL, NULL
        );
        pageentries[2] = CreateWindowA("STATIC",
            "Password :",
            WS_VISIBLE | WS_CHILD,
            40, 90, 150, 25,
            lphwnd,
            NULL, NULL, NULL
        );
        pageentries[3] = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), TEXT(""),
            WS_CHILD | WS_VISIBLE,
            200, 60, 140, 20,
            lphwnd, NULL, NULL, NULL);
        pageentries[4] = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), TEXT(""),
            WS_CHILD | WS_VISIBLE | ES_PASSWORD,
            200, 90, 140, 20,
            lphwnd, NULL, NULL, NULL);
        pageentries[5] = CreateWindowA(
            "BUTTON",  // Predefined class; Unicode assumed
            "LOGIN",      // Button text
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
            120,         // x position
            140,         // y position
            100,        // Button width
            30,        // Button height
            lphwnd,     // Parent window
            (HMENU)LOGINEVENT,       // No menu.
            (HINSTANCE)GetWindowLong(lphwnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.

        pageentries[6] = CreateWindowA("STATIC",
            "",
            WS_VISIBLE | WS_CHILD,
            120, 180, 200, 30,
            lphwnd,
            NULL, NULL, NULL
        ); 
    }

    void loginpage::HandleNotifyEvent(WPARAM &wParam, LPARAM &lParam){ }

    void loginpage::HandleEvent(WPARAM wParam, LPARAM lParam) {
        switch (LOWORD(wParam))
        {
        case LOGINEVENT:
        {

            int ulenn = GetWindowTextLengthW(pageentries[3]) + 1;
            int plenn = GetWindowTextLengthW(pageentries[4]) + 1;
            if (ulenn > 1 && plenn > 1) {
                wchar_t* username = new wchar_t[ulenn];
                wchar_t* password = new wchar_t[plenn];
                GetWindowTextW(pageentries[3], username, ulenn);
                GetWindowTextW(pageentries[4], password, plenn);
                
                std::wstring wsuser(username);
                std::wstring wspass(password);

                std::string struser(wsuser.begin(), wsuser.end());
                std::string strpass(wspass.begin(), wspass.end());

                std::string encodedpass = base64_encode(reinterpret_cast<const unsigned char*>(strpass.c_str()), strpass.length());
                
                userModel um;
                um.OpenConnection();
                std::string pass = um.getPassword(struser);
                um.closeConnection();
                if (pass.compare(encodedpass) == 0) {
                    //MessageBoxA(NULL, "Authenticated", "User-id", MB_OK);
                    loginpage::Authenticated = true;
                    SendMessage(lphwnd,WM_COMMAND, MAKEWPARAM(IDM_ADMIN_PAGE, GetDlgCtrlID(lphwnd)),
                        (LPARAM)lphwnd);
                }
                else {
                    MessageBoxA(NULL, "Username or password is wrong", "User-id", MB_OK);
                    loginpage::Authenticated = false;
                }
                //MessageBoxA(NULL, pass.c_str(), "User-id", MB_OK);
                //MessageBoxA(NULL, encodedpass.c_str(), "User-id", MB_OK);

            }
            else {

                SetWindowTextA(pageentries[6], "Please fill username and password!!!");
            }



            break;
        }
        default:
            break;
        }


    }
    loginpage::~loginpage() {
        DestroyPage();
    }

    bool loginpage::Authenticated = false;
#endif

