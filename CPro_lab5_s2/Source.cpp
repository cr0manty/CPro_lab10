#include "include.h"

int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow)
{
	OpenLab lab(MAINFUNC, "Lab10", "Lab10", { 10, 30, 400, 300 }, LoadMenu(GetModuleHandle(NULL), MAKEINTRESOURCE(IDR_MENU3)));
	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
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
		if (lab)
			delete lab;

		switch (wParam) 
		{
		case ID_MENU_LAB1:
			lab = new OpenLab(LAB1, "Lab1", "Lab1", { 10, 30, 400, 300 }, LoadMenu(GetModuleHandle(NULL), MAKEINTRESOURCE(IDR_MENU1)));
			break;
		case ID_MENU_LAB2:
			lab = new OpenLab(LAB2, "Lab2", "Lab2", { CW_USEDEFAULT, CW_USEDEFAULT, 600, 350 });
			break;
		case ID_MENU_LAB3:
			lab = new OpenLab(LAB3, "Lab3", "Lab3", { 120, 120, 520, 540 });
			break;
		case ID_MENU_LAB4:
			lab = new OpenLab(LAB4, "Lab4", "Lab4", { 250, 250, 500, 500 });
			break;
		case ID_MENU_LAB5:
			lab = new OpenLab(LAB5, "Lab5", "Lab5", { 100, 100, 515, 550, }, LoadMenu(GetModuleHandle(NULL), MAKEINTRESOURCE(IDR_MENU4)));
			break;
		case ID_MENU_LAB6:
			lab = new OpenLab(LAB6, "Lab6", "Lab6", { CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT }, NULL, GRAY_BRUSH);
			break;
		case ID_MENU_LAB7:
			lab = new OpenLab(LAB7, "Lab7", "Lab7", { 200, 200, 490, 220 }, NULL, GRAY_BRUSH);
			break;
		case ID_MENU_LAB8:
			lab = new OpenLab(LAB8, "Lab8", "Lab8", { 200, 200, 300, 250 }, NULL, GRAY_BRUSH);
			break;
		case ID_MENU_LAB9:
			//lab = new OpenLab(LAB9, "Lab9", "Lab9", { 400, 30, 100, 300 });
			break;
		case ID_ABOUT_LAB:
			DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(ID_DLG_ABOUT), hWnd, (DLGPROC)INFODLG);
			break;
		}
		break;

	case WM_DESTROY: 
		if (lab)
			delete lab;

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
