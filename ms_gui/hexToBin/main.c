/*-------------------------------------------------------------------------
Includes
-------------------------------------------------------------------------*/
#include <windows.h>
#include <commctrl.h>
#include "resource.h"
#include "string.h"
#include "stdio.h" //fopen, fclose
#include "convertHexToBin.h"
/*-------------------------------------------------------------------------
 Macros
 -------------------------------------------------------------------------*/
#define H2BPATH_INI_FILE 		"h2bpath.ini"
/*-------------------------------------------------------------------------
 Global Variables
 -------------------------------------------------------------------------*/
const char g_szClassName[] = "myWindowClass";
HWND g_hModelessDlgBox = NULL;
HWND g_hInfoDialogBox = NULL;
HWND hStatus = NULL;
char szSrcFileName[MAX_PATH]="";
char szDstFileName[MAX_PATH]="";
int isReversed=0;
int isDebug=0;
/*-------------------------------------------------------------------------
 Functions
 -------------------------------------------------------------------------*/
/*========================================================================
 DialogBoxProc
 =========================================================================*/
/** \brief Process the Dialog Box command */
BOOL CALLBACK DialogBoxProc(HWND hwnd, UINT Message,
							   WPARAM wParam, LPARAM lParam)
{
	switch(Message)
	{
		case WM_INITDIALOG:
			/// populate file path if H2BPATH_INI_FILE exist
			{
				FILE * fp = fopen(H2BPATH_INI_FILE, "r");
				unsigned char * p_str = NULL;
				if(NULL!=fp){
					HWND hEdit = GetDlgItem(hwnd, IDC_INPUT_SRC);
					fgets(szSrcFileName, MAX_PATH, fp);
					szSrcFileName[strlen(szSrcFileName)-1]='\0';
					fgets(szDstFileName, MAX_PATH, fp);
					// NOTE: immediately after last char of second line,
					// 		 it could be eof == NULL, thus no need to append \0
					if('\n' == szDstFileName[strlen(szDstFileName)-1]){
						/// extra check, just in case last char is newline
						szDstFileName[strlen(szDstFileName)-1]='\0';
					}
					SetWindowText(hEdit, szSrcFileName);
					hEdit = GetDlgItem(hwnd, IDC_INPUT_DST);
					SetWindowText(hEdit, szDstFileName);
					fclose(fp);
				}
			}
			//SendMessage(hwnd, WM_NEXTDLGCTL, 0L, 0L);
			break;
		case WM_COMMAND:
			switch(LOWORD(wParam)){
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
						ofn.lpstrFilter = "All Files (*.*)\0*.*\0Text Files (*.txt)\0*.txt\0";
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
						BOOL checked = IsDlgButtonChecked(hwnd, IDC_CHK_RVSD_BINARY);
						if (checked) {
							isReversed = 1;
						}else{
							isReversed = 0;
						}
					}
					break;
				case IDC_CHK_DEBUG:
					{
						BOOL checked = IsDlgButtonChecked(hwnd, IDC_CHK_DEBUG);
						if (checked) {
							isDebug = 1;
						}else{
							isDebug = 0;
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
							char myStr[MAX_PATH+50];
							int result = convert(szSrcFileName, szDstFileName, isReversed, isDebug);
							if(FILE_SRC_OPEN_ERR == result){
								sprintf(myStr, "Error in opening source file %s", szSrcFileName);
								MessageBox(hwnd, myStr, "Error",
										MB_OK | MB_ICONEXCLAMATION);
								break;
							}else if(FILE_DST_OPEN_ERR == result){
								sprintf(myStr, "Error in opening destination file %s", szDstFileName);
								MessageBox(hwnd, myStr, "Error",
										MB_OK | MB_ICONEXCLAMATION);
								break;
							}
							sprintf(myStr, "Conversion completed. File write to %s!", szDstFileName);
							SendMessage(hStatus, SB_SETTEXT, 0, (LPARAM)myStr);
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
							fclose(fp);
						}else{
							MessageBox(hwnd, "Error in saving path", "Error", 
									MB_OK | MB_ICONEXCLAMATION);
						}
						SendMessage(hStatus, SB_SETTEXT, 0, (LPARAM)"Path saved!");
					}
					break;
			}
			break;
		case WM_CHAR:
			{
				MessageBox(NULL, "WM_CHAR encountered in dialog", "trace", 0);
				if(wParam = '\t') {
					MessageBox(NULL, "Tab encountered in dialog", "trace", 0);
					//SendMessage(hwnd, WM_NEXTDLGCTL, 0L, 0L);
					return TRUE;
				}
			}
			break;
		case WM_NEXTDLGCTL:
			{
				char myStr[50];

				sprintf(myStr, "WM_NEXTDLGCTL in dialog");
				MessageBox(NULL, myStr, "trace", MB_OK);
			}
			break;
		default:
			return FALSE;
	}
	return TRUE;
}

/*========================================================================
 WndProc
 =========================================================================*/
/** \brief Process the main window command */
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		case WM_CREATE:
			/// create child window
			{
				g_hModelessDlgBox = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_FORMVIEW),
						hwnd, DialogBoxProc);
				if(g_hModelessDlgBox != NULL) {
					ShowWindow(g_hModelessDlgBox, SW_SHOW);
				} else {
					MessageBox(hwnd, "CreateDialog returned NULL", "Warning!",  
							MB_OK | MB_ICONEXCLAMATION);
				}
			}
			/// create status bar
			hStatus = CreateWindowEx(0, STATUSCLASSNAME, NULL,
				//WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP, 0, 0, 0, 0,
				WS_CHILD | WS_VISIBLE, 0, 0, 0, 0,
				hwnd, (HMENU)IDC_MAIN_STATUS, GetModuleHandle(NULL), NULL);
			SendMessage(hStatus, SB_SETTEXT, 0, (LPARAM)"Hi there :)");
			break;
			/// window size change
		case WM_SIZE: break;
		case WM_CHAR:
					  {
						  if(wParam = '\t') {
							  //MessageBox(NULL, "Tab encountered in main", "trace", 0);
							  SendMessage(g_hModelessDlgBox, WM_NEXTDLGCTL, 0L, 0L);
							  return TRUE;
						  }
					  }
					  break;
		case WM_NEXTDLGCTL: break;
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

/*========================================================================
 WinMain
 =========================================================================*/
/** \brief Main function */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
		LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;

	/// Registering the Window Class
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

	/// Creating the Window
	hwnd = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			g_szClassName,
			"Hexadecimal to Binary Converter",
			//WS_OVERLAPPEDWINDOW,
			WS_OVERLAPPED| WS_CAPTION | WS_SYSMENU,
			CW_USEDEFAULT, CW_USEDEFAULT, 505, 185,
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
		//if (g_hInfoDialogBox == 0 || !IsWindow(g_hInfoDialogBox) || !IsDialogMessage (g_hModelessDlgBox, &Msg)){
		if (!IsDialogMessage (g_hModelessDlgBox, &Msg)){
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
	}
	return Msg.wParam;
}

