#include "inputpage.h"

#include <commctrl.h>
#include <richedit.h>

#include "equipModel.h"
#include "processModel.h"
#include "employeeModel.h"
#include "faultModel.h"
#include "dataModel.h"
#include "respModel.h"
#include <vector>
#include <string>
#include <atlstr.h>
#include "Logger.h"

#define CMBOX1 7000
#define CMBOX2 7001
#define CMBOX3 7002
#define CMBOX4 7003
#define CMBOX5 7004
#define CMBOX6 7007
#define CMBOX7 7008
#define SUBMITINPUT 7005
#define SUBMITCLEAR 7006
#define EDITDATA 7009
#define IDB_CHECKBOX 7010
#define DELETEDATA 7011

#define LOGFORDEBUG 1
inline void iplogger(std::string str){ 
    if(LOGFORDEBUG) LOGGER->Log("Input page: " + str);

}
inputpage::inputpage(HWND &hwnd) : pages(50) {
    iphwnd = hwnd;

}
void inputpage::CreatePage() {
    iplogger(std::string("CreatePage() starting"));
    std::cout << "creating inputpage" << std::endl;
    pageentries[0] = CreateWindowA("STATIC",
        "INPUT PAGE",
        WS_VISIBLE | WS_CHILD,
        20, 20, 300, 25,
        iphwnd,
        NULL, NULL, NULL
    );
  /*  1.	Date(calendar selection type.)
        2.	Equipment name / tag(to be selected from drop down menu)
        3.	NO run reason(fault / maintenance / Greasing / main equip run)
        4.	Time description select(delay / downtime) (time format HH : MM: SS)
        5.	If Fault then Type of fault(breakdown, tripping) (TRIP TYPE CLIENT SCOPE)
        6.	Description of(fault / maintenance)
        7.	Process(Process  CLIENT SCOPE)
        8.	Effect on process. (Individual process stop / Wind volume reduction / NA)
        9.	Attended by Name Unique ID number.
        10.	Remarks
*/
    pageentries[1] = CreateWindowA("STATIC",
        "",
        WS_VISIBLE | WS_CHILD,
        40, 60, 180, 25, 
        iphwnd,
        NULL, NULL, NULL
    );

    pageentries[2] = CreateWindowW(L"SysMonthCal32", NULL,

        WS_BORDER | WS_VISIBLE | WS_CHILD | WS_TABSTOP,

        40, 90, 180, 160, iphwnd, NULL, NULL, NULL);
    pageentries[4] = CreateWindowA("STATIC",
        "Equipment Name/Tag",
        WS_VISIBLE | WS_CHILD,
        260, 60, 150, 25,
        iphwnd,
        NULL, NULL, NULL
    );

    SYSTEMTIME time;
    wchar_t s_buf[500];
    ZeroMemory(&time, sizeof(SYSTEMTIME));

    SendMessageW(pageentries[2], MCM_GETCURSEL, 0, (LPARAM)&time);
    wsprintf(s_buf, L"%d-%d-%d", time.wYear, time.wMonth, time.wDay);
    std::wstring wsbuf(s_buf);
    std::string strsbuf(wsbuf.begin(), wsbuf.end());
    SetWindowTextA(pageentries[1], (strsbuf).c_str());

    pageentries[3] = CreateWindowA("ComboBox", "",
        CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | WS_VSCROLL | CBS_AUTOHSCROLL |
        ES_LEFT | WS_HSCROLL,
        260, 90, 150, 200, iphwnd, (HMENU)CMBOX1, NULL,
        NULL);
    pageentries[35] = CreateWindowEx(
        0,
        L"BUTTON",
        L"Equipment Desc",
        WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
        260,
        120,
        150,
        25,
        iphwnd,
        (HMENU)IDB_CHECKBOX,
        (HINSTANCE)GetWindowLong(iphwnd, GWLP_HINSTANCE),
        NULL); //CreateWindowA("BUTTON", "Checkbox", BS_CHECKBOX, 260, 130, 150, 25, iphwnd, NULL, NULL, NULL);
        
        pageentries[5] = CreateWindowA("STATIC",
            "No Run Reason",
            WS_VISIBLE | WS_CHILD,
            260, 160, 150, 25,
            iphwnd,
            NULL, NULL, NULL
        );

        pageentries[6] = CreateWindowA("ComboBox", "",
            CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | WS_VSCROLL | CBS_AUTOHSCROLL |
            ES_LEFT | WS_HSCROLL,
            260, 190, 150, 200, iphwnd, (HMENU)CMBOX2, NULL,
            NULL);

        //200
        //230
        pageentries[27] = CreateWindowA("STATIC",
            "Type of Fault",
            WS_VISIBLE | WS_CHILD,
            260, 220, 150, 25,
            iphwnd,
            NULL, NULL, NULL
        );

        pageentries[28] = CreateWindowA("ComboBox", "",
            CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | WS_VSCROLL | CBS_AUTOHSCROLL |
            ES_LEFT | WS_HSCROLL,
            260, 240, 150, 200, iphwnd, (HMENU)CMBOX6, NULL,
            NULL);


        pageentries[7] = CreateWindowA("STATIC",
            "Time Desc Select",
            WS_VISIBLE | WS_CHILD,
            260, 270, 150, 25,
            iphwnd,
            NULL, NULL, NULL
        );

        pageentries[8] = CreateWindowA("ComboBox", "",
            CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | WS_VSCROLL | CBS_AUTOHSCROLL |
            ES_LEFT | WS_HSCROLL,
            260, 300, 150, 200, iphwnd, (HMENU)CMBOX3, NULL,
            NULL);
        //340
        //370

        /*pageentries[9] = CreateWindowA("STATIC",
            "Delay or Down Time\n HH      : MM     : SS",
            WS_VISIBLE | WS_CHILD,
            260, 330, 150, 34,
            iphwnd,
            NULL, NULL, NULL
        );

        pageentries[10] = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), TEXT(""),
            WS_CHILD | WS_VISIBLE,
            260, 360, 46, 25,
            iphwnd, NULL, NULL, NULL);
        pageentries[11] = CreateWindowA("STATIC",
            ":",
            WS_VISIBLE | WS_CHILD,
            306, 360, 6, 25,
            iphwnd,
            NULL, NULL, NULL
        );
        pageentries[12] = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), TEXT(""),
            WS_CHILD | WS_VISIBLE,
            312, 360, 46, 25,
            iphwnd, NULL, NULL, NULL);
        pageentries[13] = CreateWindowA("STATIC",
            ":",
            WS_VISIBLE | WS_CHILD,
            358, 360, 6, 25,
            iphwnd,
            NULL, NULL, NULL
        );
        pageentries[14] = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), TEXT(""),
            WS_CHILD | WS_VISIBLE,
            364, 360, 46, 25,
            iphwnd, NULL, NULL, NULL);
            */

        pageentries[9] = CreateWindowA("STATIC",
            " Delay or DownTime\n Start Date Time",
            WS_VISIBLE | WS_CHILD,
            450, 60, 150, 34,
            iphwnd,
            NULL, NULL, NULL
        );


        pageentries[10] = CreateWindowW(L"SysDateTimePick32", NULL,

            WS_BORDER | WS_VISIBLE | WS_CHILD | WS_TABSTOP,

            450, 114, 150, 30, iphwnd, NULL, NULL, NULL);
        pageentries[11] = CreateWindowW(L"SysDateTimePick32", NULL,

            WS_BORDER | WS_VISIBLE | WS_CHILD | WS_TABSTOP | DTS_TIMEFORMAT,

            450, 148, 150, 30, iphwnd, NULL, NULL, NULL);

        pageentries[12] = CreateWindowA("STATIC",
            " Delay or DownTime\n Stop Date Time",
            WS_VISIBLE | WS_CHILD,
            450, 182, 150, 34,
            iphwnd,
            NULL, NULL, NULL
        );


        pageentries[13] = CreateWindowW(L"SysDateTimePick32", NULL,

            WS_BORDER | WS_VISIBLE | WS_CHILD | WS_TABSTOP,

            450, 220, 150, 30, iphwnd, NULL, NULL, NULL);
        pageentries[14] = CreateWindowW(L"SysDateTimePick32", NULL,

            WS_BORDER | WS_VISIBLE | WS_CHILD | WS_TABSTOP | DTS_TIMEFORMAT,

            450, 254, 150, 30, iphwnd, NULL, NULL, NULL);


        pageentries[15] = CreateWindowA("STATIC",
            "Description (fault/mainenance)",
            WS_VISIBLE | WS_CHILD ,
            640, 60, 150, 34,
            iphwnd,
            NULL, NULL, NULL
        );

        pageentries[16] = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), TEXT(""),
            WS_CHILD | WS_VISIBLE | WS_VSCROLL |
            ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL, 
            640, 98, 150, 100,
            iphwnd, NULL, NULL, NULL);

        //ShowWindow(pageentries[15], SW_HIDE);
        //ShowWindow(pageentries[16], SW_HIDE);
        pageentries[23] = CreateWindowA("STATIC",
            "Corrective Action Taken",
            WS_VISIBLE | WS_CHILD,
            640, 203, 150, 30,
            iphwnd,
            NULL, NULL, NULL
        );

        pageentries[24] = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), TEXT(""),
            WS_CHILD | WS_VISIBLE | WS_VSCROLL |
            ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL,
            640, 238, 150, 100,
            iphwnd, NULL, NULL, NULL);


        pageentries[17] = CreateWindowA("STATIC",
            "Process (CLIENT SCOPE)",
            WS_VISIBLE | WS_CHILD,
            830, 60, 150, 34,
            iphwnd,
            NULL, NULL, NULL
        );

        pageentries[18] = CreateWindowA("ComboBox", "",
            CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | WS_VSCROLL | CBS_AUTOHSCROLL |
            ES_LEFT | WS_HSCROLL,
            830, 99, 150, 200, iphwnd, (HMENU)CMBOX4, NULL,
            NULL);


        pageentries[19] = CreateWindowA("STATIC",
            "Effect on Process (Individual process stop / Wind volume reduction / NA)",
            WS_VISIBLE | WS_CHILD,
            830, 129, 150, 68,
            iphwnd,
            NULL, NULL, NULL
        );

        pageentries[20] = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), TEXT(""),
            WS_CHILD | WS_VISIBLE | WS_VSCROLL |
            ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL,
            830, 202, 150, 100,
            iphwnd, NULL, NULL, NULL);

        pageentries[21] = CreateWindowA("STATIC",
            "Attended By:",
            WS_VISIBLE | WS_CHILD,
            40, 265 , 150, 25,
            iphwnd,
            NULL, NULL, NULL
        );

        pageentries[22] = CreateWindowA("ComboBox", "",
            CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | WS_VSCROLL | CBS_AUTOHSCROLL |
            ES_LEFT | WS_HSCROLL,
            40, 295, 150, 200, iphwnd, (HMENU)CMBOX5, NULL,
            NULL);

        

        pageentries[25] = CreateWindowA(
            "BUTTON",  // Predefined class; Unicode assumed
            "SUBMIT",      // Button text
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
            690,         // x position
            395,         // y position
            100,        // Button width
            30,        // Button height
            iphwnd,     // Parent window
            (HMENU)SUBMITINPUT,       // No menu.
            (HINSTANCE)GetWindowLong(iphwnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.

        pageentries[26] = CreateWindowA(
            "BUTTON",  // Predefined class; Unicode assumed
            "CLEAR",      // Button text
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
            560,         // x position
            395,         // y position
            100,        // Button width
            30,        // Button height
            iphwnd,     // Parent window
            (HMENU)SUBMITCLEAR,       // No menu.
            (HINSTANCE)GetWindowLong(iphwnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.

        pageentries[29] = CreateWindowA("STATIC",
            "",
            WS_VISIBLE | WS_CHILD,
            40, 430, 200, 25,
            iphwnd,
            NULL, NULL, NULL
        );

        pageentries[30] = CreateWindowA("STATIC",
            "Responsibility:",
            WS_VISIBLE | WS_CHILD,
            830, 307, 150, 25,
            iphwnd,
            NULL, NULL, NULL
        );

        pageentries[31] = CreateWindowA("ComboBox", "",
            CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | WS_VSCROLL | CBS_AUTOHSCROLL |
            ES_LEFT | WS_HSCROLL,
            830, 337, 150, 200, iphwnd, (HMENU)CMBOX7, NULL,
            NULL);

        pageentries[32] = CreateWindowA("STATIC",
            "ID :",
            WS_VISIBLE | WS_CHILD,
            490, 20, 30, 30,
            iphwnd,
            NULL, NULL, NULL
        );

        pageentries[33] = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), TEXT(""),
            WS_CHILD | WS_VISIBLE,
            520, 20, 75, 30,
            iphwnd, NULL, NULL, NULL);

        pageentries[34] = CreateWindowA(
            "BUTTON",  // Predefined class; Unicode assumed
            "EDIT",      // Button text
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
            600,         // x position
            20,         // y position
            75,        // Button width
            30,        // Button height
            iphwnd,     // Parent window
            (HMENU)EDITDATA,       // No menu.
            (HINSTANCE)GetWindowLong(iphwnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.

        pageentries[36] = CreateWindowA(
            "BUTTON",  // Predefined class; Unicode assumed
            "DELETE",      // Button text
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
            680,         // x position
            20,         // y position
            75,        // Button width
            30,        // Button height
            iphwnd,     // Parent window
            (HMENU)DELETEDATA,       // No menu.
            (HINSTANCE)GetWindowLong(iphwnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.


        iplogger(std::string("Added All the Page entries"));

        equipModel em;
        em.OpenConnection();
        std::vector<std::string> equiplist = em.getallequipnt();
        em.closeConnection();
        iplogger(std::string(" - got equipment list"));
        TCHAR A[16];

        memset(&A, 0, sizeof(A));
        for (auto it = equiplist.begin(); it != equiplist.end(); ++it) {

            _tcscpy_s(A, CA2T((*it).c_str()));

            // Add string to combobox.
            SendMessage(pageentries[3], (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)A);
        }

        // Send the CB_SETCURSEL message to display an initial item 
        //  in the selection field  
        SendMessage(pageentries[3], CB_SETCURSEL, (WPARAM)0, (LPARAM)0);

        int ItemIndex1 = SendMessage(pageentries[3], (UINT)CB_GETCURSEL,
            (WPARAM)0, (LPARAM)0);

        (TCHAR)SendMessage(pageentries[3], (UINT)CB_GETLBTEXT,
            (WPARAM)ItemIndex1, (LPARAM)EquipNT);

        iplogger(std::string("filled combobox 3 with equipment list"));

        TCHAR NoRunReason[4][15] =
        {
            TEXT("fault"), TEXT("maintenance"), TEXT("Greasing"), TEXT("Main Equip Run")
        };

        TCHAR B[16];
        int  l = 0;

        memset(&B, 0, sizeof(B));
        for (l = 0; l <= 3; l += 1)
        {
            wcscpy_s(B, sizeof(B) / sizeof(TCHAR), (TCHAR*)NoRunReason[l]);

            // Add string to combobox.
            SendMessage(pageentries[6], (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)B);
        }

        // Send the CB_SETCURSEL message to display an initial item 
        //  in the selection field  
        SendMessage(pageentries[6], CB_SETCURSEL, (WPARAM)0, (LPARAM)0);

        int ItemIndex2 = SendMessage(pageentries[6], (UINT)CB_GETCURSEL,
            (WPARAM)0, (LPARAM)0);

        (TCHAR)SendMessage(pageentries[6], (UINT)CB_GETLBTEXT,
            (WPARAM)ItemIndex2, (LPARAM)NoRR);

        iplogger(std::string("filled no run reason in combobox 6"));
        TCHAR TimeDesc[2][15] =
        {
            TEXT("delay"), TEXT("downtime")
        };

        TCHAR C[16];
        int  m = 0;

        memset(&C, 0, sizeof(C));
        for (m = 0; m <= 1; m += 1)
        {
            wcscpy_s(C, sizeof(C) / sizeof(TCHAR), (TCHAR*)TimeDesc[m]);

            // Add string to combobox.
            SendMessage(pageentries[8], (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)C);
        }

        // Send the CB_SETCURSEL message to display an initial item 
        //  in the selection field  
        SendMessage(pageentries[8], CB_SETCURSEL, (WPARAM)0, (LPARAM)0);

        int ItemIndex3 = SendMessage(pageentries[8], (UINT)CB_GETCURSEL,
            (WPARAM)0, (LPARAM)0);

        (TCHAR)SendMessage(pageentries[8], (UINT)CB_GETLBTEXT,
            (WPARAM)ItemIndex3, (LPARAM)TimeDescSelect);

        iplogger(std::string("filled time description"));
        faultModel fm;
        fm.OpenConnection();
        std::vector<faultobj> faultlist = fm.getallfaults();
        fm.closeConnection();
        iplogger(std::string("got fault model data from db"));
        TCHAR F[16];
        memset(&F, 0, sizeof(F));

        for (auto it = faultlist.begin(); it != faultlist.end(); ++it) {
            _tcscpy_s(F, CA2T((it->faulttype).c_str()));
            SendMessage(pageentries[28], (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)F);
        }
        SendMessage(pageentries[28], CB_SETCURSEL, (WPARAM)0, (LPARAM)0);

        iplogger(std::string("filled fault model combo box"));
        processModel pm;
        pm.OpenConnection();
        std::vector<processobj> processlist = pm.getallprocess();
        pm.closeConnection();

        iplogger(std::string("got process model data from db"));
        TCHAR D[16];
        int  n = 0;

        memset(&D, 0, sizeof(D));
        for (auto it = processlist.begin(); it != processlist.end(); ++it) {

            //            ft = ft + std::to_string(it->id) + "\t" + it->processname + "\n";
            _tcscpy_s(D, CA2T((it->processname).c_str()));

            //          wcscpy_s(D, sizeof(D) / sizeof(TCHAR), (TCHAR*)Process[n]);

                      // Add string to combobox.
            SendMessage(pageentries[18], (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)D);
        }

        // Send the CB_SETCURSEL message to display an initial item 
        //  in the selection field  
        SendMessage(pageentries[18], CB_SETCURSEL, (WPARAM)0, (LPARAM)0);

        int ItemIndex4 = SendMessage(pageentries[18], (UINT)CB_GETCURSEL,
            (WPARAM)0, (LPARAM)0);

        (TCHAR)SendMessage(pageentries[18], (UINT)CB_GETLBTEXT,
            (WPARAM)ItemIndex4, (LPARAM)ProcessScope);
        iplogger(std::string("filled pm in combo box 18"));
        
        employeeModel empm;
        empm.OpenConnection();
        std::vector<empobjects> emplist = empm.getallemployees();
        empm.closeConnection();
        iplogger(std::string("got employee model from db"));
        TCHAR E[16];
        int  o = 0;

        memset(&E, 0, sizeof(E));
        for (auto it = emplist.begin(); it != emplist.end(); ++it) {
            //ft = ft + std::to_string(it->id) + "\t" + it->empnum + "\t" + it->empname + "\n";
            //wcscpy_s(E, sizeof(E) / sizeof(TCHAR), (TCHAR*)Attendees[o]);
            _tcscpy_s(E, CA2T((it->empname).c_str()));
            // Add string to combobox.
            SendMessage(pageentries[22], (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)E);
        }

        // Send the CB_SETCURSEL message to display an initial item 
        //  in the selection field  
        SendMessage(pageentries[22], CB_SETCURSEL, (WPARAM)0, (LPARAM)0);

        
        int ItemIndex5 = SendMessage(pageentries[22], (UINT)CB_GETCURSEL,
            (WPARAM)0, (LPARAM)0);

        (TCHAR)SendMessage(pageentries[22], (UINT)CB_GETLBTEXT,
            (WPARAM)ItemIndex5, (LPARAM)AttendeeName);
        iplogger(std::string("filled employee mode data in cb"));
        int ItemIndex6 = SendMessage(pageentries[28], (UINT)CB_GETCURSEL,
            (WPARAM)0, (LPARAM)0);

        (TCHAR)SendMessage(pageentries[28], (UINT)CB_GETLBTEXT,
            (WPARAM)ItemIndex6, (LPARAM)FaultType);

        respModel rpm;
        rpm.OpenConnection();
        std::vector<respData> resplist = rpm.getallresp();
        rpm.closeConnection();
        iplogger(std::string("got responsibility model"));
        TCHAR R[16];
        int  p = 0;

        memset(&R, 0, sizeof(R));
        for (auto it = resplist.begin(); it != resplist.end(); ++it) {
            //ft = ft + std::to_string(it->id) + "\t" + it->empnum + "\t" + it->empname + "\n";
            //wcscpy_s(E, sizeof(E) / sizeof(TCHAR), (TCHAR*)Attendees[o]);
            _tcscpy_s(R, CA2T((it->respname).c_str()));
            // Add string to combobox.
            SendMessage(pageentries[31], (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)R);
        }

        // Send the CB_SETCURSEL message to display an initial item 
        //  in the selection field  
        SendMessage(pageentries[31], CB_SETCURSEL, (WPARAM)0, (LPARAM)0);


        int ItemIndex7 = SendMessage(pageentries[31], (UINT)CB_GETCURSEL,
            (WPARAM)0, (LPARAM)0);

        (TCHAR)SendMessage(pageentries[31], (UINT)CB_GETLBTEXT,
            (WPARAM)ItemIndex7, (LPARAM)Responsibility);

        iplogger(std::string("filled resp model"));
        iplogger(std::string("starting to fill recent entries"));
        fillallDataentries();
}

void inputpage::HandleNotifyEvent(WPARAM &wParam, LPARAM &lParam){
    switch (((LPNMHDR)lParam)->code) {
        case MCN_SELECT:
        {
            SYSTEMTIME time;
            wchar_t s_buf[500];
            ZeroMemory(&time, sizeof(SYSTEMTIME));

            SendMessageW(pageentries[2], MCM_GETCURSEL, 0, (LPARAM)&time);
            wsprintf(s_buf, L"%d-%d-%d", time.wYear, time.wMonth, time.wDay);
            std::wstring wsbuf(s_buf);
            std::string strsbuf(wsbuf.begin(), wsbuf.end());
            SetWindowTextA(pageentries[1], (strsbuf).c_str());
          //  MessageBoxW(iphwnd, s_buf, s_buf, MB_OK);
        }
            break;
        default:
            break;
    }
}

void inputpage::HandleEvent(WPARAM wParam, LPARAM lParam) {
    switch (LOWORD(wParam))
    {
        case CMBOX1:
        {
            int ItemIndex = SendMessage(pageentries[3], (UINT)CB_GETCURSEL,
                (WPARAM)0, (LPARAM)0);
            
            (TCHAR)SendMessage(pageentries[3], (UINT)CB_GETLBTEXT,
                (WPARAM)ItemIndex, (LPARAM)EquipNT);
            ///MessageBox(iphwnd, (LPCWSTR)ListItem, TEXT("Item Selected"), MB_OK);
        }
        break;
        case CMBOX2:
        {
            int ItemIndex = SendMessage(pageentries[6], (UINT)CB_GETCURSEL,
                (WPARAM)0, (LPARAM)0);

            (TCHAR)SendMessage(pageentries[6], (UINT)CB_GETLBTEXT,
                (WPARAM)ItemIndex, (LPARAM)NoRR);

            TCHAR f[] = TEXT("fault");
            TCHAR m[] = TEXT("maintenance");

            if (wcscmp(NoRR, f) == 0 || wcscmp(NoRR, m) == 0) {
                ShowWindow(pageentries[15], SW_SHOW);
                ShowWindow(pageentries[16], SW_SHOW);
                SetWindowTextA(pageentries[16], "");
            }
            else {
                ShowWindow(pageentries[15], SW_HIDE);
                ShowWindow(pageentries[16], SW_HIDE);
                SetWindowTextA(pageentries[16],"");
            }
        }
        break;
        case CMBOX3:
        {
            int ItemIndex = SendMessage(pageentries[8], (UINT)CB_GETCURSEL,
                (WPARAM)0, (LPARAM)0);

            (TCHAR)SendMessage(pageentries[8], (UINT)CB_GETLBTEXT,
                (WPARAM)ItemIndex, (LPARAM)TimeDescSelect);
        }
        break;
        case CMBOX4:
        {
            int ItemIndex = SendMessage(pageentries[18], (UINT)CB_GETCURSEL,
                (WPARAM)0, (LPARAM)0);

            (TCHAR)SendMessage(pageentries[18], (UINT)CB_GETLBTEXT,
                (WPARAM)ItemIndex, (LPARAM)ProcessScope);

        }
        break;
        case CMBOX5:
        {
            int ItemIndex = SendMessage(pageentries[22], (UINT)CB_GETCURSEL,
                (WPARAM)0, (LPARAM)0);

            (TCHAR)SendMessage(pageentries[22], (UINT)CB_GETLBTEXT,
                (WPARAM)ItemIndex, (LPARAM)AttendeeName);

        }
        break;
        case CMBOX6:
        {
            int ItemIndex = SendMessage(pageentries[28], (UINT)CB_GETCURSEL,
                (WPARAM)0, (LPARAM)0);

            (TCHAR)SendMessage(pageentries[28], (UINT)CB_GETLBTEXT,
                (WPARAM)ItemIndex, (LPARAM)FaultType);

        }
        break;
        case CMBOX7:
        {
            int ItemIndex = SendMessage(pageentries[31], (UINT)CB_GETCURSEL,
                (WPARAM)0, (LPARAM)0);

            (TCHAR)SendMessage(pageentries[31], (UINT)CB_GETLBTEXT,
                (WPARAM)ItemIndex, (LPARAM)Responsibility);

        }
        break;
        case IDB_CHECKBOX:
        {
            if (SendDlgItemMessage(iphwnd, IDB_CHECKBOX, BM_GETCHECK, 0, 0))
            { 
               // MessageBox(NULL, L"Checkbox Selected", L"Success", MB_OK | MB_ICONINFORMATION);
                equipdesc = true;
            }
            else
            { 
                //MessageBox(NULL, L"Checkbox Unselected",L"Success", MB_OK | MB_ICONINFORMATION);
                equipdesc = false;
            }
        }
        break;
        case SUBMITINPUT:
        {

            
                dataModel dm;
                dm.OpenConnection();
                dataobject dao;
                //dao.date =
                int datelen = GetWindowTextLengthW(pageentries[1]) + 1;
                if (datelen > 1) {
                    wchar_t* dateval = new wchar_t[datelen];
                    GetWindowTextW(pageentries[1], dateval, datelen);

                    std::wstring wsdateval(dateval);
                    std::string strdateval(wsdateval.begin(), wsdateval.end());
                    dao.date = strdateval;
                    //                MessageBox(iphwnd, dateval, L"", MB_OK);
                }
                else {
                    SetWindowTextA(pageentries[29], "Please fill Date!!");
                    break;
                    //return;               

                }

                //  int eqlen = GetWindowTextLengthW(pageentries[1]) + 1;
                std::wstring wsequipnt(EquipNT);
                std::string strequipnt(wsequipnt.begin(), wsequipnt.end());
                dao.equipnt = strequipnt;

                if (equipdesc) {
                    equipModel em;
                    em.OpenConnection();
                    dao.equipdes = em.getDescription(dao.equipnt);
                    em.closeConnection();
                }

                std::wstring wsnorr(NoRR);
                std::string strnorr(wsnorr.begin(), wsnorr.end());
                dao.norunreason = strnorr;

                std::wstring wstimedetail(TimeDescSelect);
                std::string strtimedetail(wstimedetail.begin(), wstimedetail.end());
                dao.timedesc = strtimedetail;



                
                CDateTime sttime;
                int tdhhlen = GetWindowTextLengthW(pageentries[10])+1;
                if (tdhhlen > 1) {
                    wchar_t* tdhhval = new wchar_t[tdhhlen];
                    GetWindowTextW(pageentries[10], tdhhval, tdhhlen);

                    std::wstring wstdhhval(tdhhval);
                    std::string strtdhhval(wstdhhval.begin(), wstdhhval.end());
                    
                    std::string delimiter = "/";
                    size_t pos = 0;
                    std::string token;
                    pos = strtdhhval.find(delimiter);
                    token = strtdhhval.substr(0, pos);
                    //            std::cout << token << std::endl;
                    sttime.month = stoi(token);
                    strtdhhval.erase(0, pos + delimiter.length());

                    pos = strtdhhval.find(delimiter);
                    token = strtdhhval.substr(0, pos);
                    sttime.day = stoi(token);
                    std::cout << token << std::endl;
                    strtdhhval.erase(0, pos + delimiter.length());

                    sttime.year = stoi(strtdhhval);

                             //       MessageBox(iphwnd, tdhhval, L"", MB_OK);
                }
            
                int tdholen = GetWindowTextLengthW(pageentries[11]) + 1;
                if (tdholen > 1) {
                    wchar_t* tdhoval = new wchar_t[tdholen];
                    GetWindowTextW(pageentries[11], tdhoval, tdholen);
                    
                    std::wstring wstdhoval(tdhoval);
                    std::string strtdhoval(wstdhoval.begin(), wstdhoval.end());

                    std::string delimiter = " ";
                    size_t pos = 0;
                    std::string token;
                    pos = strtdhoval.find(delimiter);
                    token = strtdhoval.substr(0, pos);
                    //            std::cout << token << std::endl;
                    std::string ctime = token;
                    
                    strtdhoval.erase(0, pos + delimiter.length());

                    std::string meri = strtdhoval;

                    std::string delim = ":";
                    pos = 0;
                    pos = ctime.find(delim);
                    token = ctime.substr(0, pos);

                    sttime.hour = stoi(token);
                    if (meri.compare("PM")) {
                        if (sttime.hour == 12) {
                            sttime.hour = 0;
                        }
                    }
                    if (meri.compare("AM")) {
                        if (sttime.hour == 12) {
                            sttime.hour = 12;
                        }
                        else {
                            sttime.hour = sttime.hour + 12;
                        }
                    }
                    ctime.erase(0, pos + delim.length());

                    pos = ctime.find(delim);
                    token = ctime.substr(0, pos);
                    sttime.minute = stoi(token);
                    ctime.erase(0, pos + delimiter.length());

                    sttime.second = stoi(ctime);



                           //MessageBox(iphwnd, tdhoval, L"", MB_OK);
                }

                dao.starttime = sttime;

                CDateTime sptime;
                
                {
                int tdhhlen = GetWindowTextLengthW(pageentries[13]) + 1;
                if (tdhhlen > 1) {
                    wchar_t* tdhhval = new wchar_t[tdhhlen];
                    GetWindowTextW(pageentries[13], tdhhval, tdhhlen);

                    std::wstring wstdhhval(tdhhval);
                    std::string strtdhhval(wstdhhval.begin(), wstdhhval.end());

                    std::string delimiter = "/";
                    size_t pos = 0;
                    std::string token;
                    pos = strtdhhval.find(delimiter);
                    token = strtdhhval.substr(0, pos);
                    //            std::cout << token << std::endl;
                    sptime.month = stoi(token);
                    strtdhhval.erase(0, pos + delimiter.length());

                    pos = strtdhhval.find(delimiter);
                    token = strtdhhval.substr(0, pos);
                    sptime.day = stoi(token);
                    std::cout << token << std::endl;
                    strtdhhval.erase(0, pos + delimiter.length());

                    sptime.year = stoi(strtdhhval);

                    //       MessageBox(iphwnd, tdhhval, L"", MB_OK);
                }

                int tdholen = GetWindowTextLengthW(pageentries[14]) + 1;
                if (tdholen > 1) {
                    wchar_t* tdhoval = new wchar_t[tdholen];
                    GetWindowTextW(pageentries[14], tdhoval, tdholen);

                    std::wstring wstdhoval(tdhoval);
                    std::string strtdhoval(wstdhoval.begin(), wstdhoval.end());

                    std::string delimiter = " ";
                    size_t pos = 0;
                    std::string token;
                    pos = strtdhoval.find(delimiter);
                    token = strtdhoval.substr(0, pos);
                    //            std::cout << token << std::endl;
                    std::string ctime = token;

                    strtdhoval.erase(0, pos + delimiter.length());

                    std::string meri = strtdhoval;

                    std::string delim = ":";
                    pos = 0;
                    pos = ctime.find(delim);
                    token = ctime.substr(0, pos);

                    sptime.hour = stoi(token);
                    if (meri.compare("PM")) {
                        if (sptime.hour == 12) {
                            sptime.hour = 0;
                        }
                    }
                    if (meri.compare("AM")) {
                        if (sptime.hour == 12) {
                            sptime.hour = 12;
                        }
                        else {
                            sptime.hour = sptime.hour + 12;
                        }
                    }
                    ctime.erase(0, pos + delim.length());

                    pos = ctime.find(delim);
                    token = ctime.substr(0, pos);
                    sptime.minute = stoi(token);
                    ctime.erase(0, pos + delimiter.length());

                    sptime.second = stoi(ctime);



                    //MessageBox(iphwnd, tdhoval, L"", MB_OK);
                }
                }
                dao.stoptime = sptime;
                /*
                int tdmmlen = GetWindowTextLengthW(pageentries[12]) + 1;
                if (tdmmlen > 1) {
                    wchar_t* tdmmval = new wchar_t[tdmmlen];
                    GetWindowTextW(pageentries[12], tdmmval, tdmmlen);

                    std::wstring wstdmmval(tdmmval);
                    std::string strtdmmval(wstdmmval.begin(), wstdmmval.end());
                    dao.timedescmm = strtdmmval;
                    //                MessageBox(iphwnd, dateval, L"", MB_OK);
                }
                else {
                    dao.timedescmm = "00";    //return;               

                }

                int tdsslen = GetWindowTextLengthW(pageentries[14]) + 1;
                if (tdsslen > 1) {
                    wchar_t* tdssval = new wchar_t[tdsslen];
                    GetWindowTextW(pageentries[14], tdssval, tdsslen);

                    std::wstring wstdssval(tdssval);
                    std::string strtdssval(wstdssval.begin(), wstdssval.end());
                    dao.timedescss = strtdssval;
                    //                MessageBox(iphwnd, dateval, L"", MB_OK);
                }
                else {
                    dao.timedescss = "00";    //return;               

                }
                */
                std::wstring wsft(FaultType);
                std::string strft(wsft.begin(), wsft.end());
                dao.faulttype = strft;

                std::wstring wsresp(Responsibility);
                std::string strresp(wsresp.begin(), wsresp.end());
                dao.responsibility = strresp;
            
                int fdlen = GetWindowTextLengthW(pageentries[16]) + 1;
                if (fdlen > 1) {
                    wchar_t* fdval = new wchar_t[fdlen];
                    GetWindowTextW(pageentries[16], fdval, fdlen);

                    std::wstring wsfdval(fdval);
                    std::string strfdval(wsfdval.begin(), wsfdval.end());
                    dao.faultdesc = strfdval;
                    //                MessageBox(iphwnd, dateval, L"", MB_OK);
                }
                else {
                    dao.faultdesc = "";
                }
            
                std::wstring wspn(ProcessScope);
                std::string strpn(wspn.begin(), wspn.end());
                dao.processname = strpn;

                int eoplen = GetWindowTextLengthW(pageentries[20]) + 1;
                if (eoplen > 1) {
                    wchar_t* eopval = new wchar_t[eoplen];
                    GetWindowTextW(pageentries[20], eopval, eoplen);

                    std::wstring wseopval(eopval);
                    std::string streopval(wseopval.begin(), wseopval.end());
                    dao.processeffect = streopval;
                    //                MessageBox(iphwnd, dateval, L"", MB_OK);
                }
                else {
                    dao.processeffect = "";
                }
            
                std::wstring wsan(AttendeeName);
                std::string stran(wsan.begin(), wsan.end());
                dao.attendeename = stran;


                int remlen = GetWindowTextLengthW(pageentries[24]) + 1;
                if (remlen > 1) {
                    wchar_t* remval = new wchar_t[remlen];
                    GetWindowTextW(pageentries[24], remval, remlen);

                    std::wstring wsremval(remval);
                    std::string strremval(wsremval.begin(), wsremval.end());
                    dao.remarks = strremval;
                    //                MessageBox(iphwnd, dateval, L"", MB_OK);
                }
                else {
                    dao.remarks = "";
                }

                if (inputpage::EditMode) {

                    int dataid = GetWindowTextLengthW(pageentries[33]) + 1;
                    if (dataid > 1) {
                        wchar_t* dataidval = new wchar_t[dataid];
                        GetWindowTextW(pageentries[33], dataidval, dataid);

                        std::wstring wsdataidval(dataidval);
                        std::string strdataidval(wsdataidval.begin(), wsdataidval.end());
                        dao.id = stoi(strdataidval);
                        //                MessageBox(iphwnd, dateval, L"", MB_OK);
                    }
                    else {
                        dm.closeConnection();
                        SetWindowTextA(pageentries[29], "Fill ID in edit mode!");
                        return;
                    }

                    if (dm.updatedata(dao)) {
                        SetWindowTextA(pageentries[29], "Updated successfully!!!");

                        auto vi = pageentries.begin();
                        vi = vi + 37;
                        for (; vi != pageentries.end(); ++vi) {
                            DestroyWindow(*vi);
                        }
                        fillallDataentries();
                    }
                    else {
                        SetWindowTextA(pageentries[29], "Some issue updating!!!");
                    }



                    inputpage::EditMode = false;
                    SendMessage(iphwnd, WM_COMMAND, MAKEWPARAM(SUBMITCLEAR, BN_CLICKED),
                        (LPARAM)iphwnd);

                }
                else {



                    if(dm.insertdata(dao)){
                        SetWindowTextA(pageentries[29], "Inserted successfully!!!");
                
                        auto vi = pageentries.begin();
                        vi = vi + 37;
                        for (;vi!=pageentries.end();++vi) {
                            DestroyWindow(*vi);
                        }
                        fillallDataentries();
                    }
                    else {
                        SetWindowTextA(pageentries[29], "Data might be already inserted!!!");
                    }
                }
                dm.closeConnection();
            
            
        }
        break;
        case SUBMITCLEAR:
        {
            //SetWindowText(pageentries[10], L"");
            //SetWindowText(pageentries[12], L"");
            //SetWindowText(pageentries[14], L"");
            SetWindowText(pageentries[16], L"");
            SetWindowText(pageentries[20], L"");
            SetWindowText(pageentries[24], L"");
            inputpage::EditMode = false;
            SetWindowText(pageentries[29], L"");
            SetWindowText(pageentries[33], L"");
            equipdesc = false;
            SendMessage(pageentries[43], BM_SETCHECK, BST_UNCHECKED, 0);

        }
        break;
        case DELETEDATA:
        {
            int ulenn = GetWindowTextLengthW(pageentries[33]) + 1;
            if (ulenn > 1) {
                wchar_t* equipnt = new wchar_t[ulenn];
                GetWindowTextW(pageentries[33], equipnt, ulenn);

                std::wstring wsequipnt(equipnt);
                std::string strequipnt(wsequipnt.begin(), wsequipnt.end());


                dataModel em;
                em.OpenConnection();
                if(em.deletedata(strequipnt)){
                    SetWindowTextA(pageentries[29], "Entry Deleted!!");
                    auto vi = pageentries.begin();
                    vi = vi + 37;
                    for (; vi != pageentries.end(); ++vi) {
                        DestroyWindow(*vi);
                    }
                    fillallDataentries();
                }
                else {
                    SetWindowTextA(pageentries[29], "Error Deleting!!");
                }
                em.closeConnection();
                

            }
            else {
                SetWindowTextA(pageentries[29], "Fill Data table id to delete");
            }

        }
        break;
        case EDITDATA:
        {
            int ulenn = GetWindowTextLengthW(pageentries[33]) + 1;
            if (ulenn > 1) {
                wchar_t* equipnt = new wchar_t[ulenn];
                GetWindowTextW(pageentries[33], equipnt, ulenn);

                std::wstring wsequipnt(equipnt);
                std::string strequipnt(wsequipnt.begin(), wsequipnt.end());


                dataModel em;
                em.OpenConnection();

                dataobject dobj = em.getOnedata(strequipnt);
                em.closeConnection();
                //date
                SetWindowTextA(pageentries[1], (dobj.date).c_str());
                //equpment
                memset(EquipNT, 0, sizeof(EquipNT));
                std::copy(dobj.equipnt.begin(), dobj.equipnt.end(), EquipNT);
                SendMessage(pageentries[3], CB_SETCURSEL, (WPARAM)0, (LPARAM)0);
                SendMessage(pageentries[3], CB_SELECTSTRING, (WPARAM)0, (LPARAM)EquipNT);

                if (dobj.equipdes.empty())
                {
                    equipdesc = false;
                    SendMessage(pageentries[35], BM_SETCHECK, BST_CHECKED, 0);
                }
                else {
                    equipdesc = true;
                    SendMessage(pageentries[35], BM_SETCHECK, BST_CHECKED, 0);
                }
                //norunreason

                memset(NoRR, 0, sizeof(NoRR));//                NoRR[256] = 0;
                std::copy(dobj.norunreason.begin(), dobj.norunreason.end(), NoRR);
                SendMessage(pageentries[6], CB_SETCURSEL, (WPARAM)0, (LPARAM)0);
                SendMessage(pageentries[6], CB_SELECTSTRING, (WPARAM)0, (LPARAM)NoRR);
                SendMessage(iphwnd, WM_COMMAND, MAKEWPARAM(CMBOX2, CBN_SELCHANGE),
                    (LPARAM)iphwnd);
                //tiem desc
                memset(TimeDescSelect, 0, sizeof(TimeDescSelect));
                std::copy(dobj.timedesc.begin(), dobj.timedesc.end(), TimeDescSelect);
                SendMessage(pageentries[8], CB_SETCURSEL, (WPARAM)0, (LPARAM)0);
                SendMessage(pageentries[8], CB_SELECTSTRING, (WPARAM)0, (LPARAM)TimeDescSelect);
                //

                //SetWindowText(pageentries[10], std::wstring(dobj.timedeschh.begin(), dobj.timedeschh.end()).c_str());
                //SetWindowText(pageentries[12], std::wstring(dobj.timedescmm.begin(), dobj.timedescmm.end()).c_str());
                //SetWindowText(pageentries[14], std::wstring(dobj.timedescss.begin(), dobj.timedescss.end()).c_str());
                std::string stdate = std::to_string(dobj.starttime.month) + "/" \
                                 + std::to_string(dobj.starttime.day) + "/" \
                                 + std::to_string(dobj.starttime.year);

//                SetWindowText(pageentries[10], std::wstring(stdate.begin(), stdate.end()).c_str());
                //OutputDebugString(std::wstring(stdate.begin(), stdate.end()).c_str());
                SYSTEMTIME st;
                st.wDay = dobj.starttime.day;
                st.wMonth = dobj.starttime.month;
                st.wYear = dobj.starttime.year;
                st.wHour = dobj.starttime.hour;
                st.wMinute = dobj.starttime.minute;
                st.wSecond = dobj.starttime.second;
                SendMessage(pageentries[10], DTM_SETSYSTEMTIME, (WPARAM)GDT_VALID, (LPARAM)&st);
                SendMessage(pageentries[11], DTM_SETSYSTEMTIME, (WPARAM)GDT_VALID, (LPARAM)&st);

                SetWindowText(pageentries[10], std::wstring(stdate.begin(), stdate.end()).c_str());

                SetWindowText(pageentries[16], std::wstring(dobj.faultdesc.begin(), dobj.faultdesc.end()).c_str());

                memset(FaultType, 0, sizeof(FaultType));
                std::copy(dobj.faulttype.begin(), dobj.faulttype.end(), FaultType);
                SendMessage(pageentries[28], CB_SETCURSEL, (WPARAM)0, (LPARAM)0);
                SendMessage(pageentries[28], CB_SELECTSTRING, (WPARAM)0, (LPARAM)FaultType);

                memset(ProcessScope, 0, sizeof(ProcessScope));
                //ProcessScope[256] = 0;
                std::copy(dobj.processname.begin(), dobj.processname.end(), ProcessScope);
                SendMessage(pageentries[18], CB_SETCURSEL, (WPARAM)0, (LPARAM)0);
                SendMessage(pageentries[18], CB_SELECTSTRING, (WPARAM)0, (LPARAM)ProcessScope);

                SetWindowText(pageentries[20], std::wstring(dobj.processeffect.begin(), dobj.processeffect.end()).c_str());

                memset(AttendeeName, 0, sizeof(AttendeeName));
                //AttendeeName[256] = 0;
                std::copy(dobj.attendeename.begin(), dobj.attendeename.end(), AttendeeName);
                SendMessage(pageentries[22], CB_SETCURSEL, (WPARAM)0, (LPARAM)0);
                SendMessage(pageentries[22], CB_SELECTSTRING, (WPARAM)0, (LPARAM)AttendeeName);

                SetWindowText(pageentries[24], std::wstring(dobj.remarks.begin(), dobj.remarks.end()).c_str());

                memset(Responsibility, 0, sizeof(Responsibility));
                //Responsibility[256] = 0;
                std::copy(dobj.responsibility.begin(), dobj.responsibility.end(), Responsibility);
                SendMessage(pageentries[31], CB_SETCURSEL, (WPARAM)0, (LPARAM)0);
                SendMessage(pageentries[31], CB_SELECTSTRING, (WPARAM)0, (LPARAM)Responsibility);



                inputpage::EditMode = true;
                SetWindowTextA(pageentries[29], "EditMode: Edit and Submit!!");

            }
            else {
                SetWindowTextA(pageentries[29], "Fill Data table id to edit");
            }
        }
        break;
        default:
            break;
    }
}
inputpage::~inputpage() {
    DestroyPage();
}

void inputpage::fillallDataentries() {
    iplogger(std::string("getting data model data"));
    dataModel dm;
    dm.OpenConnection();
    std::vector<dataobject> datalist = dm.getalldatas();
    dm.closeConnection();
    iplogger(std::string("got all data list"));
    int height = 490;
//    pageentries[30] = CreateWindow(L"MainWClass", NULL,  WS_CHILD | WS_BORDER | WS_VISIBLE, 35, 460, 1060, 350, iphwnd, NULL, NULL, NULL);
    pageentries.push_back(CreateWindowA("STATIC",
        "Note*: Only recent 5 entries will be shown below.",
        WS_VISIBLE | WS_CHILD,
        40, 460, 500, 30,
        iphwnd,
        NULL, NULL, NULL
    ));
    iplogger(std::string("started for loop for 5 entries"));
    for (auto it = datalist.begin(); it != datalist.end(); ++it) {
 
        pageentries.push_back(CreateWindowA("STATIC",
            (LPCSTR)std::to_string(it->id).c_str(),
            WS_VISIBLE | WS_CHILD,
            40, height, 20, 60,
            iphwnd,
            NULL, NULL, NULL
        ));
        iplogger(std::string("id added"));
        pageentries.push_back(CreateWindowA("STATIC",
            (LPCSTR)(it->date).c_str(),
            WS_VISIBLE | WS_CHILD,
            65, height, 75, 60,
            iphwnd,
            NULL, NULL, NULL
        ));
        iplogger(std::string("date added"));
        pageentries.push_back(CreateWindowA("STATIC",
            (LPCSTR)(it->equipnt).c_str(),
            WS_VISIBLE | WS_CHILD,
            145, height, 75, 60,
            iphwnd,
            NULL, NULL, NULL
        ));
        iplogger(std::string("equipment added"));
        pageentries.push_back(CreateWindowA("STATIC",
            (LPCSTR)(it->norunreason).c_str(),
            WS_VISIBLE | WS_CHILD,
            225, height, 75, 60,
            iphwnd,
            NULL, NULL, NULL
        ));
        iplogger(std::string("no run reason added"));
        std::string timedescnew = it->timedesc + " | "+it->timedeschh + ":" + it->timedescmm + ":" + it->timedescss;
        pageentries.push_back(CreateWindowA("STATIC",
            (LPCSTR)(timedescnew).c_str(),
            WS_VISIBLE | WS_CHILD,
            305, height, 150, 60,
            iphwnd,
            NULL, NULL, NULL
        ));
        iplogger(std::string("time descripton added"));
        pageentries.push_back(CreateWindowA("STATIC",
            (LPCSTR)(it->faulttype).c_str(),
            WS_VISIBLE | WS_CHILD,
            460, height, 100, 60,
            iphwnd,
            NULL, NULL, NULL
        ));
        iplogger(std::string("fault type added"));
        pageentries.push_back(CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"),
            std::wstring(it->faultdesc.begin(),it->faultdesc.end()).c_str(),
            WS_CHILD | WS_VISIBLE | WS_VSCROLL |
            ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,
            565, height, 150, 60,
            iphwnd,
            NULL, NULL, NULL
        ));
        iplogger(std::string("fault description added"));
        pageentries.push_back(CreateWindowA("STATIC",
            (LPCSTR)(it->processname).c_str(),
            WS_VISIBLE | WS_CHILD,
            720, height, 75, 60,
            iphwnd,
            NULL, NULL, NULL
        ));
        iplogger(std::string("processname added"));
        pageentries.push_back(CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"),
            std::wstring(it->processeffect.begin(),it->processeffect.end()).c_str(),
            WS_CHILD | WS_VISIBLE | WS_VSCROLL |
            ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,
            800, height, 150, 60,
            iphwnd,
            NULL, NULL, NULL
        ));
        iplogger(std::string("process effect added"));
        pageentries.push_back(CreateWindowA("STATIC",
            (LPCSTR)(it->attendeename).c_str(),
            WS_VISIBLE | WS_CHILD,
            955, height, 75, 60,
            iphwnd,
            NULL, NULL, NULL
        ));
        iplogger(std::string("attendeename added"));
        pageentries.push_back(
            CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), std::wstring(it->remarks.begin(), it->remarks.end()).c_str(),
                WS_CHILD | WS_VISIBLE | WS_VSCROLL |
                ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,
            1035, height, 150, 60,
            iphwnd,
            NULL, NULL, NULL
        ));
        iplogger(std::string("remarks added"));
        pageentries.push_back(CreateWindowA("STATIC",
            (LPCSTR)(it->responsibility).c_str(),
            WS_VISIBLE | WS_CHILD,
            1190, height, 100, 60,
            iphwnd,
            NULL, NULL, NULL
        ));
        iplogger(std::string("responsibility added"));
        height = height +65;

    
    }
    iplogger(std::string("for loop completed filling"));
 
}

bool inputpage::EditMode = false;