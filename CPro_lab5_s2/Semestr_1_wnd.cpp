#include "include.h"

BOOL CALLBACK DlgExitAnswer(HWND hDlg, UINT msg, WPARAM wParm, LPARAM lParam) {
	static HWND *hWnd;
	switch (msg)
	{
	case WM_INITDIALOG:
		hWnd = (HWND *)lParam;
		return TRUE;

	case WM_COMMAND:
		if (LOWORD(wParm) == IDOK) { //закрытие формы
			Shell_NotifyIcon(NIM_DELETE, &tray);
			ShowWindow(*hWnd, SW_HIDE);
		}
		//если нажать нет, идет закрытие даилога
		EndDialog(hDlg, LOWORD(wParm));

		return FALSE;
		break;

	}
	return FALSE;
}

BOOL CALLBACK DlgPloc(HWND hDlg, UINT msg, WPARAM wParm, LPARAM lParam) {
	switch (msg)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		if (LOWORD(wParm) == IDOK || LOWORD(wParm) == IDCANCEL || LOWORD(wParm) == IDINFO) {
			//при нажатии на любую кнопку закрывается диалог
			EndDialog(hDlg, LOWORD(wParm));
			return TRUE;
		}

	}
	return FALSE;
}

BOOL CALLBACK DlgAdditional(HWND hDlg, UINT msg, WPARAM wParm, LPARAM lParam) {
	switch (msg)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		if (LOWORD(wParm) == IDOK) {

			HWND hEdit1 = GetDlgItem(hDlg, IDC_EDIT1); // инициализруем поля ввода
			CHAR buffer[256] = { 0 };
			SendMessage(hEdit1, WM_GETTEXT, (WPARAM)255, (LPARAM)buffer); //заполняем буфер данными которые ввели в поле
						//(откуда,что,доп информация,куда сохранено)
			MessageBox(hDlg, buffer, "Зачитываю!", MB_OK);//воспроизводим текст из буфера
			return TRUE;
		}
		else if (LOWORD(wParm) == IDCANCEL) {
			MessageBox(hDlg, "Осторожно, окно закрывается", "Exit", MB_OK);
			EndDialog(hDlg, LOWORD(wParm));
			return TRUE;
		}
	}
	return FALSE;
}

LRESULT CALLBACK LAB1(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HMENU hMenu;
	PAINTSTRUCT ps;//графический вывод
	HDC hdc;//назначения вывода
	RECT rt;//область окна для рисования
	switch (message)
	{
	case WM_CREATE:// Сообщение приходит при создании окна
		trayInit(hWnd, tray); //инициализация иконки в трее
		Shell_NotifyIcon(NIM_ADD, &tray);
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_ABOUT_ABOUT: //пункт меню "о программе"
			DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDHELP), hWnd, (DLGPROC)DlgPloc); // вызов диалогового окна( указатель приложения, ресурс диалогового окна,дескриптор окна, проверка кнопок)
			break;
		case ID_CHANGE_ICON1: //изменение иконки окна и трея
			tray.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));// загружаем иконку в трей
			Shell_NotifyIcon(NIM_MODIFY, &tray);//отображаем иконку в трей
			SetClassLong(hWnd, GCLP_HICON, (LONG)LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1)));//установка (окно, что нужно изменить, выгрузка из реусрсов картинки)

			break;
		case ID_CHANGE_ICON2:
			tray.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON3));

			SetClassLong(hWnd, GCLP_HICON, (LONG)LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON3)));
			Shell_NotifyIcon(NIM_MODIFY, &tray);
			break;
		case ID_CHANGE_ICON3:
			tray.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON5));
			Shell_NotifyIcon(NIM_MODIFY, &tray);
			SetClassLong(hWnd, GCLP_HICON, (LONG)LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON5)));
			break;
		case ID_ABOUT_ADITIONAL:
			DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(ID_ADDITIONAL), hWnd, (DLGPROC)DlgAdditional);
			break;
		case ID_GETNEWSTYLE_GETNEW:
			hMenu = LoadMenu(GetModuleHandle(NULL), MAKEINTRESOURCE(IDR_MENU2)); //загружаем иной ресурс окна
			SetMenu(hWnd, hMenu);//устанавливаем новое меню
			break;
		case ID_FILE_GETBACK:
			hMenu = LoadMenu(GetModuleHandle(NULL), MAKEINTRESOURCE(IDR_MENU1));//возвращаем исходное меню
			SetMenu(hWnd, hMenu);
			break;

		}
		break;
	case WM_LBUTTONDBLCLK://ЛКМ
		MessageBox(hWnd, "Mouse Click!", "click!", MB_OK); //вывод сообщения при 2 нажатии на лкм
		break;

	case WM_PAINT:  // Перерисовать окно
		hdc = BeginPaint(hWnd, &ps);	// Начать графический вывод
		GetClientRect(hWnd, &rt); // Область окна для рисования
		DrawText(hdc, "КИУКИ-17-8 Дудка,Литвинова,Ткачук", -1, &rt, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		EndPaint(hWnd, &ps);	// Закончить графический вывод
		break;

	case WM_CLOSE:
		DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDABORTORNO), hWnd, (DLGPROC)DlgExitAnswer, (LPARAM)&hWnd);
		break;

	case WM_DESTROY: // Завершение работы
		Shell_NotifyIcon(NIM_DELETE, &tray);
		ShowWindow(hWnd, SW_HIDE);
		break;

	default:
		// Обработка сообщений, которые не обработаны пользователем
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK LAB2(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	RECT rt;
	TEXTMETRIC tm;
	PAINTSTRUCT ps;

	char buff[100];
	hdc = GetDC(hWnd);
	int xMouse, yMouse;
	switch (message)
	{
	case WM_CREATE: // Сообщение приходит при создании окна
		break;

	case WM_PAINT:  // Перерисовать окно
		GetTextMetrics(hdc, &tm);
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 20, 20, buff, wsprintf(buff, "Ширина монитора в пикселях %5d", GetSystemMetrics(SM_CXSCREEN)));
		TextOut(hdc, 20, 40, buff, wsprintf(buff, "Высота монитора в пикселях %5d", GetSystemMetrics(SM_CYSCREEN)));
		TextOut(hdc, 20, 60, buff, wsprintf(buff, "Ширина монитора в мм %5d", GetDeviceCaps(hdc, HORZSIZE)));
		TextOut(hdc, 20, 80, buff, wsprintf(buff, "Высота монитора в мм %5d", GetDeviceCaps(hdc, VERTSIZE)));
		TextOut(hdc, 20, 100, buff, wsprintf(buff, "Ширина горизонтальной полосы прокрутки %5d", GetSystemMetrics(SM_CXHSCROLL)));
		TextOut(hdc, 20, 120, buff, wsprintf(buff, "Высота горизонтальной полосы прокрутки %5d", GetSystemMetrics(SM_CYHSCROLL)));
		TextOut(hdc, 20, 140, buff, wsprintf(buff, "Высота символа %5d", tm.tmHeight));
		TextOut(hdc, 20, 160, buff, wsprintf(buff, "Высота пространства над символом  %5d", tm.tmInternalLeading));
		EndPaint(hWnd, &ps);
		break;
	case WM_MOUSEMOVE:
		xMouse = LOWORD(lParam);
		yMouse = HIWORD(lParam);
		TextOut(hdc, 20, 180, buff, wsprintf(buff, "Положение мышки по Х = %5d", xMouse));
		TextOut(hdc, 20, 200, buff, wsprintf(buff, "Положение мышки по Y = %5d", yMouse));
		break;
	case WM_LBUTTONDOWN:
		SetMapMode(hdc, MM_ANISOTROPIC);
		SetWindowExtEx(hdc, 500, -500, NULL);
		SetViewportOrgEx(hdc, LOWORD(lParam), HIWORD(lParam), NULL);
		break;
	case WM_RBUTTONDOWN:
		SetCapture(hWnd);
		while (!WM_RBUTTONUP) {
			xMouse = LOWORD(lParam);
			yMouse = HIWORD(lParam);
		}
		break;
	case WM_KEYDOWN:
		SetCapture(hWnd);
		POINT home;
		GetCursorPos(&home);
		switch (wParam)
		{
		case VK_LEFT:
			SetCursorPos(home.x - 1, home.y);
			break;
		case VK_RIGHT:
			SetCursorPos(home.x + 1, home.y);
			break;
		case VK_UP:
			SetCursorPos(home.x, home.y - 1);
			break;
		case VK_DOWN:
			SetCursorPos(home.x, home.y + 1);
			break;
		}
		ReleaseCapture();
		break;

	case WM_DESTROY: // Завершение работы
		ShowWindow(hWnd, SW_HIDE);
		break;
	default:
		//Обробка повідомлень, які не оброблені користувачем
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK LAB3(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rt[6] = { 0 };
	RECT winRT;
	HBRUSH brush;
	static COLORREF BckColor[6], TextColor[6];
	int x, y;
	switch (message)
	{
	case WM_CREATE:
		break;

	case WM_PAINT:
		GetClientRect(hWnd, &winRT);
		brush = CreateSolidBrush(RGB(255, 255, 255));
		SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (LONG)brush);
		hdc = BeginPaint(hWnd, &ps);
		rt[1].top = winRT.top;
		rt[1].left = winRT.right / 2;
		rt[0].top = winRT.top;
		rt[0].left = winRT.left;
		rt[0].right = rt[1].left;
		rt[0].bottom = winRT.bottom / 2;
		rt[1].right = winRT.right;
		rt[2].top = rt[0].bottom;
		rt[1].bottom = winRT.bottom / 2;
		rt[2].left = rt[0].left;
		rt[2].right = rt[0].right;
		rt[2].bottom = winRT.bottom;
		rt[3].top = rt[2].top;
		rt[3].left = rt[1].left;
		rt[3].right = winRT.right;
		rt[3].bottom = winRT.bottom;

		if (rt[3].bottom - rt[3].top > 300 || rt[0].bottom - rt[0].top > 300) {
			rt[0].bottom = rt[1].bottom = 300;
			rt[4] = { winRT.left, 600, winRT.right, winRT.bottom };
			rt[2].top = rt[3].top = 300;
			rt[2].bottom = rt[3].bottom = 600;
			FillRect(hdc, &rt[4], HBRUSH(CreateSolidBrush(RGB(255, 255, 0))));
		}
		if (rt[3].right - rt[3].left > 600 || rt[0].right - rt[0].left > 600) {
			rt[1].right = rt[3].right = 1200;
			rt[1].left = rt[3].left = 600;
			rt[5] = { 1200, winRT.top, winRT.right, rt[2].bottom };
			rt[0].right = rt[2].right = 600;
			FillRect(hdc, &rt[5], HBRUSH(CreateSolidBrush(RGB(255, 0, 255))));
		}
		FillRect(hdc, &rt[0], HBRUSH(CreateHatchBrush(HS_DIAGCROSS, RGB(255, 0, 0))));
		FillRect(hdc, &rt[1], HBRUSH(CreateHatchBrush(HS_CROSS, RGB(0, 255, 0))));
		FillRect(hdc, &rt[2], HBRUSH(CreateHatchBrush(HS_FDIAGONAL, RGB(0, 0, 255))));
		FillRect(hdc, &rt[3], HBRUSH(CreateHatchBrush(HS_DIAGCROSS, RGB(0, 0, 0))));
		for (int i = 0; i < 6; i++) {
			SetTextColor(hdc, TextColor[i]);
			SetBkColor(hdc, BckColor[i]);
			DrawText(hdc, "Random text", -1, &rt[i], DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		}

		EndPaint(hWnd, &ps);
		break;
	case WM_MOUSEMOVE:
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		for (int i = 1; i <= 6; i++) {
			BckColor[i - 1] = RGB(x * i * i, y * i * i, x + y + i * i);
			TextColor[i - 1] = RGB(y * i, x * i, x - y + i * i);
		}
		break;

	case WM_DESTROY:
		ShowWindow(hWnd, SW_HIDE);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK LAB4(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND ListBox;
	static HWND hButton[2];//объекты
	static HWND HScroll, VScroll;
	char fileName[200] = { 0 };
	static int hpos, vpos;
	switch (message)
	{
	case WM_CREATE: // Сообщение приходит при создании окна
		hButton[0] = CreateWindow("Button", "Text", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
			50, 20, 150, 50, hWnd, (HMENU)ID_BUTTON1, NULL, NULL);
		hButton[1] = CreateWindow("Button", "Binary", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
			300, 20, 150, 50, hWnd, (HMENU)ID_BUTTON2, NULL, NULL);
		ListBox = CreateWindow("listbox", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER,
			10, 80, 444, 354, hWnd, (HMENU)ID_LISTBOX1, NULL, NULL);
		VScroll = CreateWindow("scrollbar", NULL, WS_VISIBLE | WS_CHILD | SBS_VERT | WS_BORDER,
			455, 80, 20, 350, hWnd, (HMENU)ID_VSCROLL, NULL, NULL);
		HScroll = CreateWindow("scrollbar", NULL, WS_VISIBLE | WS_CHILD | SBS_HORZ | WS_BORDER,
			10, 430, 465, 20, hWnd, (HMENU)ID_HSCROLL, NULL, NULL);
		SetScrollRange(HScroll, SB_CTL, 0, 1000, TRUE);
		SetDlgItemInt(ListBox, ID_LISTBOX1, 0, FALSE);
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_BUTTON1:
			ReadFromFile(ListBox, VScroll, hWnd, fileName);
			break;
		case ID_BUTTON2:
			ReadFromFile(ListBox, VScroll, hWnd, fileName, true);
			break;
		}
		break;
	case WM_VSCROLL:
		switch (LOWORD(wParam))
		{
		case	SB_LINEUP:
			vpos += 10;
			SetScrollPos(VScroll, SB_CTL, vpos, TRUE);
			break;
		case     SB_PAGEUP:
			vpos += 10;
			SetScrollPos(VScroll, SB_CTL, vpos, TRUE);
			break;
		case     SB_THUMBTRACK:
			vpos += 10;
			SetScrollPos(VScroll, SB_CTL, vpos, TRUE);
			break;
		case     SB_THUMBPOSITION:
			vpos -= 10;
			SetScrollPos(VScroll, SB_CTL, vpos, TRUE);
			break;
		case     SB_PAGEDOWN:
			vpos -= 10;
			SetScrollPos(VScroll, SB_CTL, vpos, TRUE);
			break;
		case     SB_LINEDOWN:
			vpos -= 10;
			SetScrollPos(VScroll, SB_CTL, vpos, TRUE);
			break;
		}
		break;
	case WM_HSCROLL:
		switch (LOWORD(wParam))
		{
		case	SB_LINEUP:
			hpos += 10;
			SetScrollPos(HScroll, SB_CTL, hpos, TRUE);
			break;
		case     SB_PAGEUP:
			hpos += 10;
			SetScrollPos(HScroll, SB_CTL, hpos, TRUE);
			break;
		case     SB_THUMBTRACK:
			hpos += 10;
			SetScrollPos(HScroll, SB_CTL, hpos, TRUE);
			SetDlgItemInt(hWnd, ID_LISTBOX1, hpos, FALSE);
			break;
		case     SB_THUMBPOSITION:
			hpos -= 10;
			SetScrollPos(HScroll, SB_CTL, hpos, TRUE);
			break;
		case     SB_PAGEDOWN:
			hpos -= 10;
			SetScrollPos(HScroll, SB_CTL, hpos, TRUE);
			break;
		case     SB_LINEDOWN:
			hpos -= 10;
			SetScrollPos(HScroll, SB_CTL, hpos, TRUE);
			break;
		}
		break;

	case WM_DESTROY: // Завершение работы
		ShowWindow(hWnd, SW_HIDE);
		break;
	default:
		// Обработка сообщений, которые не обработаны пользователем
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK LAB5(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static DWORD ExitCode;
	switch (message) {
	case WM_CREATE: //Повідомлення приходить при створенні вікна
		Text[0] = CreateWindow("Edit", NULL, WS_VISIBLE | ES_MULTILINE | ES_READONLY | WS_BORDER | WS_CHILD | WS_VSCROLL,
			0, 0, 250, 250, hWnd, (HMENU)ID_EDIT1, GetModuleHandle(NULL), NULL);
		Text[1] = CreateWindow("Edit", NULL, WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_READONLY | WS_BORDER | WS_VSCROLL,
			250, 0, 250, 250, hWnd, (HMENU)ID_EDIT2, GetModuleHandle(NULL), NULL);
		Text[2] = CreateWindow("Static", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER,
			250, 250, 250, 250, hWnd, (HMENU)ID_LABEL1, GetModuleHandle(NULL), NULL);
		ThreadStart(hWnd);
		SetClassLong(hWnd, GCL_HBRBACKGROUND, COLOR_WINDOW);
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));
		break;

	case WM_COMMAND:
		switch (wParam) {
		case ID_OPEN:
			EnableMenuItem(GetMenu(hWnd), ID_OPEN, MF_DISABLED);
			CreateProcess(TEXT("C:\\Windows\\system32\\notepad.exe"),
				NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi);
			break;

		case ID_CLOSE:
			GetExitCodeProcess(pi.hProcess, &ExitCode);
			if (ExitCode != STILL_ACTIVE)
				MessageBox(hWnd, "Процесс еще не запущен!", "Дождитесь запуска процесса", MB_OK);
			else {
				EnableMenuItem(GetMenu(hWnd), ID_OPEN, MF_ENABLED);
				TerminateProcess(pi.hProcess, -1);
				CloseHandle(pi.hThread);
			}
			break;
		case ID_DESTROY:
			closeProgram(hWnd, ExitCode);
			break;
		case ID_THREED_RESUME:
			EnableMenuItem(GetMenu(hWnd), ID_THREED_RESUME, MF_DISABLED);
			EnableMenuItem(GetMenu(hWnd), ID_THREED_STOP, MF_ENABLED);
			ThreadStart(hWnd);
			break;
		case ID_THREED_STOP:
			EnableMenuItem(GetMenu(hWnd), ID_THREED_RESUME, MF_ENABLED);
			EnableMenuItem(GetMenu(hWnd), ID_THREED_STOP, MF_DISABLED);
			ThreadStop();
			break;
		}
		break;
	case WM_DESTROY: 				//Завершення роботи
		closeProgram(hWnd, ExitCode);
		break;
	default:
		//Обробка повідомлень, які не оброблені користувачем
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}
