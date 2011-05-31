//#include "stdafx.h"
#include <windows.h>
#include "resource.h"
#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                      // current instance
TCHAR szTitle[MAX_LOADSTRING];        // The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];  // The title bar text

// Forward declarations of functions included in this code module:
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


int WINAPI WinMain(HINSTANCE hInstance,
				   HINSTANCE hPrevInstance,
				   LPTSTR     lpCmdLine,
				   int       nCmdShow)
{
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDS_WIN_CLASS, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}
	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDS_WIN_CLASS);

	// Main message loop:
	/// message posted by PostMessage will get by GetMessage
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage is only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;;
	wc.lpfnWndProc = (WNDPROC) WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = 0;
	wc.hCursor = 0;
	//wc.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
	wc.hbrBackground =(HBRUSH) GetStockObject(LTGRAY_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = szWindowClass;
	return RegisterClass(&wc);
}


//
//   FUNCTION: InitInstance(HANDLE, int)
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
	HWND hWnd;
	hInst = hInstance; // Store instance handle in our global variable
	hWnd = CreateWindow(szWindowClass, szTitle, WS_BORDER | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, 500, 230, NULL, NULL, hInstance, NULL);
	if (!hWnd)
	{
		return FALSE;
	}
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	//MessageBox(hWnd, TEXT("my title"), TEXT("header"),NULL);
	return TRUE;
}

BOOL CALLBACK DialogBoxProc(HWND hWnd, UINT Message,
							   WPARAM wParam, LPARAM lParam)
{
	switch(Message)
	{
		case WM_COMMAND:
			switch(LOWORD(wParam)){
				case IDC_BUTTON1: 
					MessageBox(hWnd, TEXT("btn1 is pressed"), TEXT("header"),NULL);
					break; 
				case IDC_BUTTON2: break; 
				default:
					return FALSE;
			}
		case WM_NEXTDLGCTL:
			break;
		default:
			return FALSE;
	}
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
/*-------------------------------------------------------------------------
 Global Variables
 -------------------------------------------------------------------------*/
HWND g_hModelessDlgBox = NULL;
HWND hStatus = NULL;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int i=0;
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR szHello[MAX_LOADSTRING];
	LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);
	switch (message) 
	{
	case WM_CREATE:
		/// create child window
		{
			g_hModelessDlgBox = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_FORMVIEW),
				hWnd, DialogBoxProc);
			if(g_hModelessDlgBox != NULL) {
				ShowWindow(g_hModelessDlgBox, SW_SHOW);
			} else {
				MessageBox(hWnd, "CreateDialog returned NULL", "Warning!",  
					MB_OK | MB_ICONEXCLAMATION);
			}
		}
		break;
	case WM_INITDIALOG:
		break;
	case WM_LBUTTONDOWN:
		break;

	case WM_PAINT:
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}