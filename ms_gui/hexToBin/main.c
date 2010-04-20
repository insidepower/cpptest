#include <windows.h>
#include "resource.h"
#include "string.h"
#include "stdio.h" //fopen, fclose
#include "convertHexToBin.h"

#define H2BPATH_INI_FILE 		"h2bpath.ini"

const char g_szClassName[] = "myWindowClass";
HWND g_hChildMainGui = NULL;
HWND g_hInfoDialogBox = NULL;
char szSrcFileName[MAX_PATH]="";
char szDstFileName[MAX_PATH]="";
int isReversed=0;


BOOL CALLBACK childMainGuiProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch(Message)
	{
		case WM_INITDIALOG:
			/// populate file path if H2BPATH_INI_FILE exist
			{
				FILE * fp = fopen(H2BPATH_INI_FILE, "r");
				if(NULL!=fp){
					HWND hEdit = GetDlgItem(hwnd, IDC_INPUT_SRC);
					fgets(szSrcFileName, MAX_PATH, fp);
					fgets(szDstFileName, MAX_PATH, fp);
					SetWindowText(hEdit, szSrcFileName);
					hEdit = GetDlgItem(hwnd, IDC_INPUT_DST);
					SetWindowText(hEdit, szDstFileName);
					fclose(fp);
				}
			}
			break;
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
						ofn.lpstrDefExt = "vhd";//append if user forget to type the ext

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
						ofn.lpstrDefExt = NULL; 
						ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;

						if(GetSaveFileName(&ofn))
						{
							HWND hEdit = GetDlgItem(hwnd, IDC_INPUT_DST);
							strcpy(szDstFileName, ofn.lpstrFile);
							SetWindowText(hEdit, szDstFileName);
						}
					}
					break;
				case IDC_CHK_RVSD_BINARY:
					{
						HWND hChkBox = GetDlgItem(hwnd, IDC_CHK_RVSD_BINARY); 
						BOOL checked = IsDlgButtonChecked(hChkBox, 1);
						if (checked) {
							CheckDlgButton(hwnd, 1, BST_UNCHECKED);
							MessageBox(hwnd, "checked", "Info", 
									MB_OK | MB_ICONINFORMATION);
						}else{
							CheckDlgButton(hwnd, 1, BST_CHECKED);
							MessageBox(hwnd, "not checked", "Info", 
									MB_OK | MB_ICONINFORMATION);
						}
					}
					break;
				case IDC_BTN_CONVERT:
					{
						/// to convert the Hexadecimal to binary
						if (0==strlen(szSrcFileName) || 0==strlen(szDstFileName)){
							MessageBox(hwnd, "Please provide source and destination file", "Error", 
									MB_OK | MB_ICONEXCLAMATION);
						}else{
							int result = convert(szSrcFileName, szDstFileName, isReversed);
							if(FILE_SRC_OPEN_ERR == result){
								MessageBox(hwnd, "Error in opening source file", "Error", 
										MB_OK | MB_ICONEXCLAMATION);
							}else if(FILE_DST_OPEN_ERR == result){
								MessageBox(hwnd, "Error in opening destination file", "Error", 
										MB_OK | MB_ICONEXCLAMATION);
							}
						}
					}
					break;
				case IDC_BTN_SAVE:
					{
						/// to save the source and destination path for next ease of use
						FILE * fp = fopen(H2BPATH_INI_FILE, "w");
						if (NULL!=fp){
							fprintf(fp, szSrcFileName);
							fprintf(fp, "\n");
							fprintf(fp, szDstFileName);
							fprintf(fp, "\n");
							fclose(fp);
						}else{
							MessageBox(hwnd, "Error in saving path", "Error", 
										MB_OK | MB_ICONEXCLAMATION);
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
							MB_OK | MB_ICONEXCLAMATION);
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
		if(!IsDialogMessage(g_hInfoDialogBox, &Msg)){
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
	}
	return Msg.wParam;
}

