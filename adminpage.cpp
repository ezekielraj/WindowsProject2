#include "adminpage.h"
#include "equipModel.h"
#include "employeeModel.h"
#include "processModel.h"
#include "faultModel.h"
#include "respModel.h"

#define SUBMITEQUIP 5050
#define SUBMITEMP 5051
#define SUBMITPROC 5052
#define SUBMITFAULT 5053
#define SUBMITRESP 5054

#define DELETEEQUIP 5055
#define DELETEEMP 5056
#define DELETEPROC 5057
#define DELETEFAULT 5058
#define DELETERESP 5059

#define EDITEQUIP 5060
#define EDITEMP 5061
bool adminpage::eqeditmode = false;
bool adminpage::emeditmode = false;

adminpage::adminpage(HWND &hwnd) : pages(50) {
    aphwnd = hwnd;

}

adminpage::~adminpage() {
    DestroyPage();
}

void adminpage::CreatePage() {
    std::cout << "creating adminpage" << std::endl;
    pageentries[0] = CreateWindowA("STATIC",
        "ADMIN UPDATES",
        WS_VISIBLE | WS_CHILD,
        20, 20, 300, 25,
        aphwnd,
        NULL, NULL, NULL
    );
    pageentries[1] = CreateWindowA("STATIC",
        "Equipment Name/Tag :",
        WS_VISIBLE | WS_CHILD,
        40, 60, 150, 25,
        aphwnd,
        NULL, NULL, NULL
    );

    pageentries[2] = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), TEXT(""),
        WS_CHILD | WS_VISIBLE,
        40, 90, 150, 25,
        aphwnd, NULL, NULL, NULL);

    pageentries[43] = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), TEXT(""),
        WS_CHILD | WS_VISIBLE | WS_VSCROLL |
        ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL,
        40, 120, 150, 100,
        aphwnd, NULL, NULL, NULL);

    pageentries[3] = CreateWindowA(
        "BUTTON",  // Predefined class; Unicode assumed
        "SUBMIT",      // Button text
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
        40,         // x position
        225,         // y position
        100,        // Button width
        30,        // Button height
        aphwnd,     // Parent window
        (HMENU)SUBMITEQUIP,       // No menu.
        (HINSTANCE)GetWindowLong(aphwnd, GWLP_HINSTANCE),
        NULL);      // Pointer not needed.
    
    pageentries[30] = CreateWindowA("STATIC",
        "ID :",
        WS_VISIBLE | WS_CHILD,
        40, 260, 30, 30,
        aphwnd,
        NULL, NULL, NULL
    );

    pageentries[28] = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), TEXT(""),
            WS_CHILD | WS_VISIBLE,
            70, 260,40, 30,
            aphwnd, NULL, NULL, NULL);

    pageentries[44] = CreateWindowA(
        "BUTTON",  // Predefined class; Unicode assumed
        "EDIT",      // Button text
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
        115,         // x position
        260,         // y position
        45,        // Button width
        30,        // Button height
        aphwnd,     // Parent window
        (HMENU)EDITEQUIP,       // No menu.
        (HINSTANCE)GetWindowLong(aphwnd, GWLP_HINSTANCE),
        NULL);      // Pointer not needed.

    pageentries[29] = CreateWindowA(
        "BUTTON",  // Predefined class; Unicode assumed
        "DELETE",      // Button text
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
        165,         // x position
        260,         // y position
        70,        // Button width
        30,        // Button height
        aphwnd,     // Parent window
        (HMENU)DELETEEQUIP,       // No menu.
        (HINSTANCE)GetWindowLong(aphwnd, GWLP_HINSTANCE),
        NULL);      // Pointer not needed.
    
    pageentries[4] = CreateWindowA("STATIC",
        "",
        WS_VISIBLE | WS_CHILD,
        40, 295, 200, 30,
        aphwnd,
        NULL, NULL, NULL
    );
    pageentries[5] = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), TEXT(""),
        WS_CHILD | WS_VISIBLE | WS_VSCROLL |
        ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,
        40, 335, 200, 300,
        aphwnd, NULL, NULL, NULL);
        /*CreateWindowA("STATIC",
        "",
        WS_VISIBLE | WS_CHILD | WS_VSCROLL |
        ES_LEFT | ES_AUTOVSCROLL,
        40, 250, 200, 30,
        aphwnd,
        NULL, NULL, NULL
    );*/

    fillEquipEntries();

    pageentries[6] = CreateWindowA("STATIC",
        "Employee Number :",
        WS_VISIBLE | WS_CHILD,
        280, 60, 150, 25,
        aphwnd,
        NULL, NULL, NULL
    );
    pageentries[7] = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), TEXT(""),
        WS_CHILD | WS_VISIBLE,
        280, 90, 150, 25,
        aphwnd, NULL, NULL, NULL);

    pageentries[8] = CreateWindowA("STATIC",
        "Employee Name :",
        WS_VISIBLE | WS_CHILD,
        280, 120, 150, 25,
        aphwnd,
        NULL, NULL, NULL
    );
    pageentries[9] = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), TEXT(""),
        WS_CHILD | WS_VISIBLE,
        280, 150, 150, 25,
        aphwnd, NULL, NULL, NULL);

    pageentries[45] = CreateWindowA("STATIC",
        "Password :",
        WS_VISIBLE | WS_CHILD,
        280, 180, 150, 25,
        aphwnd,
        NULL, NULL, NULL
    );

    pageentries[46] = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), TEXT(""),
        WS_CHILD | WS_VISIBLE,
        280, 210, 150, 25,
        aphwnd, NULL, NULL, NULL);

    pageentries[10] = CreateWindowA(
        "BUTTON",  // Predefined class; Unicode assumed
        "SUBMIT",      // Button text
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
        280,         // x position
        250,         // y position
        100,        // Button width
        30,        // Button height
        aphwnd,     // Parent window
        (HMENU)SUBMITEMP,       // No menu.
        (HINSTANCE)GetWindowLong(aphwnd, GWLP_HINSTANCE),
        NULL);      // Pointer not needed.

    pageentries[31] = CreateWindowA("STATIC",
        "ID :",
        WS_VISIBLE | WS_CHILD,
        280, 290, 30, 30,
        aphwnd,
        NULL, NULL, NULL
    );

    pageentries[32] = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), TEXT(""),
        WS_CHILD | WS_VISIBLE,
        310, 290, 40, 30,
        aphwnd, NULL, NULL, NULL);
    
    pageentries[47] = CreateWindowA(
        "BUTTON",  // Predefined class; Unicode assumed
        "EDIT",      // Button text
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
        355,         // x position
        290,         // y position
        45,        // Button width
        30,        // Button height
        aphwnd,     // Parent window
        (HMENU)EDITEMP,       // No menu.
        (HINSTANCE)GetWindowLong(aphwnd, GWLP_HINSTANCE),
        NULL);      // Pointer not needed.

    pageentries[33] = CreateWindowA(
        "BUTTON",  // Predefined class; Unicode assumed
        "DELETE",      // Button text
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
        405,         // x position
        290,         // y position
        70,        // Button width
        30,        // Button height
        aphwnd,     // Parent window
        (HMENU)DELETEEMP,       // No menu.
        (HINSTANCE)GetWindowLong(aphwnd, GWLP_HINSTANCE),
        NULL);      // Pointer not needed.

    pageentries[11] = CreateWindowA("STATIC",
        "",
        WS_VISIBLE | WS_CHILD,
        280, 330, 200, 30,
        aphwnd,
        NULL, NULL, NULL
    );
    pageentries[12] = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), TEXT(""),
        WS_CHILD | WS_VISIBLE | WS_VSCROLL |
        ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,
        280, 370, 200, 244,
        aphwnd,
        NULL, NULL, NULL
    );

    fillEmployeeEntries();

    pageentries[13] = CreateWindowA("STATIC",
        "Process Name :",
        WS_VISIBLE | WS_CHILD,
        520, 60, 150, 25,
        aphwnd,
        NULL, NULL, NULL
    );
    pageentries[14] = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), TEXT(""),
        WS_CHILD | WS_VISIBLE,
        520, 90, 150, 25,
        aphwnd, NULL, NULL, NULL);

    pageentries[15] = CreateWindowA(
        "BUTTON",  // Predefined class; Unicode assumed
        "SUBMIT",      // Button text
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
        520,         // x position
        120,         // y position
        100,        // Button width
        30,        // Button height
        aphwnd,     // Parent window
        (HMENU)SUBMITPROC,       // No menu.
        (HINSTANCE)GetWindowLong(aphwnd, GWLP_HINSTANCE),
        NULL);      // Pointer not needed.

    pageentries[34] = CreateWindowA("STATIC",
        "ID :",
        WS_VISIBLE | WS_CHILD,
        520, 160, 30, 30,
        aphwnd,
        NULL, NULL, NULL
    );

    pageentries[35] = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), TEXT(""),
        WS_CHILD | WS_VISIBLE,
        550, 160, 75, 30,
        aphwnd, NULL, NULL, NULL);

    pageentries[36] = CreateWindowA(
        "BUTTON",  // Predefined class; Unicode assumed
        "DELETE",      // Button text
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
        630,         // x position
        160,         // y position
        75,        // Button width
        30,        // Button height
        aphwnd,     // Parent window
        (HMENU)DELETEPROC,       // No menu.
        (HINSTANCE)GetWindowLong(aphwnd, GWLP_HINSTANCE),
        NULL);      // Pointer not needed.

    pageentries[16] = CreateWindowA("STATIC",
        "",
        WS_VISIBLE | WS_CHILD,
        520, 200, 200, 30,
        aphwnd,
        NULL, NULL, NULL
    );
    pageentries[17] = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), TEXT(""),
        WS_CHILD | WS_VISIBLE | WS_VSCROLL |
        ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,
        520, 240, 200, 300,
        aphwnd,
        NULL, NULL, NULL
    );
    fillProcessEntries();

    pageentries[18] = CreateWindowA("STATIC",
        "Fault Type :",
        WS_VISIBLE | WS_CHILD,
        760, 60, 150, 25,
        aphwnd,
        NULL, NULL, NULL
    );
    pageentries[19] = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), TEXT(""),
        WS_CHILD | WS_VISIBLE,
        760, 90, 150, 25,
        aphwnd, NULL, NULL, NULL);

    pageentries[20] = CreateWindowA(
        "BUTTON",  // Predefined class; Unicode assumed
        "SUBMIT",      // Button text
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
        760,         // x position
        120,         // y position
        100,        // Button width
        30,        // Button height
        aphwnd,     // Parent window
        (HMENU)SUBMITFAULT,       // No menu.
        (HINSTANCE)GetWindowLong(aphwnd, GWLP_HINSTANCE),
        NULL);      // Pointer not needed.

    pageentries[37] = CreateWindowA("STATIC",
        "ID :",
        WS_VISIBLE | WS_CHILD,
        760, 160, 30, 30,
        aphwnd,
        NULL, NULL, NULL
    );

    pageentries[38] = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), TEXT(""),
        WS_CHILD | WS_VISIBLE,
        790, 160, 75, 30,
        aphwnd, NULL, NULL, NULL);

    pageentries[39] = CreateWindowA(
        "BUTTON",  // Predefined class; Unicode assumed
        "DELETE",      // Button text
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
        870,         // x position
        160,         // y position
        75,        // Button width
        30,        // Button height
        aphwnd,     // Parent window
        (HMENU)DELETEFAULT,       // No menu.
        (HINSTANCE)GetWindowLong(aphwnd, GWLP_HINSTANCE),
        NULL);      // Pointer not needed.


    pageentries[21] = CreateWindowA("STATIC",
        "",
        WS_VISIBLE | WS_CHILD,
        760, 200, 200, 30,
        aphwnd,
        NULL, NULL, NULL
    );
    pageentries[22] = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), TEXT(""),
        WS_CHILD | WS_VISIBLE | WS_VSCROLL |
        ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,
        760, 240, 200, 300,
        aphwnd,
        NULL, NULL, NULL
    );

    fillFaultEntries();

    pageentries[23] = CreateWindowA("STATIC",
        "Responsibility :",
        WS_VISIBLE | WS_CHILD,
        1000, 60, 150, 25,
        aphwnd,
        NULL, NULL, NULL
    );

    pageentries[24] = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), TEXT(""),
        WS_CHILD | WS_VISIBLE,
        1000, 90, 150, 25,
        aphwnd, NULL, NULL, NULL);

    pageentries[25] = CreateWindowA(
        "BUTTON",  // Predefined class; Unicode assumed
        "SUBMIT",      // Button text
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
        1000,         // x position
        120,         // y position
        100,        // Button width
        30,        // Button height
        aphwnd,     // Parent window
        (HMENU)SUBMITRESP,       // No menu.
        (HINSTANCE)GetWindowLong(aphwnd, GWLP_HINSTANCE),
        NULL);      // Pointer not needed.

    pageentries[40] = CreateWindowA("STATIC",
        "ID :",
        WS_VISIBLE | WS_CHILD,
        1000, 160, 30, 30,
        aphwnd,
        NULL, NULL, NULL
    );

    pageentries[41] = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), TEXT(""),
        WS_CHILD | WS_VISIBLE,
        1030, 160, 75, 30,
        aphwnd, NULL, NULL, NULL);

    pageentries[42] = CreateWindowA(
        "BUTTON",  // Predefined class; Unicode assumed
        "DELETE",      // Button text
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
        1110,         // x position
        160,         // y position
        75,        // Button width
        30,        // Button height
        aphwnd,     // Parent window
        (HMENU)DELETERESP,       // No menu.
        (HINSTANCE)GetWindowLong(aphwnd, GWLP_HINSTANCE),
        NULL);      // Pointer not needed.


    pageentries[26] = CreateWindowA("STATIC",
        "",
        WS_VISIBLE | WS_CHILD,
        1000, 200, 200, 30,
        aphwnd,
        NULL, NULL, NULL
    );
    pageentries[27] = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), TEXT(""),
        WS_CHILD | WS_VISIBLE | WS_VSCROLL |
        ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,
        1000, 240, 200, 300,
        aphwnd,
        NULL, NULL, NULL
    );
    fillRespEntries();

}

void adminpage::HandleNotifyEvent(WPARAM &wParam, LPARAM &lParam) { }

void adminpage::HandleEvent(WPARAM wParam, LPARAM lParam) {
    switch (LOWORD(wParam))
    {
        case SUBMITEQUIP:
            {
                int ulenn = GetWindowTextLengthW(pageentries[2]) + 1;
                int dlenn = GetWindowTextLengthW(pageentries[43]) +1;
                if (ulenn > 1) {
                    wchar_t* equipnt = new wchar_t[ulenn];
                    wchar_t* equipdes = new wchar_t[dlenn];
                    GetWindowTextW(pageentries[2], equipnt, ulenn);
                    GetWindowTextW(pageentries[43], equipdes, dlenn);

                    std::wstring wsequipnt(equipnt);
                    std::wstring wsequipdes(equipdes);
                    std::string strequipnt(wsequipnt.begin(), wsequipnt.end());
                    std::string strequipdes(wsequipdes.begin(), wsequipdes.end());


                    equipModel em;
                    em.OpenConnection();

                    if(!eqeditmode){
                        if(em.insertequipnt(strequipnt, strequipdes)){
                            SetWindowTextA(pageentries[4], "Successfully inserted!!!");
                            fillEquipEntries();
                        }
                        else {
                            SetWindowTextA(pageentries[4], "Failed!! check if already exists");
                        }
                    }
                    else {
                        int eqid = GetWindowTextLengthW(pageentries[28]) + 1;
                        if (eqid > 1) {
                            wchar_t* eqidv = new wchar_t[eqid];
                            GetWindowTextW(pageentries[28], eqidv, eqid);

                            std::wstring wseqidv(eqidv);
                            std::string streqidv(wseqidv.begin(), wseqidv.end());


                            equipData edd;
                            edd.description = strequipdes;
                            edd.equipnt = strequipnt;
                            edd.id = stoi(streqidv);

                            if (em.updateequip(edd)) {
                                SetWindowTextA(pageentries[4], "Updated successfully!!!");
                                
                            }
                            else {
                                SetWindowTextA(pageentries[4], "Failed!! ");
                            }
                            SetWindowTextA(pageentries[2], "");
                            SetWindowTextA(pageentries[43], "");
                            eqeditmode = false;

                        }
                    }
                    em.closeConnection();
                }
                else {
                    SetWindowTextA(pageentries[4], "Please fill Equipment Details!!!");
                }
            }
            break;
        case SUBMITEMP:
            {
                int enulen = GetWindowTextLengthW(pageentries[7]) + 1;
                int enalen = GetWindowTextLengthW(pageentries[9]) + 1;
                int passlen = GetWindowTextLengthW(pageentries[46]) + 1;
                if (enulen > 1 && enalen > 1 && passlen > 1) {
                    wchar_t* empnum = new wchar_t[enulen];
                    wchar_t* empname = new wchar_t[enalen];
                    wchar_t* emppass = new wchar_t[passlen];
                    
                    GetWindowTextW(pageentries[7], empnum, enulen);
                    GetWindowTextW(pageentries[9], empname, enalen);
                    GetWindowTextW(pageentries[46], emppass, passlen);

                    std::wstring wsempnum(empnum);
                    std::wstring wsempname(empname);
                    std::wstring wsemppass(emppass);

                    std::string strempnum(wsempnum.begin(), wsempnum.end());
                    std::string strempname(wsempname.begin(), wsempname.end());
                    std::string stremppass(wsemppass.begin(), wsemppass.end());

                    employeeModel empm;
                    empm.OpenConnection();

                    if(!emeditmode){
                        if (empm.insemployee(strempnum, strempname, stremppass)) {
                            SetWindowTextA(pageentries[11], "Successfully inserted!!!");
                            fillEmployeeEntries();
                        }
                        else {
                            SetWindowTextA(pageentries[11], "Failed!! check if already exists");
                        }
                    }
                    else {
                        int eqid = GetWindowTextLengthW(pageentries[32]) + 1;
                        if (eqid > 1) {
                            wchar_t* eqidv = new wchar_t[eqid];
                            GetWindowTextW(pageentries[32], eqidv, eqid);

                            std::wstring wseqidv(eqidv);
                            std::string streqidv(wseqidv.begin(), wseqidv.end());


                            empobjects eo;
                            eo.empnum = strempnum;
                            eo.empname = strempname;
                            eo.password = stremppass;
                            eo.id = stoi(streqidv);

                            if (empm.updateemployee(eo)) {
                                SetWindowTextA(pageentries[11], "Updated successfully!!!");

                            }
                            else {
                                SetWindowTextA(pageentries[11], "Failed!! ");
                            }
                            SetWindowTextA(pageentries[7], "");
                            SetWindowTextA(pageentries[9], "");
                            SetWindowTextA(pageentries[46], "");
                            eqeditmode = false;

                        }
                        emeditmode = false;
                    }
                    
                    empm.closeConnection();
                }
                else {
                    SetWindowTextA(pageentries[11], "Please fill Employee Details!!!");
                }
            }
            break;
        case SUBMITPROC:
            {
                int ulenn = GetWindowTextLengthW(pageentries[14]) + 1;
                if (ulenn > 1) {
                    wchar_t* pname = new wchar_t[ulenn];
                    GetWindowTextW(pageentries[14], pname, ulenn);

                    std::wstring wspname(pname);
                    std::string strpname(wspname.begin(), wspname.end());


                    processModel pm;
                    pm.OpenConnection();
                    if (pm.insertpname(strpname)) {
                        SetWindowTextA(pageentries[16], "Successfully inserted!!!");
                        fillProcessEntries();
                    }
                    else {
                        SetWindowTextA(pageentries[16], "Failed!! check if already exists");
                    }
                    pm.closeConnection();

                }
                else {
                    SetWindowTextA(pageentries[16], "Please fill Process Details!!!");
                }
            }
            break;
        case SUBMITFAULT:
            {
                int ulenn = GetWindowTextLengthW(pageentries[19]) + 1;
                if (ulenn > 1) {
                    wchar_t* fname = new wchar_t[ulenn];
                    GetWindowTextW(pageentries[19], fname, ulenn);

                    std::wstring wsfname(fname);
                    std::string strfname(wsfname.begin(), wsfname.end());


                    faultModel fm;
                    fm.OpenConnection();
                    if (fm.insertftype(strfname)) {
                        SetWindowTextA(pageentries[21], "Successfully inserted!!!");
                        fillFaultEntries();
                    }
                    else {
                        SetWindowTextA(pageentries[21], "Failed!! check if already exists");
                    }
                    fm.closeConnection();

                }
                else {
                    SetWindowTextA(pageentries[21], "Please fill Fault Details!!!");
                }
            }
            break;
        case SUBMITRESP:
        {
            int ulenn = GetWindowTextLengthW(pageentries[24]) + 1;
            if (ulenn > 1) {
                wchar_t* rname = new wchar_t[ulenn];
                GetWindowTextW(pageentries[24], rname, ulenn);

                std::wstring wsrname(rname);
                std::string strrname(wsrname.begin(), wsrname.end());

                respModel rm;
                rm.OpenConnection();
                if (rm.insertresp(strrname)) {
                    SetWindowTextA(pageentries[26], "Successfully inserted!!!");
                    fillRespEntries();
                }
                else {
                    SetWindowTextA(pageentries[26], "Failed!! check if already exists");
                }
                rm.closeConnection();

            }
            else {
                SetWindowTextA(pageentries[26], "Please fill Responsibility Details!!!");
            }

        }
        break;
        case DELETEEQUIP:
        {
            int ulenn = GetWindowTextLengthW(pageentries[28]) + 1;
            if (ulenn > 1) {
                wchar_t* equipnt = new wchar_t[ulenn];
                GetWindowTextW(pageentries[28], equipnt, ulenn);

                std::wstring wsequipnt(equipnt);
                std::string strequipnt(wsequipnt.begin(), wsequipnt.end());


                equipModel em;
                em.OpenConnection();
                if (em.deleteequipnt(strequipnt)) {
                    SetWindowTextA(pageentries[4], "Deleted successfully!!!");
                    fillEquipEntries();
                }
                else {
                    SetWindowTextA(pageentries[4], "Failed!! ");
                }
                em.closeConnection();

            }
            else {
                SetWindowTextA(pageentries[4], "Fill Equipment id to delete");
            }
        }
        break;
        case EDITEQUIP:
        {
            int ulenn = GetWindowTextLengthW(pageentries[28]) + 1;
            if (ulenn > 1) {
                eqeditmode = true;
                wchar_t* equipnt = new wchar_t[ulenn];
                GetWindowTextW(pageentries[28], equipnt, ulenn);

                std::wstring wsequipnt(equipnt);
                std::string strequipnt(wsequipnt.begin(), wsequipnt.end());


                equipModel em;
                em.OpenConnection();
                equipData ed = em.getoneequip(strequipnt);
                SetWindowTextA(pageentries[2], ed.equipnt.c_str());
                SetWindowTextA(pageentries[43], ed.description.c_str());
                SetWindowTextA(pageentries[4], "Edit Mode!!");

                em.closeConnection();

            }
            else {
                SetWindowTextA(pageentries[4], "Fill Equipment id to edit");
            }
        }
        break;
        case EDITEMP:
        {
            int ulenn = GetWindowTextLengthW(pageentries[32]) + 1;
            if (ulenn > 1) {
                emeditmode = true;
                wchar_t* equipnt = new wchar_t[ulenn];
                GetWindowTextW(pageentries[32], equipnt, ulenn);

                std::wstring wsequipnt(equipnt);
                std::string strequipnt(wsequipnt.begin(), wsequipnt.end());


                employeeModel em;
                em.OpenConnection();

                empobjects eo = em.getoneEmployee(strequipnt);
                SetWindowTextA(pageentries[7], eo.empnum.c_str());
                SetWindowTextA(pageentries[9], eo.empname.c_str());
                SetWindowTextA(pageentries[46], eo.password.c_str());
                SetWindowTextA(pageentries[11], "Edit Mode!!");


                em.closeConnection();

            }
            else {
                SetWindowTextA(pageentries[11], "Fill Employee table id to delete");
            }
        }
        break;
        case DELETEEMP:
        {
            int ulenn = GetWindowTextLengthW(pageentries[32]) + 1;
            if (ulenn > 1) {
                wchar_t* equipnt = new wchar_t[ulenn];
                GetWindowTextW(pageentries[32], equipnt, ulenn);

                std::wstring wsequipnt(equipnt);
                std::string strequipnt(wsequipnt.begin(), wsequipnt.end());


                employeeModel em;
                em.OpenConnection();
                if (em.deleteemp(strequipnt)) {
                    SetWindowTextA(pageentries[11], "Deleted successfully!!!");
                    fillEmployeeEntries();
                }
                else {
                    SetWindowTextA(pageentries[11], "Failed!! ");
                }
                em.closeConnection();

            }
            else {
                SetWindowTextA(pageentries[11], "Fill Employee table id to delete");
            }
        }
        break;
        case DELETEPROC:
        {
            int ulenn = GetWindowTextLengthW(pageentries[35]) + 1;
            if (ulenn > 1) {
                wchar_t* equipnt = new wchar_t[ulenn];
                GetWindowTextW(pageentries[35], equipnt, ulenn);

                std::wstring wsequipnt(equipnt);
                std::string strequipnt(wsequipnt.begin(), wsequipnt.end());


                processModel em;
                em.OpenConnection();
                if (em.deleteprocess(strequipnt)) {
                    SetWindowTextA(pageentries[16], "Deleted successfully!!!");
                    fillProcessEntries();
                    
                }
                else {
                    SetWindowTextA(pageentries[16], "Failed!! ");
                }
                em.closeConnection();

            }
            else {
                SetWindowTextA(pageentries[16], "Fill process table id to delete");
            }

        }
        break;
        case DELETEFAULT:
        {
            int ulenn = GetWindowTextLengthW(pageentries[38]) + 1;
            if (ulenn > 1) {
                wchar_t* equipnt = new wchar_t[ulenn];
                GetWindowTextW(pageentries[38], equipnt, ulenn);

                std::wstring wsequipnt(equipnt);
                std::string strequipnt(wsequipnt.begin(), wsequipnt.end());


                faultModel em;
                em.OpenConnection();
                if (em.deletefault(strequipnt)) {
                    SetWindowTextA(pageentries[21], "Deleted successfully!!!");
                    fillFaultEntries();

                }
                else {
                    SetWindowTextA(pageentries[21], "Failed!! ");
                }
                em.closeConnection();

            }
            else {
                SetWindowTextA(pageentries[21], "Fill fault table id to delete");
            }
        }
        break;
        case DELETERESP:
        {
            int ulenn = GetWindowTextLengthW(pageentries[41]) + 1;
            if (ulenn > 1) {
                wchar_t* equipnt = new wchar_t[ulenn];
                GetWindowTextW(pageentries[41], equipnt, ulenn);

                std::wstring wsequipnt(equipnt);
                std::string strequipnt(wsequipnt.begin(), wsequipnt.end());


                respModel em;
                em.OpenConnection();
                if (em.deleteresp(strequipnt)) {
                    SetWindowTextA(pageentries[26], "Deleted successfully!!!");
                    fillRespEntries();

                }
                else {
                    SetWindowTextA(pageentries[26], "Failed!! ");
                }
                em.closeConnection();

            }
            else {
                SetWindowTextA(pageentries[26], "Fill fault table id to delete");
            }
        }
        break;
        default:
            break;
    }
}

void adminpage::fillEquipEntries() {
    equipModel em;
    em.OpenConnection();
    std::vector<equipData> equiplist = em.getallequipnts();
    em.closeConnection();
    std::string ft = "Equipment Tag/Name\r\n";
    int height = 20;
    for (auto it = equiplist.begin(); it != equiplist.end(); ++it) {
        ft = ft + std::to_string(it->id) + "\t" + it->equipnt + "\r\n";
        height = height + 20;
    }
    SetWindowTextA(pageentries[5], ft.c_str());
    SetWindowPos(pageentries[5],
        0,
        40,
        335,
        200,
        300,//height,
        0
    );
}

void adminpage::fillEmployeeEntries() {
    employeeModel empm;
    empm.OpenConnection();
    std::vector<empobjects> emplist = empm.getallemployees();
    empm.closeConnection();
    std::string ft = "Employee Details\r\n";
    int height = 20;

    for (auto it = emplist.begin(); it != emplist.end(); ++it) {
        ft = ft + std::to_string(it->id) + "\t" + it->empnum + "\t" + it->empname + "\r\n";
        height = height + 20;
    }

    SetWindowTextA(pageentries[12], ft.c_str());
    SetWindowPos(pageentries[12],
        0,
        280,
        370,
        200,
        244,
        0
    );

}

void adminpage::fillProcessEntries() {
    processModel pm;
    pm.OpenConnection();
    std::vector<processobj> processlist = pm.getallprocess();
    pm.closeConnection();
    std::string ft = "Prcoess Details\r\n";
    int height = 20;

    for (auto it = processlist.begin(); it != processlist.end(); ++it) {
        ft = ft + std::to_string(it->id) + "\t" + it->processname + "\r\n";
        height = height + 20;
    }

    SetWindowTextA(pageentries[17], ft.c_str());
    SetWindowPos(pageentries[17],
        0,
        520,
        240,
        200,
        300,
        0
    );
}

void adminpage::fillFaultEntries() {
    faultModel fm;
    fm.OpenConnection();
    std::vector<faultobj> faultlist = fm.getallfaults();
    fm.closeConnection();
    std::string ft = "Fault Types\r\n";
    int height = 20;

    for (auto it = faultlist.begin(); it != faultlist.end(); ++it) {
        ft = ft + std::to_string(it->id) + "\t" + it->faulttype + "\r\n";
        height = height + 20;
    }

    SetWindowTextA(pageentries[22], ft.c_str());
    SetWindowPos(pageentries[22],
        0,
        760,
        240,
        200,
        300,
        0
    );
}

void adminpage::fillRespEntries(){
    respModel rm;
    rm.OpenConnection();
    std::vector<respData> resplist = rm.getallresp();
    rm.closeConnection();
    std::string rp = "Responsibilities \r\n";
    int height = 20;

    for (auto it = resplist.begin(); it != resplist.end(); ++it) {
        rp = rp + std::to_string(it->id) + "\t" + it->respname + "\r\n";
        height = height + 20;
    }

    SetWindowTextA(pageentries[27], rp.c_str());
    SetWindowPos(pageentries[27],
            0,
            1000,
            240,
            200,
            300,
            0
        );
}