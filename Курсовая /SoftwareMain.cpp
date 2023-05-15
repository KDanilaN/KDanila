#include <Windows.h> 
#include <string>
#include "SoftwareDefinitions.h"
#include <fstream>
#include <iostream>
using namespace std;


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {

	WNDCLASS SoftWareMainClass = NewWindowClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hInst, LoadIcon(NULL, IDI_QUESTION),
		L"MainWndClass", SoftwareMainProcedure);

	if (!RegisterClassW(&SoftWareMainClass)) { return -1; }
	MSG SoftwareMainMessage = { 0 };

	CreateWindow(L"MainWndClass", L"DKAudioTeka", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 250, NULL, NULL, NULL, NULL);

	while (GetMessage(&SoftwareMainMessage, NULL, NULL, NULL)) {
		TranslateMessage(&SoftwareMainMessage);
		DispatchMessage(&SoftwareMainMessage);
	}
	return 0;

}

WNDCLASS NewWindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure) {
	WNDCLASS NWC = { 0 };

	NWC.hIcon = Icon;
	NWC.hCursor = Cursor;
	NWC.hInstance = hInst;
	NWC.lpszClassName = Name;
	NWC.hbrBackground = (HBRUSH)(COLOR_WINDOW + 23);
	NWC.lpfnWndProc = Procedure;

	return NWC;
}

LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {

	switch (msg)
	{
	case WM_COMMAND:
		switch (wp) {
		case OnClearField:
			SetWindowTextA(hEditControl, "");
			break;
		case OnReadField:
			GetWindowTextA(hEditControl, Buffer, TextBufferSize);
			SetWindowTextA(hStaticControl2, Buffer);
			break;
		case OnSaveFile:
			if (GetSaveFileNameA(&ofn)) { SaveData(filename); }
			break;
		case OnLoadFile:
			if (GetOpenFileNameA(&ofn)) { LoadData(filename); }
			break;
		case OnExitSoftware:
			PostQuitMessage(0);
			break;
		default: break;
		}
		break;
	case WM_CREATE:
		MainWndAddMenus(hWnd);
		MainWndAddWidgets(hWnd);
		SetOpenFileParams(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default: return DefWindowProc(hWnd, msg, wp, lp);
	}
}

void MainWndAddMenus(HWND hWnd) {
	HMENU RootMenu = CreateMenu();

	HMENU SubMenu = CreateMenu();

	AppendMenu(SubMenu, MF_STRING, OnClearField, L"Clear");
	AppendMenu(SubMenu, MF_STRING, OnSaveFile, L"Save");
	AppendMenu(SubMenu, MF_STRING, OnLoadFile, L"Load");
	AppendMenu(SubMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(SubMenu, MF_STRING, OnExitSoftware, L"Exit");

	AppendMenu(RootMenu, MF_POPUP, (UINT_PTR)SubMenu, L"File");
	AppendMenu(RootMenu, MF_STRING, (UINT_PTR)SubMenu, L"Help");
	SetMenu(hWnd, RootMenu);

}

void MainWndAddWidgets(HWND hWnd) {

	hStaticControl = CreateWindowA("static", "Welcome to DKAudioTeka! \n (������ ��� ������� �������� �����, ������� ������ Clear)", WS_VISIBLE | WS_CHILD | ES_CENTER, 200, 5, 280, 48, hWnd, NULL, NULL, NULL);
	hEditControl = CreateWindowA("edit", "������� �������� �����:", WS_VISIBLE | WS_CHILD | ES_MULTILINE | WS_VSCROLL | ES_CENTER, 5, 60, 250, 50, hWnd, NULL, NULL, NULL);
	hStaticControl2 = CreateWindowA("static", "", WS_VISIBLE | WS_CHILD | ES_CENTER, 5,  115, 475, 60, hWnd, NULL, NULL, NULL);

	CreateWindowA("button", "Clear", WS_VISIBLE | WS_CHILD | ES_CENTER, 5, 5, 120, 30, hWnd,(HMENU)OnClearField, NULL, NULL);
	CreateWindowA("button", "Search", WS_VISIBLE | WS_CHILD | ES_CENTER, 130, 5, 60, 30, hWnd, (HMENU)OnReadField, NULL, NULL);

} 
void SaveData(LPCSTR path) {
	HANDLE FileToSave = CreateFileA(
		path,
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	int saveLenth = GetWindowTextLength(hEditControl)+1;
	char* data = new char[saveLenth];

	saveLenth = GetWindowTextA(hEditControl, data, saveLenth);

	DWORD bytesIterated;
	WriteFile(FileToSave, data, saveLenth, &bytesIterated, NULL);

	CloseHandle(FileToSave);
	delete[] data;
}
void LoadData(LPCSTR path) {
	HANDLE FileToLoad = CreateFileA(
		path,
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	DWORD bytesIterated;
	ReadFile(FileToLoad, Buffer, TextBufferSize, &bytesIterated, NULL);

	SetWindowTextA(hEditControl, Buffer);

	CloseHandle(FileToLoad);

}
void SetOpenFileParams(HWND hWnd) {
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = filename;
	ofn.nMaxFile = sizeof(filename);
	ofn.lpstrFilter = "*.txt";
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = "G:/������/�++/������/output.txt";
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

}
