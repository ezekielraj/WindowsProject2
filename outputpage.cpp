#include "outputpage.h"
#include<windows.h>
#include<string>
#include<commdlg.h>
#include "xlsxwriter.h"
#include "dataModel.h"

#include "equipModel.h"

#include <string>
#include <atlstr.h>

#include <commctrl.h>
#include <richedit.h>



#define GENCSV 800
#define OCMBOX1 801
#define GETDATA 802
#define SHOWPREV 803
#define SHOWNEXT 804

outputpage::outputpage(HWND &hwnd) : pages(30) {
    ophwnd = hwnd;
    ctp = 0;
}
void outputpage::CreatePage() {

    
     pageentries[0] = CreateWindowA(
             "BUTTON",  // Predefined class; Unicode assumed
             "Generate OverAll Excel",      // Button text
             WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
             40,         // x position
             40,         // y position
             200,        // Button width
             30,        // Button height
             ophwnd,     // Parent window
             (HMENU)GENCSV,       // No menu.
             (HINSTANCE)GetWindowLong(ophwnd, GWLP_HINSTANCE),
             NULL);
     

     pageentries[2] = CreateWindowA("ComboBox", "",
         CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | WS_VSCROLL | CBS_AUTOHSCROLL |
         ES_LEFT | WS_HSCROLL,
         40, 75, 150, 200, ophwnd, (HMENU)OCMBOX1, NULL,
         NULL);

     pageentries[3] = CreateWindowW(L"SysDateTimePick32", NULL,

         WS_BORDER | WS_VISIBLE | WS_CHILD | WS_TABSTOP,

         200, 75, 150, 30, ophwnd, NULL, NULL, NULL);
     std::string dateFormat = "M'/'d'/'yyyy";
     DateTime_SetFormat(pageentries[3], std::wstring(dateFormat.begin(), dateFormat.end()).c_str());


     pageentries[4] = CreateWindowA(
             "BUTTON",  // Predefined class; Unicode assumed
             "Get Data",      // Button text
             WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
             360,         // x position
             75,         // y position
             100,        // Button width
             30,        // Button height
             ophwnd,     // Parent window
             (HMENU)GETDATA,       // No menu.
             (HINSTANCE)GetWindowLong(ophwnd, GWLP_HINSTANCE),
             NULL);
     pageentries[5] = CreateWindowA(
         "BUTTON",  // Predefined class; Unicode assumed
         "Prev",      // Button text
         WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
         760,         // x position
         75,         // y position
         100,        // Button width
         30,        // Button height
         ophwnd,     // Parent window
         (HMENU)SHOWPREV,       // No menu.
         (HINSTANCE)GetWindowLong(ophwnd, GWLP_HINSTANCE),
         NULL);
     pageentries[6] = CreateWindowA(
         "BUTTON",  // Predefined class; Unicode assumed
         "Next",      // Button text
         WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
         865,         // x position
         75,         // y position
         100,        // Button width
         30,        // Button height
         ophwnd,     // Parent window
         (HMENU)SHOWNEXT,       // No menu.
         (HINSTANCE)GetWindowLong(ophwnd, GWLP_HINSTANCE),
         NULL);
     equipModel em;
     em.OpenConnection();
     std::vector<std::string> equiplist = em.getallequipnt();
     em.closeConnection();
     TCHAR A[16];

     memset(&A, 0, sizeof(A));
     for (auto it = equiplist.begin(); it != equiplist.end(); ++it) {

         _tcscpy_s(A, CA2T((*it).c_str()));

         // Add string to combobox.
         SendMessage(pageentries[2], (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)A);
     }

     // Send the CB_SETCURSEL message to display an initial item 
     //  in the selection field  
     SendMessage(pageentries[2], CB_SETCURSEL, (WPARAM)0, (LPARAM)0);

     int ItemIndex1 = SendMessage(pageentries[2], (UINT)CB_GETCURSEL,
         (WPARAM)0, (LPARAM)0);

     (TCHAR)SendMessage(pageentries[2], (UINT)CB_GETLBTEXT,
         (WPARAM)ItemIndex1, (LPARAM)EquipNT);


}
void outputpage::HandleEvent(WPARAM wParam, LPARAM lParam){ 
    switch (LOWORD(wParam))
    {
        case SHOWNEXT:
        {
            
            ctp = ctp+10;
            if (datalist.size() > ctp) {
                auto vi = pageentries.begin();
                vi = vi + 7;
                for (; vi != pageentries.end(); ++vi) {
                    DestroyWindow(*vi);
                }
                filltenentries(ctp);
            }
            else {
                ctp = ctp-10;
            }
        }
        break;
        case SHOWPREV:
        {
            ctp = ctp - 10;
            if (ctp >=0 ) {
                auto vi = pageentries.begin();
                vi = vi + 7;
                for (; vi != pageentries.end(); ++vi) {
                    DestroyWindow(*vi);
                }
                filltenentries(ctp);
            }
            else {
                ctp = ctp + 10;
            }
        }
        break;
        case GETDATA:
        {
            dataModel dm;
            dm.OpenConnection();

            std::wstring wsequipnt(EquipNT);
            std::string strequipnt(wsequipnt.begin(), wsequipnt.end());
            int tdhhlen = GetWindowTextLengthW(pageentries[3]) + 1;
           // if (tdhhlen > 1) {
                wchar_t* tdhhval = new wchar_t[tdhhlen];
                GetWindowTextW(pageentries[3], tdhhval, tdhhlen);

                std::wstring wstdhhval(tdhhval);
                std::string strtdhhval(wstdhhval.begin(), wstdhhval.end());

                std::string delimiter = "/";
                size_t pos = 0;
                std::string token;
                pos = strtdhhval.find(delimiter);
                token = strtdhhval.substr(0, pos);
                //            std::cout << token << std::endl;
                std::string month = token;
                strtdhhval.erase(0, pos + delimiter.length());

                pos = strtdhhval.find(delimiter);
                token = strtdhhval.substr(0, pos);
                std::string day = token;
                std::cout << token << std::endl;
                strtdhhval.erase(0, pos + delimiter.length());

                std::string year = strtdhhval;

                std::string completedate = year + "-" + month + "-" + day;
            //}
                //int height = 110;
            std::vector<dataobject> cdatalist = dm.getspecificdata(strequipnt, completedate);
            datalist.clear();

            for (auto itr = cdatalist.begin(); itr != cdatalist.end(); ++itr) {
                datalist.push_back(*itr);
            }

            dm.closeConnection();
            ctp = 0;
            auto vi = pageentries.begin();
            vi = vi + 7;
            for (; vi != pageentries.end(); ++vi) {
                DestroyWindow(*vi);
            }
                filltenentries(ctp);
        }
        break;
        case OCMBOX1:
        {
            int ItemIndex = SendMessage(pageentries[2], (UINT)CB_GETCURSEL,
                (WPARAM)0, (LPARAM)0);

            (TCHAR)SendMessage(pageentries[2], (UINT)CB_GETLBTEXT,
                (WPARAM)ItemIndex, (LPARAM)EquipNT);
            ///MessageBox(ophwnd, (LPCWSTR)ListItem, TEXT("Item Selected"), MB_OK);
        }
        break;
        case GENCSV:
            {
            wchar_t filename[MAX_PATH];

            OPENFILENAME ofn;
            //SAVEFILE
            ZeroMemory(&filename, sizeof(filename));
            //wchar_t wtext[20];
            //mbstowcs_s(wtext, filename, strlen(filename) + 1);
            ZeroMemory(&ofn, sizeof(ofn));
            ofn.lStructSize = sizeof(ofn);
            ofn.hwndOwner = NULL;  // If you have a window to center over, put its HANDLE here
            ofn.lpstrFilter = L"Excel Files(xlsx)\0*.xlsx\0Any File\0*.*\0";
            ofn.lpstrFile = filename;
            ofn.lpstrFile[0] = '\0';
            ofn.nMaxFile = MAX_PATH;
            ofn.lpstrTitle = L"Select a File, yo!";
            ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

            if (GetSaveFileName(&ofn))
            {
                
                std::wstring fn = std::wstring(filename);
                std::string strfn = std::string(fn.begin(), fn.end());

                lxw_workbook  *workbook = workbook_new(strfn.c_str());
                lxw_worksheet *worksheet = workbook_add_worksheet(workbook, "CAPA");
                lxw_worksheet *worksheet0 = workbook_add_worksheet(workbook, "Support");
                lxw_worksheet *worksheet1 = workbook_add_worksheet(workbook, "ComparisonHours");
                lxw_worksheet *worksheet2 = workbook_add_worksheet(workbook, "ComparisonCount");
                lxw_format *merge_format = workbook_add_format(workbook);
                format_set_align(merge_format, LXW_ALIGN_CENTER);
                format_set_pattern(merge_format, LXW_PATTERN_SOLID);
                format_set_bg_color(merge_format, LXW_COLOR_GREEN);
                format_set_border(merge_format, LXW_BORDER_THICK);
                format_set_bold(merge_format);
                worksheet_merge_range(worksheet, 0, 0, 0, 13, "CAPA Report", merge_format);

                lxw_format *bold = workbook_add_format(workbook);
                format_set_bold(bold);
                format_set_text_wrap(bold);
                format_set_align(bold, LXW_ALIGN_CENTER);
                format_set_pattern(bold, LXW_PATTERN_SOLID);
                format_set_bg_color(bold, 0x38c2c2);
                format_set_border(bold, LXW_BORDER_THIN);

                lxw_format *normalcell = workbook_add_format(workbook);
                format_set_text_wrap(normalcell);
                format_set_border(normalcell, LXW_BORDER_THIN);



               int a = 1;

                worksheet_write_string(worksheet, a, 0, "ID", bold);
                worksheet_write_string(worksheet, a, 1, "Area/Process", bold);
                worksheet_write_string(worksheet, a, 2, "Date", bold);
                worksheet_write_string(worksheet, a, 3, "Equipment", bold);
                worksheet_write_string(worksheet, a, 4, "Equip Desc", bold);
                worksheet_write_string(worksheet, a, 5, "No Run Reason", bold);
                worksheet_write_string(worksheet, a, 6, "Delay/Downtime", bold);
                worksheet_write_string(worksheet, a, 7, "Delay/Downtime Duration", bold);
                worksheet_write_string(worksheet, a, 8, "Start Date/Time", bold);
                worksheet_write_string(worksheet, a, 9, "Stop Date/Time", bold);
                worksheet_write_string(worksheet, a, 10, "Fault Type", bold);
                worksheet_write_string(worksheet, a, 11, "Fault Description", bold);
                worksheet_write_string(worksheet, a, 12, "Effect on Process", bold);
                worksheet_write_string(worksheet, a, 13, "Responsibility", bold);
                worksheet_write_string(worksheet, a, 14, "Employee", bold);
                worksheet_write_string(worksheet, a, 15, "Corrective Action Taken", bold);


                dataModel dm;
                dm.OpenConnection();

                std::vector<dataobject> dobj = dm.getalldata();
                int i=2;
                for (auto it = dobj.begin(); it != dobj.end(); ++it) {
                    worksheet_write_string(worksheet, i, 0, std::to_string(it->id).c_str(), normalcell);
                    worksheet_write_string(worksheet, i, 1, (it->processname).c_str(), normalcell);
                    worksheet_write_string(worksheet, i, 2, (it->date).c_str(), normalcell);
                    worksheet_write_string(worksheet, i, 3, (it->equipnt).c_str(), normalcell);
                    worksheet_write_string(worksheet, i, 4, (it->equipdes).c_str(), normalcell);
                    worksheet_write_string(worksheet, i, 5, (it->norunreason).c_str(), normalcell);
                    worksheet_write_string(worksheet, i, 6, (it->timedesc).c_str(), normalcell);
                    worksheet_write_string(worksheet, i, 7, (it->timedeschh + ":" + it->timedescmm + ":" + it->timedescss).c_str(), normalcell);
                    worksheet_write_string(worksheet, i, 8, (it->starttime.getinpformat()).c_str(), normalcell);
                    worksheet_write_string(worksheet, i, 9, (it->stoptime.getinpformat()).c_str(), normalcell);
                    worksheet_write_string(worksheet, i, 10, (it->faulttype).c_str(), normalcell);
                    worksheet_write_string(worksheet, i, 11, (it->faultdesc).c_str(), normalcell);
                    worksheet_write_string(worksheet, i, 12, (it->processeffect).c_str(), normalcell);
                    worksheet_write_string(worksheet, i, 13, (it->responsibility).c_str(), normalcell);
                    worksheet_write_string(worksheet, i, 14, (it->attendeename).c_str(), normalcell);
                    worksheet_write_string(worksheet, i, 15, (it->remarks).c_str(), normalcell);
                    i++;
                }



                equipModel em;
                em.OpenConnection();
                std::vector<std::string> ed = em.getallequipnt();

                worksheet_write_string(worksheet0, 0, 0, "Equipment Name", bold);
                worksheet_write_string(worksheet0, 0, 1, "Total Delay hours", bold);
                worksheet_write_string(worksheet0, 0, 2, "Total Downtime hours", bold);
                worksheet_write_string(worksheet0, 0, 3, "Total Delay Count", bold);
                worksheet_write_string(worksheet0, 0, 4, "Total Downtime Count", bold);

                int b = 1;
                int just = 10;
                int hour1 =0, min1 =0, sec1 =0;
                int hour=0, min=0,sec=0;
                std::string s;
                std::string delimiter = ":";
                size_t pos = 0;
                std::string token;

                for (auto et = ed.begin(); et != ed.end(); ++et) {

                    worksheet_write_string(worksheet0, b, 0, (*et).c_str(), normalcell);

                    std::vector<std::string> delaytimes = dm.equipDelaytime(*et);
                    std::vector<std::string> downtimes = dm.equipDowntime(*et);
                    sec = 0;
                    min = 0;
                    hour = 0;
                    sec1 = 0;
                    min1 = 0;
                    hour1 = 0;
                    for (auto det = delaytimes.begin(); det != delaytimes.end(); ++det) {
                        s = *det;
                        pos = 0;
                        pos = s.find(delimiter);
                        token = s.substr(0, pos);
                        hour1 = stoi(token);
                        s.erase(0, pos + delimiter.length());
                        pos = s.find(delimiter);
                        token = s.substr(0, pos);
                        min1 = stoi(token);
                        s.erase(0, pos + delimiter.length());
                        sec1 = stoi(s);

                        sec = sec + sec1;
                        min = min + min1 + (sec / 60);
                        hour = hour + hour1 + (min / 60);
                        min = min % 60;
                        sec = sec % 60;

                    }
                    worksheet_write_number(worksheet0, b, 1, float(hour) + float(min)/float(30), normalcell);

                    sec = 0;
                    min = 0;
                    hour = 0;
                    sec1 = 0;
                    min1 = 0;
                    hour1 = 0;
                    for (auto dot = downtimes.begin(); dot != downtimes.end(); ++dot) {
                        s = *dot;
                        pos = 0;
                        pos = s.find(delimiter);
                        token = s.substr(0, pos);
                        hour1 = stoi(token);
                        s.erase(0, pos + delimiter.length());
                        pos = s.find(delimiter);
                        token = s.substr(0, pos);
                        min1 = stoi(token);
                        s.erase(0, pos + delimiter.length());
                        sec1 = stoi(s);

                        sec = sec + sec1;
                        min = min + min1 + (sec / 60);
                        hour = hour + hour1 + (min / 60);
                        min = min % 60;
                        sec = sec % 60;

                    }
                    worksheet_write_number(worksheet0, b, 2, double(hour) + double(min)/double(30), normalcell);
                    worksheet_write_number(worksheet0, b, 3, delaytimes.size(), normalcell);
                    worksheet_write_number(worksheet0, b, 4, downtimes.size(), normalcell);
                    b=b+1;
                    just = just +10;
                }

                em.closeConnection();
                dm.closeConnection();

                std::string yaxisloc = "=Support!$A$2:$A$";
                yaxisloc = yaxisloc + std::to_string(b);

                std::string xaxisloc1 = "=Support!$B$2:$B$";
                xaxisloc1 = xaxisloc1 + std::to_string(b);

                std::string xaxisloc2 = "=Support!$C$2:$C$";
                xaxisloc2 = xaxisloc2 + std::to_string(b);

                std::string xaxisloc3 = "=Support!$D$2:$D$";
                xaxisloc3 = xaxisloc3 + std::to_string(b);

                std::string xaxisloc4 = "=Support!$E$2:$E$";
                xaxisloc4 = xaxisloc4 + std::to_string(b);

                lxw_chart_series *series;
                lxw_chart *chart = workbook_add_chart(workbook, LXW_CHART_COLUMN);

                /* Add the first series to the chart. */
                series = chart_add_series(chart, yaxisloc.c_str(), xaxisloc1.c_str());

                
                /* Set the name for the series instead of the default "Series 1". */
                chart_series_set_name(series, "=Support!$B$1");
                //lxw_chart_fill fill1;// = {
                //fill1.color = LXW_COLOR_RED;
                //chart_series_set_fill(series, &fill1);
                /* Add a second series but leave the categories and values undefined. They
                 * can be defined later using the alternative syntax shown below.  */
                series = chart_add_series(chart, yaxisloc.c_str(), xaxisloc2.c_str());
                chart_series_set_name(series, "=Support!$C$1");
                
                
                /* Configure the series using a syntax that is easier to define programmatically. */
//                chart_series_set_categories(series, "Support", 1, 0, 6, 0); /* "=Support!$A$2:$A$7" */
 //               chart_series_set_values(series, "Support", 1, 2, 6, 2); /* "=Support!$C$2:$C$7" */
  //              chart_series_set_name_range(series, "Support", 0, 2);       /* "=Support!$C$1"      */
                
                

                /* Add a chart title and some axis labels. */
                chart_title_set_name(chart, "Results of Equip analysis");
                chart_axis_set_name(chart->x_axis, "Equipments");
                chart_axis_set_name(chart->y_axis, "Hours");

                /* Set an Excel chart style. */
                chart_set_style(chart, 12);

                /* Insert the chart into the worksheet. */
                worksheet_insert_chart(worksheet1, CELL("B2"), chart);
//========================================================================
                chart = workbook_add_chart(workbook, LXW_CHART_COLUMN);

                /* Add the first series to the chart. */
                series = chart_add_series(chart, yaxisloc.c_str(), xaxisloc3.c_str());

                /* Set the name for the series instead of the default "Series 1". */
                chart_series_set_name(series, "=Support!$D$1");

                /* Add the second series to the chart. */
                series = chart_add_series(chart, yaxisloc.c_str(), xaxisloc4.c_str());

                /* Set the name for the series instead of the default "Series 2". */
                chart_series_set_name(series, "=Support!$E$1");

                /* Add a chart title and some axis labels. */
                chart_title_set_name(chart, "Results of Equip count analysis");
                chart_axis_set_name(chart->x_axis, "Equipments");
                chart_axis_set_name(chart->y_axis, "Count");

                /* Set an Excel chart style. */
                chart_set_style(chart, 12);

                std::string cellvalue = "U" + std::to_string(b+b);

                /* Insert the chart into the worksheet. */
                worksheet_insert_chart(worksheet2, CELL("B2"), chart);

                workbook_close(workbook);


                MessageBox(ophwnd, L"Excel Generated", L"", MB_OK);
//                std::cout << "You chose the file \"" << filename << "\"\n";
            }
            else
            {
                // All this stuff below is to tell you exactly how you messed up above. 
                // Once you've got that fixed, you can often (not always!) reduce it to a 'user cancelled' assumption.
                switch (CommDlgExtendedError())
                {
                case CDERR_DIALOGFAILURE: MessageBox(ophwnd, L"CDERR_DIALOGFAILURE", L"", MB_OK);   break;
                case CDERR_FINDRESFAILURE: MessageBox(ophwnd, L"CDERR_FINDRESFAILURE", L"", MB_OK);  break;
                case CDERR_INITIALIZATION: MessageBox(ophwnd, L"CDERR_INITIALIZATION", L"", MB_OK);  break;
                case CDERR_LOADRESFAILURE: MessageBox(ophwnd, L"CDERR_LOADRESFAILURE", L"", MB_OK);  break;
                case CDERR_LOADSTRFAILURE: MessageBox(ophwnd, L"CDERR_LOADSTRFAILURE", L"", MB_OK);  break;
                case CDERR_LOCKRESFAILURE: MessageBox(ophwnd, L"CDERR_LOCKRESFAILURE", L"", MB_OK);  break;
                case CDERR_MEMALLOCFAILURE: MessageBox(ophwnd, L"CDERR_MEMALLOCFAILURE", L"", MB_OK); break;
                case CDERR_MEMLOCKFAILURE: MessageBox(ophwnd, L"CDERR_MEMLOCKFAILURE", L"", MB_OK);  break;
                case CDERR_NOHINSTANCE: MessageBox(ophwnd, L"CDERR_NOHINSTANCE", L"", MB_OK);     break;
                case CDERR_NOHOOK: MessageBox(ophwnd, L"CDERR_NOHOOK", L"", MB_OK);          break;
                case CDERR_NOTEMPLATE: MessageBox(ophwnd, L"CDERR_NOTEMPLATE", L"", MB_OK);      break;
                case CDERR_STRUCTSIZE: MessageBox(ophwnd, L"CDERR_STRUCTSIZE", L"", MB_OK);      break;
                case FNERR_BUFFERTOOSMALL: MessageBox(ophwnd, L"FNERR_BUFFERTOOSMALL", L"", MB_OK);  break;
                case FNERR_INVALIDFILENAME: MessageBox(ophwnd, L"FNERR_INVALIDFILENAME", L"", MB_OK); break;
                case FNERR_SUBCLASSFAILURE: MessageBox(ophwnd, L"FNERR_SUBCLASSFAILURE", L"", MB_OK); break;
                default: MessageBox(ophwnd, L"You cancelled.", L"", MB_OK);
                }
            }
            }
            break;
        default:
            break;
    }

}

void outputpage::HandleNotifyEvent(WPARAM &wParam, LPARAM &lParam) { }

outputpage::~outputpage() {
    DestroyPage();
}

void outputpage::filltenentries(int ctp) {
    int height = 110;
    auto it= datalist.begin();
    it = it+ctp;
    int i = 0;
//    for (auto it = datalist.begin(); it != datalist.end(); ++it) {
    while(it!=datalist.end() && i < 10){
        
        pageentries.push_back(CreateWindowA("STATIC",
            (LPCSTR)std::to_string(it->id).c_str(),
            WS_VISIBLE | WS_CHILD,
            40, height, 20, 60,
            ophwnd,
            NULL, NULL, NULL
        ));
        pageentries.push_back(CreateWindowA("STATIC",
            (LPCSTR)(it->date).c_str(),
            WS_VISIBLE | WS_CHILD,
            65, height, 75, 60,
            ophwnd,
            NULL, NULL, NULL
        ));
        pageentries.push_back(CreateWindowA("STATIC",
            (LPCSTR)(it->equipnt).c_str(),
            WS_VISIBLE | WS_CHILD,
            145, height, 75, 60,
            ophwnd,
            NULL, NULL, NULL
        ));
        pageentries.push_back(CreateWindowA("STATIC",
            (LPCSTR)(it->norunreason).c_str(),
            WS_VISIBLE | WS_CHILD,
            225, height, 75, 60,
            ophwnd,
            NULL, NULL, NULL
        ));
        std::string timedescnew = it->timedesc + " | " + it->timedeschh + ":" + it->timedescmm + ":" + it->timedescss;
        pageentries.push_back(CreateWindowA("STATIC",
            (LPCSTR)(timedescnew).c_str(),
            WS_VISIBLE | WS_CHILD,
            305, height, 150, 60,
            ophwnd,
            NULL, NULL, NULL
        ));
        pageentries.push_back(CreateWindowA("STATIC",
            (LPCSTR)(it->faulttype).c_str(),
            WS_VISIBLE | WS_CHILD,
            460, height, 100, 60,
            ophwnd,
            NULL, NULL, NULL
        ));
        pageentries.push_back(CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"),
            std::wstring(it->faultdesc.begin(), it->faultdesc.end()).c_str(),
            WS_CHILD | WS_VISIBLE | WS_VSCROLL |
            ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,
            565, height, 150, 60,
            ophwnd,
            NULL, NULL, NULL
        ));
        pageentries.push_back(CreateWindowA("STATIC",
            (LPCSTR)(it->processname).c_str(),
            WS_VISIBLE | WS_CHILD,
            720, height, 75, 60,
            ophwnd,
            NULL, NULL, NULL
        ));
        pageentries.push_back(CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"),
            std::wstring(it->processeffect.begin(), it->processeffect.end()).c_str(),
            WS_CHILD | WS_VISIBLE | WS_VSCROLL |
            ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,
            800, height, 150, 60,
            ophwnd,
            NULL, NULL, NULL
        ));
        pageentries.push_back(CreateWindowA("STATIC",
            (LPCSTR)(it->attendeename).c_str(),
            WS_VISIBLE | WS_CHILD,
            955, height, 75, 60,
            ophwnd,
            NULL, NULL, NULL
        ));
        pageentries.push_back(
            CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), std::wstring(it->remarks.begin(), it->remarks.end()).c_str(),
                WS_CHILD | WS_VISIBLE | WS_VSCROLL |
                ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,
                1035, height, 150, 60,
                ophwnd,
                NULL, NULL, NULL
            ));
        pageentries.push_back(CreateWindowA("STATIC",
            (LPCSTR)(it->responsibility).c_str(),
            WS_VISIBLE | WS_CHILD,
            1190, height, 100, 60,
            ophwnd,
            NULL, NULL, NULL
        ));
        height = height + 65;
        it++;
        i++;
    }
}