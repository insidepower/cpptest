#include <windows.h>
#include "resource.h"

const char g_szClassName[] = "myWindowClass";

// DialogBox handler (don't return until finish)
BOOL CALLBACK AboutDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch(Message)
	{
		case WM_INITDIALOG:

		return TRUE;
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				case IDOK:
					EndDialog(hwnd, IDOK);
				break;
				case IDCANCEL:
					EndDialog(hwnd, IDCANCEL);
				break;
			}
		break;
		default:
			return FALSE;
	}
	return TRUE;
}

// CreateDialog() handler
BOOL CALLBACK ToolDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    switch(Message)
    {
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case IDC_PRESS:
                    MessageBox(hwnd, "Hi!", "This is a message", 
                        MB_OK | MB_ICONEXCLAMATION);
                break;
                case IDC_OTHER:
                    MessageBox(hwnd, "Bye!", "This is also a message", 
                        MB_OK | MB_ICONEXCLAMATION);
                break;
            }
        break;
        default:
            return FALSE;
    }
    return TRUE;
}

HWND g_hToolbar = NULL;

// Step 4: the Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		case WM_LBUTTONDOWN:
			// BEGIN NEW CODE
			{
				char szFileName[MAX_PATH];
				HINSTANCE hInstance = GetModuleHandle(NULL);

				GetModuleFileName(hInstance, szFileName, MAX_PATH);
				MessageBox(hwnd, szFileName, "This program is:", MB_OK | MB_ICONINFORMATION);
			}
			// END NEW CODE
		case WM_CREATE:
			g_hToolbar = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_TOOLBAR),
					hwnd, ToolDlgProc);
			if(g_hToolbar != NULL) {
				ShowWindow(g_hToolbar, SW_SHOW);
			} else {
				MessageBox(hwnd, "CreateDialog returned NULL", "Warning!",  
						MB_OK | MB_ICONINFORMATION);
			}
			break;
		/// menu id
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				case ID_FILE_EXIT:
					PostMessage(hwnd, WM_CLOSE, 0, 0);
					break;
				case ID_HELP_ABOUT:
					{
						int ret = DialogBox(GetModuleHandle(NULL), 
								MAKEINTRESOURCE(IDD_ABOUT), hwnd, AboutDlgProc);
						if(ret == IDOK){
							MessageBox(hwnd, "Dialog exited with IDOK.", "Notice",
									MB_OK | MB_ICONINFORMATION);
						}
						else if(ret == IDCANCEL){
							MessageBox(hwnd, "Dialog exited with IDCANCEL.", "Notice",
									MB_OK | MB_ICONINFORMATION);
						}
						else if(ret == -1){
							MessageBox(hwnd, "Dialog failed!", "Error",
									MB_OK | MB_ICONINFORMATION);
						}
					}
					break;
				case ID_DIALOG_SHOW:
					ShowWindow(g_hToolbar, SW_SHOW);
					break;
				case ID_DIALOG_HIDE:
					ShowWindow(g_hToolbar, SW_HIDE);
					break;
			}
			break;
		case WM_CLOSE:
			DestroyWindow(hwnd);
			break;
		case WM_DESTROY:
			DestroyWindow(g_hToolbar);
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}


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
	wc.lpszMenuName  = MAKEINTRESOURCE(IDR_MYMENU);
	wc.lpszClassName = g_szClassName;
	wc.hIcon  = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYICON));
	wc.hIconSm  = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYICON), IMAGE_ICON, 16, 16, 0);


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
			"The title of my window",
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, 240, 120,
			NULL, NULL, hInstance, NULL);

	if(hwnd == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!",
				MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	// Step 3: The Message Loop
	while(GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		// to get the alt-tab & hotkey working in the CreateDialog
		if(!IsDialogMessage(g_hToolbar, &Msg)){
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
	}
	return Msg.wParam;
}
