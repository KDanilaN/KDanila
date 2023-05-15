#pragma once

#define OnMenuAction1   1
#define OnMenuAction2   2
#define OnMenuAction3   3
#define OnExitSoftware  4
#define OnClearField    5
#define OnReadField     6
#define OnSaveFile      7
#define OnLoadFile      8
#define OnSearchFile    9

#define TextBufferSize  256

char Buffer[TextBufferSize];
char SearchBuffer[TextBufferSize];
char ResultBuffer[TextBufferSize];


HWND hStaticControl;
HWND hEditControl; 
HWND hStaticControl2;

char filename[260];
OPENFILENAMEA ofn;

LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
WNDCLASS NewWindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Prodecude);

void MainWndAddMenus(HWND hWnd);
void MainWndAddWidgets(HWND hWnd);
void SetOpenFileParams(HWND hWnd);
void SaveData(LPCSTR path);
void LoadData(LPCSTR path);
void SearchSong(HWND hWnd);