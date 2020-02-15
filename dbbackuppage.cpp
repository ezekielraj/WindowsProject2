#include "dbbackuppage.h"
#include <tchar.h>

#define EXPORTSQL 900
#define IMPORTSQL 901

dbbackuppage::dbbackuppage(HWND &hwnd) : pages(50) {
    dbhwnd = hwnd;

}

dbbackuppage::~dbbackuppage() {
    DestroyPage();
}


void dbbackuppage::CreatePage() {
    pageentries[0] = CreateWindowA(
            "BUTTON",  // Predefined class; Unicode assumed
            "EXPORT DB",      // Button text
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
            40,         // x position
            40,         // y position
            150,        // Button width
            30,        // Button height
            dbhwnd,     // Parent window
            (HMENU)EXPORTSQL,       // No menu.
            (HINSTANCE)GetWindowLong(dbhwnd, GWLP_HINSTANCE),
            NULL);
    

    pageentries[1] = CreateWindowA(
            "BUTTON",  // Predefined class; Unicode assumed
            "IMPORT DB",      // Button text
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
            40,         // x position
            80,         // y position
            150,        // Button width
            30,        // Button height
            dbhwnd,     // Parent window
            (HMENU)IMPORTSQL,       // No menu.
            (HINSTANCE)GetWindowLong(dbhwnd, GWLP_HINSTANCE),
            NULL);

    pageentries[2] = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"),
            L"",
            WS_CHILD | WS_VISIBLE | WS_VSCROLL |
            ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,
            40, 120, 450, 450,
            dbhwnd,
            NULL, NULL, NULL
        );
}


void dbbackuppage::HandleNotifyEvent(WPARAM &wParam, LPARAM &lParam) { }

void dbbackuppage::HandleEvent(WPARAM wParam, LPARAM lParam) {

    switch (LOWORD(wParam))
    {
        case EXPORTSQL:
        {
            AppendText(pageentries[2], "=====================================================\r\nChecking Mysql installation Path\r\n");
            
            FILE *fp;
            errno_t err;

            if ((err = fopen_s(&fp,"C:\\mysql\\mysql-8.0.17-winx64\\bin\\mysqldump.exe", "r")) != 0) {
                AppendText(pageentries[2], "MysqlDump Not Exists!!!\r\n Kindly install mysql so the installation path will be C:\mysql\mysql-8.0.17-winx64\bin\r\n");
            }
            else {
                fclose(fp);
                AppendText(pageentries[2], "MysqlDump Exists\r\n");
                wchar_t filename[MAX_PATH];

                OPENFILENAME ofn;
                //SAVEFILE
                ZeroMemory(&filename, sizeof(filename));
                //wchar_t wtext[20];
                //mbstowcs_s(wtext, filename, strlen(filename) + 1);
                ZeroMemory(&ofn, sizeof(ofn));
                ofn.lStructSize = sizeof(ofn);
                ofn.hwndOwner = NULL;  // If you have a window to center over, put its HANDLE here
                ofn.lpstrFilter = L"SQL Files(.sql)\0*.sql\0Any File\0*.*\0";
                ofn.lpstrFile = filename;
                ofn.lpstrFile[0] = '\0';
                ofn.nMaxFile = MAX_PATH;
                ofn.lpstrTitle = L"Select a File, yo!";
                ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

                if (GetSaveFileName(&ofn))
                {

                    std::wstring fn = std::wstring(filename);
                    std::string strfn = std::string(fn.begin(), fn.end());

                    AppendText(pageentries[2], "File Selected :");
                    AppendText(pageentries[2], strfn.c_str());
                    AppendText(pageentries[2], "\r\n");

                    AppendText(pageentries[2], "running system ccall\r\n");
                    std::string systemcall = "C:\\mysql\\mysql-8.0.17-winx64\\bin\\mysqldump.exe -uroot -p123456 -P55555 digitization > " + strfn;
                    system(systemcall.c_str());
                    AppendText(pageentries[2], "completed taking sql backup check the location\r\n");
                    AppendText(pageentries[2], strfn);
                }
                else
                {
                    // All this stuff below is to tell you exactly how you messed up above. 
                    // Once you've got that fixed, you can often (not always!) reduce it to a 'user cancelled' assumption.
                    switch (CommDlgExtendedError())
                    {
                    case CDERR_DIALOGFAILURE: MessageBox(dbhwnd, L"CDERR_DIALOGFAILURE", L"", MB_OK);   break;
                    case CDERR_FINDRESFAILURE: MessageBox(dbhwnd, L"CDERR_FINDRESFAILURE", L"", MB_OK);  break;
                    case CDERR_INITIALIZATION: MessageBox(dbhwnd, L"CDERR_INITIALIZATION", L"", MB_OK);  break;
                    case CDERR_LOADRESFAILURE: MessageBox(dbhwnd, L"CDERR_LOADRESFAILURE", L"", MB_OK);  break;
                    case CDERR_LOADSTRFAILURE: MessageBox(dbhwnd, L"CDERR_LOADSTRFAILURE", L"", MB_OK);  break;
                    case CDERR_LOCKRESFAILURE: MessageBox(dbhwnd, L"CDERR_LOCKRESFAILURE", L"", MB_OK);  break;
                    case CDERR_MEMALLOCFAILURE: MessageBox(dbhwnd, L"CDERR_MEMALLOCFAILURE", L"", MB_OK); break;
                    case CDERR_MEMLOCKFAILURE: MessageBox(dbhwnd, L"CDERR_MEMLOCKFAILURE", L"", MB_OK);  break;
                    case CDERR_NOHINSTANCE: MessageBox(dbhwnd, L"CDERR_NOHINSTANCE", L"", MB_OK);     break;
                    case CDERR_NOHOOK: MessageBox(dbhwnd, L"CDERR_NOHOOK", L"", MB_OK);          break;
                    case CDERR_NOTEMPLATE: MessageBox(dbhwnd, L"CDERR_NOTEMPLATE", L"", MB_OK);      break;
                    case CDERR_STRUCTSIZE: MessageBox(dbhwnd, L"CDERR_STRUCTSIZE", L"", MB_OK);      break;
                    case FNERR_BUFFERTOOSMALL: MessageBox(dbhwnd, L"FNERR_BUFFERTOOSMALL", L"", MB_OK);  break;
                    case FNERR_INVALIDFILENAME: MessageBox(dbhwnd, L"FNERR_INVALIDFILENAME", L"", MB_OK); break;
                    case FNERR_SUBCLASSFAILURE: MessageBox(dbhwnd, L"FNERR_SUBCLASSFAILURE", L"", MB_OK); break;
                    default: MessageBox(dbhwnd, L"You cancelled.", L"", MB_OK);
                    }
                }
            }

        }
        break;
        case IMPORTSQL:
        {
            AppendText(pageentries[2], "=====================================================\r\nChecking Mysql installation Path\r\n");

            FILE *fp;
            errno_t err;

            if ((err = fopen_s(&fp, "C:\\mysql\\mysql-8.0.17-winx64\\bin\\mysql.exe", "r")) != 0) {
                AppendText(pageentries[2], "MysqlDump Not Exists!!!\r\n Kindly install mysql so the installation path will be C:\mysql\mysql-8.0.17-winx64\bin\r\n");
            }
            else {
                fclose(fp);
                AppendText(pageentries[2], "MysqlDump Exists\r\n");
                wchar_t filename[MAX_PATH];

                OPENFILENAME ofn;
                //SAVEFILE
                ZeroMemory(&filename, sizeof(filename));
                //wchar_t wtext[20];
                //mbstowcs_s(wtext, filename, strlen(filename) + 1);
                ZeroMemory(&ofn, sizeof(ofn));
                ofn.lStructSize = sizeof(ofn);
                ofn.hwndOwner = NULL;  // If you have a window to center over, put its HANDLE here
                ofn.lpstrFilter = L"SQL Files(.sql)\0*.sql\0Any File\0*.*\0";
                ofn.lpstrFile = filename;
                ofn.lpstrFile[0] = '\0';
                ofn.nMaxFile = MAX_PATH;
                ofn.lpstrTitle = L"Select a File, yo!";
                ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;
            
                if (GetOpenFileName(&ofn))
                {
//                    MessageBox(dbhwnd,filename, L"", MB_OK);
                    std::wstring fn = std::wstring(filename);
                    std::string strfn = std::string(fn.begin(), fn.end());

                    AppendText(pageentries[2], "File Selected :");
                    AppendText(pageentries[2], strfn.c_str());
                    AppendText(pageentries[2], "\r\n");

                    AppendText(pageentries[2], "running system ccall\r\n");
                    std::string systemcall = "C:\\mysql\\mysql-8.0.17-winx64\\bin\\mysql.exe -uroot -p123456 -P55555 digitization < " + strfn;
                    system(systemcall.c_str());
                    AppendText(pageentries[2], "completed importing sql backup check the db!!!\r\n");
                    AppendText(pageentries[2], strfn);
                }
                else
                {
                    // All this stuff below is to tell you exactly how you messed up above. 
                    // Once you've got that fixed, you can often (not always!) reduce it to a 'user cancelled' assumption.
                    switch (CommDlgExtendedError())
                    {
                    case CDERR_DIALOGFAILURE: MessageBox(dbhwnd, L"CDERR_DIALOGFAILURE", L"", MB_OK);   break;
                    case CDERR_FINDRESFAILURE: MessageBox(dbhwnd, L"CDERR_FINDRESFAILURE", L"", MB_OK);  break;
                    case CDERR_INITIALIZATION: MessageBox(dbhwnd, L"CDERR_INITIALIZATION", L"", MB_OK);  break;
                    case CDERR_LOADRESFAILURE: MessageBox(dbhwnd, L"CDERR_LOADRESFAILURE", L"", MB_OK);  break;
                    case CDERR_LOADSTRFAILURE: MessageBox(dbhwnd, L"CDERR_LOADSTRFAILURE", L"", MB_OK);  break;
                    case CDERR_LOCKRESFAILURE: MessageBox(dbhwnd, L"CDERR_LOCKRESFAILURE", L"", MB_OK);  break;
                    case CDERR_MEMALLOCFAILURE: MessageBox(dbhwnd, L"CDERR_MEMALLOCFAILURE", L"", MB_OK); break;
                    case CDERR_MEMLOCKFAILURE: MessageBox(dbhwnd, L"CDERR_MEMLOCKFAILURE", L"", MB_OK);  break;
                    case CDERR_NOHINSTANCE: MessageBox(dbhwnd, L"CDERR_NOHINSTANCE", L"", MB_OK);     break;
                    case CDERR_NOHOOK: MessageBox(dbhwnd, L"CDERR_NOHOOK", L"", MB_OK);          break;
                    case CDERR_NOTEMPLATE: MessageBox(dbhwnd, L"CDERR_NOTEMPLATE", L"", MB_OK);      break;
                    case CDERR_STRUCTSIZE: MessageBox(dbhwnd, L"CDERR_STRUCTSIZE", L"", MB_OK);      break;
                    case FNERR_BUFFERTOOSMALL: MessageBox(dbhwnd, L"FNERR_BUFFERTOOSMALL", L"", MB_OK);  break;
                    case FNERR_INVALIDFILENAME: MessageBox(dbhwnd, L"FNERR_INVALIDFILENAME", L"", MB_OK); break;
                    case FNERR_SUBCLASSFAILURE: MessageBox(dbhwnd, L"FNERR_SUBCLASSFAILURE", L"", MB_OK); break;
                    default: MessageBox(dbhwnd, L"You cancelled.", L"", MB_OK);
                    }
                }
            
            }
        }
        break;
        default:
            break;
    }
}
void dbbackuppage::AppendText(HWND &hwndOutput, std::string newText)
{
    
    
    // get the current selection
    DWORD StartPos, EndPos;
    SendMessage(hwndOutput, EM_GETSEL, reinterpret_cast<WPARAM>(&StartPos), reinterpret_cast<WPARAM>(&EndPos));

    // move the caret to the end of the text
    int outLength = GetWindowTextLength(hwndOutput);
    SendMessage(hwndOutput, EM_SETSEL, outLength, outLength);

    // insert the text at the new caret position
    SendMessage(hwndOutput, EM_REPLACESEL, TRUE, reinterpret_cast<LPARAM>(std::wstring(newText.begin(), newText.end()).c_str()));

    // restore the previous selection
    SendMessage(hwndOutput, EM_SETSEL, StartPos, EndPos);
}