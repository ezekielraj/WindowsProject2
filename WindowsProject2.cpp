#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif
// WindowsProject2.cpp : Defines the entry point for the application.
//

#include<iostream>
#include<tchar.h>
#include "framework.h"
#include "WindowsProject2.h"
#include "Pages.h"

#include "homepage.cpp"
#include "loginpage.h"
#include "adminpage.h"
#include "inputpage.h"
#include "outputpage.h"
#include "dbbackuppage.h"
#include "apuserlog.h"
#include "Logger.h"
#define MAX_LOADSTRING 100

#define IDM_IP 6000
#define IDM_OP 6001
#define IDM_AP_LOGIN 6002
#define IDM_FILE_QUIT 6003
#define IDM_HELP 6004
#define IDM_ADMIN_PAGE 6005
#define IDM_AP_LOGOUT 6006
#define IDM_AP_ADMINCTRL 6007
#define IDM_AP_DBBACKUP 6008
#define IDM_AP_LOGGED 6009

// Global Variables:
HINSTANCE hInst;                                // current instance
HMENU hMenubar;
HMENU hMenu;
HMENU hMenu1;

pages *p;
 
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name]
HBITMAP hBitmap = NULL;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
bool LoadAndBlitBitmap(LPCWSTR szFileName, HDC hWinDC);
bool LoadAndBlitBitmap1(LPCWSTR szFileName, HDC hWinDC);
static bool ShowImmage = true;
static bool StopPaint = false;
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, SW_MAXIMIZE))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT2));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;//MAKEINTRESOURCEW(IDC_WINDOWSPROJECT2);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, _T("Digitization"), WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    //static HBRUSH hbrBackground;
    PAINTSTRUCT ps;
    HDC hdc;

    switch (message)
    {
    case WM_CREATE:
        
        hMenubar = CreateMenu();
        hMenu = CreateMenu();
        hMenu1 = CreateMenu();

        AppendMenuW(hMenu, MF_STRING, IDM_FILE_QUIT, L"&Exit");
        AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR)hMenu, L"&File");
            AppendMenuW(hMenu1, MF_STRING, IDM_AP_LOGIN, L"&Login");
        AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR)hMenu1, L"&Admin Page");
        AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR)hMenu1, L"&Input Page");
       //AppendMenuW(hMenubar, MF_STRING, IDM_IP, L"&Input Page");
       AppendMenuW(hMenubar, MF_STRING, IDM_OP, L"&Output Page");
        AppendMenuW(hMenubar, MF_STRING, IDM_HELP, L"&Help");

        SetMenu(hWnd, hMenubar);
        p = new homepage(hWnd);
        p->CreatePage();

        break;
    /*case WM_CTLCOLORDLG:
        return (LONG)hbrBackground;
    case WM_CTLCOLORSTATIC:
    {
        HDC hdcStatic = (HDC)wParam;
        SetBkMode(hdcStatic, TRANSPARENT);
        return (LONG)hbrBackground;
    }*/
    case WM_COMMAND:
        {
            
            
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_AP_LOGIN:
            {
                ShowImmage = false;
                p->DestroyPage();
                p = new loginpage(hWnd);
                p->CreatePage();
                break;
            }
            case IDM_IP:
            {
                LOGGER->Log("Input menu cclicked and in switch case of ip");
                ShowImmage = false;
                p->DestroyPage();
                LOGGER->Log("previous page destroyed in the page objecct");
                if (loginpage::UserAuthenticated) {
                    p = new inputpage(hWnd);
                    
                    hMenu1 = CreateMenu();
                    AppendMenuW(hMenu1, MF_STRING, IDM_IP, L"&Input Updates");
                    AppendMenuW(hMenu1, MF_STRING, IDM_AP_LOGOUT, L"&Logout");
                    ModifyMenuW(hMenubar, 2, MF_BYPOSITION | MF_POPUP, (UINT_PTR)hMenu1, L"&Input Page");
                    SetMenu(hWnd, hMenubar);
                    
                }
                else {
                    p = new loginpage(hWnd);
                    
                }
                LOGGER->Log("input page ctor class is created");
                p->CreatePage();
                LOGGER->Log("Create for input page is executed successfully");
                break;
            }
            case IDM_OP:
            {
                ShowImmage = false;
                p->DestroyPage();
                p = new outputpage(hWnd);
                p->CreatePage();
                break;
            }
            case IDM_HELP:
                ShowImmage = false;
                break;
            case IDM_FILE_QUIT:
                ShowImmage = false;
                delete p;
                PostQuitMessage(0);
                break;
            case IDM_ADMIN_PAGE:
                p->DestroyPage();
                if (loginpage::Authenticated) {
                    p = new adminpage(hWnd);
                    
                    hMenu1 = CreateMenu();
                    AppendMenuW(hMenu1, MF_STRING, IDM_AP_ADMINCTRL, L"&Admin Updates");
                    AppendMenuW(hMenu1, MF_STRING, IDM_AP_DBBACKUP, L"&DB Backup");
                    AppendMenuW(hMenu1, MF_STRING, IDM_AP_LOGGED, L"&User Log");
                    AppendMenuW(hMenu1, MF_STRING, IDM_AP_LOGOUT, L"&Logout");
                    ModifyMenuW(hMenubar, 1, MF_BYPOSITION | MF_POPUP, (UINT_PTR)hMenu1, L"&AdminPage");
                    SetMenu(hWnd,hMenubar); 
                }
                else {
                    p = new loginpage(hWnd);
                }
                p->CreatePage();
                break;
            case IDM_AP_DBBACKUP:
                p->DestroyPage();
                if (loginpage::Authenticated) {
                    p = new dbbackuppage(hWnd);
                }
                else {
                    p = new loginpage(hWnd);
                }
                p->CreatePage();
                break;
            case IDM_AP_LOGGED:
                p->DestroyPage();
                if (loginpage::Authenticated) {
                    p = new apuserlog(hWnd);
                }
                else {
                    p = new loginpage(hWnd);
                }
                p->CreatePage();
                break;
            case IDM_AP_LOGOUT:
                ShowImmage = false;
                if(loginpage::Authenticated){
                    loginpage::Authenticated = false;
                    hMenu1 = CreateMenu();
                    AppendMenuW(hMenu1, MF_STRING, IDM_AP_LOGIN, L"&Login");
                    ModifyMenuW(hMenubar, 1, MF_BYPOSITION | MF_POPUP, (UINT_PTR)hMenu1, L"&Admin Page");
                    SetMenu(hWnd, hMenubar);
                    
                }
                if (loginpage::UserAuthenticated) {
                    loginpage::UserAuthenticated = false;
                    hMenu1 = CreateMenu();
                    AppendMenuW(hMenu1, MF_STRING, IDM_AP_LOGIN, L"&Login");
                    ModifyMenuW(hMenubar, 2, MF_BYPOSITION | MF_POPUP, (UINT_PTR)hMenu1, L"&Input Page");
                    SetMenu(hWnd, hMenubar);
                }
                    p->DestroyPage();
                    p = new loginpage(hWnd);
                    p->CreatePage();
                
                break;
            case IDM_AP_ADMINCTRL:
                ShowImmage = false;
                if (loginpage::Authenticated) {
                    p->DestroyPage();
                    p = new adminpage(hWnd);
                    p->CreatePage();
                }
                break;
            default:
                if (HIWORD(wParam) == BN_CLICKED || (HIWORD(wParam) == CBN_SELCHANGE)) {
                    if (p) {
                        p->HandleEvent(wParam, lParam);
                    }
                }
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_NOTIFY:
        if (p) {
            p->HandleNotifyEvent(wParam, lParam);
        }
        break;
//        MessageBoxW(hWnd,L"hi", L"hi", MB_OK);
    case WM_PAINT:
        if(ShowImmage){
        hdc = BeginPaint(hWnd, &ps);
        LoadAndBlitBitmap(__T("fm.bmp"), hdc);
        EndPaint(hWnd, &ps);
        }
        else {
            InvalidateRect(hWnd, NULL, NULL);
            hdc = BeginPaint(hWnd, &ps);
            LoadAndBlitBitmap(__T("white.bmp"), hdc);
            EndPaint(hWnd, &ps);
            StopPaint = true;
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
/*INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
*/

bool LoadAndBlitBitmap(LPCWSTR szFileName, HDC hWinDC)
{
    // Load the bitmap image file
    HBITMAP hBitmap;
    hBitmap = (HBITMAP)::LoadImage(NULL, szFileName, IMAGE_BITMAP, 0, 0,
        LR_LOADFROMFILE);
    // Verify that the image was loaded
    if (hBitmap == NULL) {
        ::MessageBox(NULL, __T("LoadImage Failed"), __T("Error"), MB_OK);
        return false;
    }

    // Create a device context that is compatible with the window
    HDC hLocalDC;
    hLocalDC = ::CreateCompatibleDC(hWinDC);
    // Verify that the device context was created
    if (hLocalDC == NULL) {
        ::MessageBox(NULL, __T("CreateCompatibleDC Failed"), __T("Error"), MB_OK);
        return false;
    }

    // Get the bitmap's parameters and verify the get
    BITMAP qBitmap;
    int iReturn = GetObject(reinterpret_cast<HGDIOBJ>(hBitmap), sizeof(BITMAP),
        reinterpret_cast<LPVOID>(&qBitmap));
    if (!iReturn) {
        ::MessageBox(NULL, __T("GetObject Failed"), __T("Error"), MB_OK);
        return false;
    }

    // Select the loaded bitmap into the device context
    HBITMAP hOldBmp = (HBITMAP)::SelectObject(hLocalDC, hBitmap);
    if (hOldBmp == NULL) {
        ::MessageBox(NULL, __T("SelectObject Failed"), __T("Error"), MB_OK);
        return false;
    }

    // Blit the dc which holds the bitmap onto the window's dc
    BOOL qRetBlit = ::BitBlt(hWinDC, 50, 50, qBitmap.bmWidth, qBitmap.bmHeight,
        hLocalDC, 0, 0, SRCCOPY);
    if (!qRetBlit) {
        ::MessageBox(NULL, __T("Blit Failed"), __T("Error"), MB_OK);
        return false;
    }

    // Unitialize and deallocate resources
    ::SelectObject(hLocalDC, hOldBmp);
    ::DeleteDC(hLocalDC);
    ::DeleteObject(hBitmap);
    return true;
}

