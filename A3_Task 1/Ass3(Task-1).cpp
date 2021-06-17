// Ass3(Task-1).cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Ass3(Task-1).h"
#include "Curve.h"
#include <windowsx.h>


struct Circle {
    int xc, yc;
    int r;
};

Circle c1, c2, c3;

struct line {
    int xs, ys;
};

line l1, l2, l3;

int bx[3], by[3];

bool clickFlags[15] = { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };


#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

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
    LoadStringW(hInstance, IDC_ASS3TASK1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ASS3TASK1));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ASS3TASK1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_ASS3TASK1);
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

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
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
    switch (message)
    {

    case WM_CREATE:
    {
        HMENU menuBar = CreateMenu();
        HMENU circlesBar = CreateMenu();
        HMENU curveBar = CreateMenu();
        HMENU linesBar = CreateMenu();

        LPCWSTR circles = L"Circles";
        LPCWSTR circle1 = L"Circle 1";
        LPCWSTR circle2 = L"Circle 2";
        LPCWSTR circle3 = L"Circle 3";
        LPCWSTR curve = L"Curve";
        LPCWSTR lines = L"Lines";
        LPCWSTR line1 = L"Line 1";
        LPCWSTR line2 = L"Line 2";
        LPCWSTR line3 = L"Line 3";

        AppendMenu(menuBar, MF_POPUP, (UINT_PTR)circlesBar, circles);
        AppendMenu(circlesBar, MF_STRING, 1, circle1);
        AppendMenu(circlesBar, MF_STRING, 2, circle2);
        AppendMenu(circlesBar, MF_STRING, 3, circle3);
        AppendMenu(menuBar, MF_POPUP, 4, curve);
        AppendMenu(menuBar, MF_POPUP, (UINT_PTR)linesBar, lines);
        AppendMenu(linesBar, MF_STRING, 5, line1);
        AppendMenu(linesBar, MF_STRING, 6, line2);
        AppendMenu(linesBar, MF_STRING, 7, line3);

        SetMenu(hWnd, menuBar);
    }
    case WM_COMMAND:
        {
        switch (wParam)
        {
        case 1:
            MessageBeep(MB_OK);
            clickFlags[0] = true;
            break;

        case 2:
            clickFlags[2] = true;
            break;

        case 3:
            clickFlags[4] = true;
            break;

        case 4:
            clickFlags[6] = true;
            break;

        case 5:
            clickFlags[9] = true;
            break;

        case 6:
            clickFlags[11] = true;
            break;

        case 7:
            clickFlags[13] = true;
            break;
        }
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }

        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;

    case WM_LBUTTONDOWN:
        if (clickFlags[0])
        {
            c1.xc = GET_X_LPARAM(lParam);
            c1.yc = GET_Y_LPARAM(lParam);
            clickFlags[0] = false;
            clickFlags[1] = true;
        }

        else if (clickFlags[2])
        {
            c2.xc = GET_X_LPARAM(lParam);
            c2.yc = GET_Y_LPARAM(lParam);
            clickFlags[2] = false;
            clickFlags[3] = true;
        }

        else if (clickFlags[4])
        {
            c3.xc = GET_X_LPARAM(lParam);
            c3.yc = GET_Y_LPARAM(lParam);
            clickFlags[4] = false;
            clickFlags[5] = true;
        }

        else if (clickFlags[6])
        {
            bx[0] = GET_X_LPARAM(lParam);
            by[0] = GET_Y_LPARAM(lParam);
            clickFlags[6] = false;
            clickFlags[7] = true;
        }

        else if (clickFlags[7])
        {
            bx[1] = GET_X_LPARAM(lParam);
            by[1] = GET_Y_LPARAM(lParam);
            clickFlags[7] = false;
            clickFlags[8] = true;
        }

        else if (clickFlags[9])
        {
            l1.xs = GET_X_LPARAM(lParam);
            l1.ys = GET_Y_LPARAM(lParam);
            clickFlags[9] = false;
            clickFlags[10] = true;
        }

        else if (clickFlags[11])
        {
            l2.xs = GET_X_LPARAM(lParam);
            l2.ys = GET_Y_LPARAM(lParam);
            clickFlags[11] = false;
            clickFlags[12] = true;
        }

        else if (clickFlags[13])
        {
            l3.xs = GET_X_LPARAM(lParam);
            l3.ys = GET_Y_LPARAM(lParam);
            clickFlags[13] = false;
            clickFlags[14] = true;
        }

        break;

    case WM_RBUTTONUP:

        if (clickFlags[1])
        {
            HDC hdc = GetDC(hWnd);
            int x = GET_X_LPARAM(lParam);
            int y = GET_Y_LPARAM(lParam);
            c1.r = Ass3_Task_1::getRaduis(c1.xc, x, c1.yc, y);
            Ass3_Task_1::CirclePolar(hdc, c1.xc, c1.yc, c1.r, 0x00000000);
            clickFlags[1] = false;
            ReleaseDC(hWnd, hdc);
        }

        else if (clickFlags[3])
        {
            HDC hdc = GetDC(hWnd);
            int x = GET_X_LPARAM(lParam);
            int y = GET_Y_LPARAM(lParam);
            c2.r = Ass3_Task_1::getRaduis(c2.xc, x, c2.yc, y);
            Ass3_Task_1::CirclePolar(hdc, c2.xc, c2.yc, c2.r, 0x00FF0000);
            clickFlags[3] = false;
            ReleaseDC(hWnd, hdc);
        }

        else if (clickFlags[5])
        {
            HDC hdc = GetDC(hWnd);
            int x = GET_X_LPARAM(lParam);
            int y = GET_Y_LPARAM(lParam);
            c3.r = Ass3_Task_1::getRaduis(c3.xc, x, c3.yc, y);
            Ass3_Task_1::CirclePolar(hdc, c3.xc, c3.yc, c3.r, 0x00FF0000);
            clickFlags[5] = false;
            ReleaseDC(hWnd, hdc);
        }

        else if (clickFlags[8])
        {
            HDC hdc = GetDC(hWnd);
            bx[2] = GET_X_LPARAM(lParam);
            by[2] = GET_Y_LPARAM(lParam);
            Quad_Curve::DrawBezier(hdc, bx, by);
            clickFlags[8] = false;
            ReleaseDC(hWnd, hdc);
        }

        else if (clickFlags[10])
        {
            HDC hdc = GetDC(hWnd);
            int x = GET_X_LPARAM(lParam);
            int y = GET_Y_LPARAM(lParam);
            //Ass3_Task_1::CohenSuth(hdc, l1.xs, l1.ys, x, y, abs(c1.xc - c1.r), (c1.xc + c1.r), abs(c1.yc - c1.r), (c1.yc + c1.r));
            Ass3_Task_1::CohenSuth2(hdc, l1.xs, l1.ys, x, y, c1.xc, c1.yc, c1.r);
            clickFlags[10] = false;
            ReleaseDC(hWnd, hdc);
        }

        else if (clickFlags[12])
        {
            HDC hdc = GetDC(hWnd);
            int x = GET_X_LPARAM(lParam);
            int y = GET_Y_LPARAM(lParam);
            //Ass3_Task_1::CohenSuth(hdc, l1.xs, l1.ys, x, y, abs(c1.xc - c1.r), (c1.xc + c1.r), abs(c1.yc - c1.r), (c1.yc + c1.r));
            Ass3_Task_1::CohenSuth2(hdc, l2.xs, l2.ys, x, y, c1.xc, c1.yc, c1.r);
            clickFlags[12] = false;
            ReleaseDC(hWnd, hdc);
        }

        else if (clickFlags[14])
        {
            HDC hdc = GetDC(hWnd);
            int x = GET_X_LPARAM(lParam);
            int y = GET_Y_LPARAM(lParam);
            //Ass3_Task_1::CohenSuth(hdc, l1.xs, l1.ys, x, y, abs(c1.xc - c1.r), (c1.xc + c1.r), abs(c1.yc - c1.r), (c1.yc + c1.r));
            Ass3_Task_1::CohenSuth2(hdc, l3.xs, l3.ys, x, y, c1.xc, c1.yc, c1.r);
            clickFlags[14] = false;
            ReleaseDC(hWnd, hdc);
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
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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
