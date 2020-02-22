#include "apuserlog.h"
#include "dataModel.h"
#include "employeeModel.h"

#include <sstream>
#include <iomanip>

#define GETDATA 901

apuserlog::apuserlog(HWND &hwnd) : pages(50) {
    ulhwnd = hwnd;

}

apuserlog::~apuserlog() {
    DestroyPage();
}

void apuserlog::CreatePage() {
    pageentries[0] = CreateWindowW(L"SysDateTimePick32", NULL,

        WS_BORDER | WS_VISIBLE | WS_CHILD | WS_TABSTOP,

        50, 75, 150, 30, ulhwnd, NULL, NULL, NULL);

    pageentries[1] = CreateWindowA(
        "BUTTON",  // Predefined class; Unicode assumed
        "Get Data",      // Button text
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
        205,         // x position
        75,         // y position
        100,        // Button width
        30,        // Button height
        ulhwnd,     // Parent window
        (HMENU)GETDATA,       // No menu.
        (HINSTANCE)GetWindowLong(ulhwnd, GWLP_HINSTANCE),
        NULL);
    pageentries[2] = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), TEXT(""),
        WS_CHILD | WS_VISIBLE | WS_VSCROLL |
        ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,
        50, 110, 200, 300,
        ulhwnd, NULL, NULL, NULL);
}

void apuserlog::HandleNotifyEvent(WPARAM &wParam, LPARAM &lParam) { }

void apuserlog::HandleEvent(WPARAM wParam, LPARAM lParam) {

    switch (LOWORD(wParam))
    {
        case GETDATA:
        {
            dataModel dm;
            dm.OpenConnection();

            int tdhhlen = GetWindowTextLengthW(pageentries[0]) + 1;
            wchar_t* tdhhval = new wchar_t[tdhhlen];
            GetWindowTextW(pageentries[0], tdhhval, tdhhlen);

            std::wstring wstdhhval(tdhhval);
            std::string strtdhhval(wstdhhval.begin(), wstdhhval.end());

            std::string delimiter = "/";
            size_t pos = 0;
            std::string token;
            pos = strtdhhval.find(delimiter);
            token = strtdhhval.substr(0, pos);
            //            std::cout << token << std::endl;
            std::stringstream ss;
            ss << std::setw(2) << std::setfill('0') << token;
            std::string month = ss.str();

            //std::string month = token;
            strtdhhval.erase(0, pos + delimiter.length());

            pos = strtdhhval.find(delimiter);
            token = strtdhhval.substr(0, pos);
            std::stringstream ssd;
            ssd << std::setw(2) << std::setfill('0') << token;

            std::string day = ssd.str();
            std::cout << token << std::endl;
            strtdhhval.erase(0, pos + delimiter.length());

            std::string year = strtdhhval;

            std::string completedate = year + "-" + month + "-" + day;

           // MessageBox(ulhwnd, std::wstring(completedate.begin(), completedate.end()).c_str(),L"", MB_OK );
            std::vector<std::string> userdetails=dm.getUserDetails(completedate);
            dm.closeConnection();
            std::string ft = "User Log Details\r\n";
            employeeModel em;
            em.OpenConnection();
            empobjects eb;
            for (auto it = userdetails.begin(); it != userdetails.end(); ++it) {
                eb = em.getoneEmployee(*it);
                ft = ft + std::to_string(eb.id) + "\t" + eb.empnum + "\t" + eb.empname + "\r\n";
            }
            em.closeConnection();
            SetWindowTextA(pageentries[2], ft.c_str());
           
        }
            break;
        default:
            break;
    }
}
