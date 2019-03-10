#include "include.h"

LRESULT CALLBACK LAB6(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND Edit;
	switch (message)
	{
	case WM_CREATE: 				
		Edit = CreateWindow("Edit", NULL, WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_BORDER | WS_VSCROLL | ES_MULTILINE,
			10, 10, 480, 480, hWnd, (HMENU)ID_EDIT3, GetModuleHandle(NULL), NULL);
		break;

	case WM_COMMAND:
		switch (wParam)
		{
		case ID_FILE_CREATE:
			CreateNewFile(hWnd);
			break;

		case ID_FILE_OPEN:
			OpenFile(hWnd, Edit);
			break;

		case ID_FILE_SAVE:
			InitOpenDialog(hWnd, "Text file (.txt)\0*.txt\0");
			SaveFile(hWnd);
			break;

		case ID_FILE_DELETE:
			DeleteMyFile(hWnd);
			break;
		}
		break;

	case WM_DESTROY: 				
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK LAB7(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	static RECT rt;
	static HWND edit;
	static char buffer[64];
	int num;
	switch (message)
	{
	case WM_CREATE: 	
		rt = { 120, 10, 300, 25 };
		edit = CreateWindow("edit", NULL, WS_VISIBLE | WS_CHILD | EN_SETFOCUS, 10, 10, 100, 18, hWnd, NULL, GetModuleHandle(NULL), NULL);
		CreateWindow("button", "Фибоначи", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 10, 35, 100, 25, hWnd, (HMENU)ID_BUTTON3, GetModuleHandle(NULL), NULL);
		CreateWindow("button", "Факториал", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 10, 65, 100, 25, hWnd, (HMENU)ID_BUTTON4, GetModuleHandle(NULL), NULL);
		break;

	case WM_PAINT: 			
		hdc = BeginPaint(hWnd, &ps); 
		DrawText(hdc, buffer, -1, &rt, DT_SINGLELINE);
		EndPaint(hWnd, &ps);
		break;

	case WM_COMMAND:
		switch (wParam)
		{
		case ID_BUTTON3:
			GetWindowText(edit, buffer, 16);
			num = atoi(buffer);
			wsprintf(buffer, "%i", fibonach(num));
			InvalidateRect(hWnd, NULL, TRUE);
			break;

		case ID_BUTTON4:
			GetWindowText(edit, buffer, 16);
			num = atoi(buffer);
			wsprintf(buffer, "%i", factorial(num));

			InvalidateRect(hWnd, NULL, FALSE);
			break;
		}
		break;

	case WM_RBUTTONDOWN:
		hdc = GetDC(hWnd);
		rectangle_paint(hdc, { LOWORD(lParam), HIWORD(lParam) });
		ReleaseDC(hWnd, hdc);
		break;

	case WM_DESTROY: 				
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK LAB8(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	char *buffer;
	static HWND Edit[2];
	static int b_eax, b_edx, a_eax, a_edx, result;
	static bool click;

	switch (message)
	{
	case WM_CREATE:
		click = false;
		result = 0;
		CreateWindow("Button", "+", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
			125, 100, 75, 25, hWnd, (HMENU)ID_BUTTON5, NULL, NULL);
		CreateWindow("Button", "*", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
			25, 100, 75, 25, hWnd, (HMENU)ID_BUTTON6, NULL, NULL);
		Edit[0] = CreateWindow("Edit", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER,
			25, 25, 175, 25, hWnd, NULL, NULL, NULL);
		Edit[1] = CreateWindow("Edit", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER,
			25, 65, 175, 25, hWnd, NULL, NULL, NULL);
		_asm {
			mov b_eax, eax
			mov b_edx, edx
		}
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		print(hdc, { 220, 20 }, b_eax, b_edx, "Before: ");
		if (click) {
			buffer = new char[20];
			print(hdc, { 350, 20 }, a_eax, a_edx, "After: ");
			TextOut(hdc, 25, 135, buffer, wsprintf(buffer, "Result = %5d", result));
			delete[] buffer;
		}
		EndPaint(hWnd, &ps);
		break;

	case WM_COMMAND:
		switch (wParam)
		{
		case ID_BUTTON5: {
			int x, y;
			buffer = new char[20];
			click = true;
			GetWindowText(Edit[0], buffer, 20);
			x = atoi(buffer);
			GetWindowText(Edit[1], buffer, 20);
			y = atoi(buffer);
			delete[] buffer;
			_asm {
				mov eax, x
				mov edx, y
				add eax, edx
				mov result, eax

				mov a_eax, eax
				mov a_edx, edx
			}
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		case ID_BUTTON6: {
			int x, y;
			buffer = new char[20];
			click = true;
			GetWindowText(Edit[0], buffer, 20);
			x = atoi(buffer);
			GetWindowText(Edit[1], buffer, 20);
			y = atoi(buffer);
			delete[] buffer;
			_asm {
				mov eax, x
				mov edx, y
				mul edx
				mov result, eax

				mov a_eax, eax
				mov a_edx, edx
			}
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		}
		break;

	case WM_DESTROY:
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK LAB9(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static HWND Edit[3];
	char *first, *second;

	switch (message)
	{
	case WM_CREATE:
		CreateWindow("Button", "cpy", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
			160, 120, 75, 25, hWnd, (HMENU)ID_STRCPY, NULL, NULL);
		CreateWindow("Button", "cat", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
			60, 120, 75, 25, hWnd, (HMENU)ID_STRCAT, NULL, NULL);
		CreateWindow("Button", "len", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
			160, 150, 75, 25, hWnd, (HMENU)ID_STRLEN, NULL, NULL);
		CreateWindow("Button", "cmp", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
			60, 150, 75, 25, hWnd, (HMENU)ID_STRCMP, NULL, NULL);
		Edit[0] = CreateWindow("Edit", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER,
			60, 25, 175, 25, hWnd, NULL, NULL, NULL);
		Edit[1] = CreateWindow("Edit", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER,
			60, 55, 175, 25, hWnd, NULL, NULL, NULL);
		Edit[2] = CreateWindow("Static", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER,
			60, 85, 175, 25, hWnd, NULL, NULL, NULL);
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		first = new char[64];
		TextOut(hdc, 5, 30, "Str 1:", 6);
		TextOut(hdc, 5, 60, "Str 2:", 6);
		TextOut(hdc, 5, 90, "Result:", 7);
		EndPaint(hWnd, &ps);
		break;

	case WM_COMMAND:
		switch (wParam)
		{
		case ID_STRCPY: {
			first = new char[256];
			second = new char[256];
			GetWindowText(Edit[0], first, 255);
			GetWindowText(Edit[1], second, 255);
			_strcpy(first, second);
			SetWindowText(Edit[2], first);
			delete[] first;
			delete[] second;
			break;
		}

		case ID_STRCAT: {
			first = new char[512];
			second = new char[256];
			GetWindowText(Edit[0], first, 255);
			GetWindowText(Edit[1], second, 255);
			_strcat(first, second);
			SetWindowText(Edit[2], first);
			delete[] first;
			delete[] second;
			break;
		}

		case ID_STRLEN: {
			first = new char[255];
			second = new char[15];
			GetWindowText(Edit[0], first, 255);
			_itoa(_strlen(first), second, 10);
			SetWindowText(Edit[2], second);
			delete[] first;
			delete[] second;
			break;
		}

		case ID_STRCMP: {
			first = new char[256];
			second = new char[256];
			GetWindowText(Edit[0], first, 255);
			GetWindowText(Edit[1], second, 255);
			bool cmp = _strcmp(first, second);
			delete[] first;
			delete[] second;
			first = new char[5];
			_itoa(cmp, first, 10);
			SetWindowText(Edit[2], first);
			delete[] first;
			break;
		}
		}
		break;

	case WM_DESTROY:
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}