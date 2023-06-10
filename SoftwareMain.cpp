#include <windows.h>
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
			SearchSong(hWnd);
			break;
		case OnSaveFile:
			if (GetSaveFileNameA(&ofn)) { SaveData(filename); }
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
	AppendMenu(SubMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(SubMenu, MF_STRING, OnExitSoftware, L"Exit");

	AppendMenu(RootMenu, MF_POPUP, (UINT_PTR)SubMenu, L"File");
	AppendMenu(RootMenu, MF_STRING, (UINT_PTR)SubMenu, L"Help");
	SetMenu(hWnd, RootMenu);

}

void MainWndAddWidgets(HWND hWnd) {

	hStaticControl = CreateWindowA("static", "Welcome to DKAudioTeka! \n (Прежде чем ввести название песни, нажмите кнопку Clear)", WS_VISIBLE | WS_CHILD | ES_CENTER, 200, 5, 280, 48, hWnd, NULL, NULL, NULL);
	hEditControl = CreateWindowA("edit", "Введите название песни:", WS_VISIBLE | WS_CHILD | ES_MULTILINE | WS_VSCROLL | ES_CENTER, 5, 60, 250, 50, hWnd, NULL, NULL, NULL);
	hStaticControl2 = CreateWindowA("static", "", WS_VISIBLE | WS_CHILD | ES_CENTER, 5, 115, 475, 60, hWnd, NULL, NULL, NULL);

	CreateWindowA("button", "Clear", WS_VISIBLE | WS_CHILD | ES_CENTER, 5, 5, 120, 30, hWnd, (HMENU)OnClearField, NULL, NULL);
	CreateWindowA("button", "Search", WS_VISIBLE | WS_CHILD | ES_CENTER, 130, 5, 60, 30, hWnd, (HMENU)OnReadField, NULL, NULL);

}
void SaveData(LPCSTR path) {
	HANDLE FileToSave = CreateFileA(
		path,
		GENERIC_WRITE,
		0,
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	SetFilePointer(FileToSave, 0, NULL, FILE_END);
	int saveLenth = GetWindowTextLength(hEditControl) + 1;
	char* data = new char[saveLenth];

	saveLenth = GetWindowTextA(hEditControl, data, saveLenth);

	DWORD bytesIterated;
	WriteFile(FileToSave, data, saveLenth, &bytesIterated, NULL);

	CloseHandle(FileToSave);
	delete[] data;
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
	ofn.lpstrInitialDir = "base.txt";
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

}


void SearchSong(HWND hWnd) {
	string query; // слово, которое ищем
	char Buffer[TextBufferSize]; // буфер для чтения из текстового поля
	char Buffer2[TextBufferSize];
	GetWindowTextA(hEditControl, Buffer2, TextBufferSize); // считываем текст из текстового поля в буфер

	FILE* file;
	errno_t err = fopen_s(&file, "G:\\Данила\\С++\\6 practic\\Ex 2\\Курсач\\base.txt", "r"); // открываем файл для чтения
	if (err != 0) { // проверяем, удалось ли открыть файл
		SetWindowTextA(hStaticControl2, "Ошибка открытия файла.");
		return;
	}

	bool found = false; // флаг для проверки, найдено ли слово
	while (fgets(Buffer, TextBufferSize, file)) { // читаем строки из файла
		if (std::string(Buffer).find(Buffer2) != std::string::npos) { // ищем слово в строке
			found = true;
			break;
		}
	}
	fclose(file); // закрываем файл

	if (found) { // слово найденоее в буфер
		SetWindowTextA(hStaticControl2, Buffer);
	}
	else { // слово не найдено
		SetWindowTextA(hStaticControl2, "Песня не найдена.");
	}
}

