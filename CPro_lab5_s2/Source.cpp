#include "include.h"

int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow)
{
	OpenLab *laba = nullptr;
	_create_lab(laba, MAINFUNC, "Lab10", "Lab10", { 10, 30, 400, 300 }, LoadMenu(GetModuleHandle(NULL), MAKEINTRESOURCE(IDR_MENU3)));
	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	delete laba;
	return msg.wParam;
}

LRESULT CALLBACK MAINFUNC(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static OpenLab *lab;
	switch (message)
	{
	case WM_CREATE:
		break;

	case WM_COMMAND:
		switch (wParam) 
		{
		case ID_MENU_LAB1:
			_create_lab(lab, LAB1, "Lab1", "Lab1", { 10, 30, 400, 300 }, LoadMenu(GetModuleHandle(NULL), MAKEINTRESOURCE(IDR_MENU1)));
			break;
		case ID_MENU_LAB2:
			_create_lab(lab, LAB2, "Lab2", "Lab2", { CW_USEDEFAULT, CW_USEDEFAULT, 600, 350 });
			break;
		case ID_MENU_LAB3:
			_create_lab(lab, LAB3, "Lab3", "Lab3", { 120, 120, 520, 540 });
			break;
		case ID_MENU_LAB4:
			_create_lab(lab, LAB4, "Lab4", "Lab4", { 250, 250, 480, 495 });
			break;
		case ID_MENU_LAB5:
			_create_lab(lab, LAB5, "Lab5", "Lab5", { 100, 100, 515, 550, }, LoadMenu(GetModuleHandle(NULL), MAKEINTRESOURCE(IDR_MENU4)));
			break;
		case ID_MENU_LAB6:
			_create_lab(lab, LAB6, "Lab6", "Lab6", { 250, 250, 517, 562}, LoadMenu(GetModuleHandle(NULL), MAKEINTRESOURCE(IDR_MENU5)));
			break;
		case ID_MENU_LAB7:
			_create_lab(lab, LAB7, "Lab7", "Lab7", { CW_USEDEFAULT, CW_USEDEFAULT, 350, 150 }, NULL, GRAY_BRUSH);
			break;
		case ID_MENU_LAB8:
			_create_lab(lab, LAB8, "Lab8", "Lab8", { 200, 200, 600, 220 }, NULL, GRAY_BRUSH);
			break;
		case ID_MENU_LAB9:
			_create_lab(lab, LAB9, "Lab9", "Lab9", { 200, 200, 300, 250 }, NULL, GRAY_BRUSH);
			break;
		case ID_ABOUT_LAB:
			DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(ID_DLG_ABOUT), hWnd, (DLGPROC)INFODLG);
			break;
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

BOOL CALLBACK INFODLG(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		return true;

	case WM_COMMAND:
		switch (wParam)
		{
		case IDOK:
			EndDialog(hDlg, LOWORD(wParam));
			break;

		case IDCANCEL:
			EndDialog(hDlg, LOWORD(wParam));
			break;

		case ID_RESPECT:
			MessageBox(hDlg, "Thank you for you respect!", "RESPECT!", MB_OK);
			break;
		}
	}
	return false;
}
