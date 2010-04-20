#include <windows.h>
#include "resource.h"
#include "string.h"

const char g_szClassName[] = "myWindowClass";
HWND g_hChildMainGui = NULL;
HWND g_hInfoDialogBox = NULL;
char szSrcFileName[MAX_PATH]="";
char szDstFileName[MAX_PATH]="";


BOOL CALLBACK childMainGuiProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch(Message)
	{
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				case IDC_BTN_INPUT_SRC:
					{
						OPENFILENAME ofn;
						char szFileName[MAX_PATH] = "";

						ZeroMemory(&ofn, sizeof(ofn));
						ofn.lStructSize = sizeof(OPENFILENAME);
						ofn.hwndOwner = hwnd;
						ofn.lpstrFilter = "vhd Files (*.vhd)\0*.vhd\0All Files (*.*)\0*.*\0";
						ofn.lpstrFile = szFileName;
						ofn.nMaxFile = MAX_PATH;
						ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
						ofn.lpstrDefExt = "vhd";

						if(GetOpenFileName(&ofn))
						{
							/// display the path name to control edit box
							HWND hEdit = GetDlgItem(hwnd, IDC_INPUT_SRC);
							strcpy(szSrcFileName, ofn.lpstrFile);
							SetWindowText(hEdit, szSrcFileName);
						}
					}
					break;
				case IDC_BTN_INPUT_DST:
					{
						OPENFILENAME ofn;
						char szFileName[MAX_PATH] = "";

						ZeroMemory(&ofn, sizeof(ofn));
						ofn.lStructSize = sizeof(OPENFILENAME);
						ofn.hwndOwner = hwnd;
						ofn.lpstrFilter = "Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
						ofn.lpstrFile = szFileName;
						ofn.nMaxFile = MAX_PATH;
						ofn.lpstrDefExt = "txt";
						ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;

						if(GetSaveFileName(&ofn))
						{
							HWND hEdit = GetDlgItem(hwnd, IDC_INPUT_DST);
							strcpy(szDstFileName, ofn.lpstrFile);
							SetWindowText(hEdit, szDstFileName);
						}
					}
					break;
			}
			break;
		default:
			return FALSE;
	}
	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		case WM_CREATE:
			/// create child window
			{
				g_hChildMainGui = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_FORMVIEW),
						hwnd, childMainGuiProc);
				if(g_hChildMainGui != NULL) {
					ShowWindow(g_hChildMainGui, SW_SHOW);
				} else {
					MessageBox(hwnd, "CreateDialog returned NULL", "Warning!",  
							MB_OK | MB_ICONINFORMATION);
				}
			}
			break;

			/// window size change
		case WM_SIZE: break;
		case WM_CLOSE:
					  DestroyWindow(hwnd);
					  break;
		case WM_DESTROY:
					  DestroyWindow(g_hInfoDialogBox);
					  PostQuitMessage(0);
					  break;
		default:
					  return DefWindowProc(hwnd, msg, wParam, lParam);

	}
	return 0;
}

/// main function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
		LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;

	//Step 1: Registering the Window Class
	wc.cbSize        = sizeof(WNDCLASSEX);
	wc.style         = 0;
	wc.lpfnWndProc   = WndProc;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = hInstance;
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszMenuName  = NULL;
	wc.lpszClassName = g_szClassName;
	wc.hIcon  = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm  = LoadIcon(NULL, IDI_APPLICATION);;


	if(!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!",
				MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	// Step 2: Creating the Window
	hwnd = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			g_szClassName,
			"Hexadecimal to Binary Converter",
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, 500, 190,
			NULL, NULL, hInstance, NULL);

	if(hwnd == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!",
				MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	/// The Message Loop
	while(GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		/// to get the alt-tab & hotkey working in the CreateDialog
		//if(!IsDialogMessage(g_hInfoDialogBox, &Msg)){
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
		//}
	}
	return Msg.wParam;
}

