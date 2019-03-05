#include "include.h"

void trayInit(HWND hWnd, NOTIFYICONDATA &tray)
{
	tray.cbSize = sizeof(NOTIFYICONDATA);//установка размера
	tray.hWnd = hWnd; //указать окно
	tray.uFlags = NIF_ICON;//типо который будет в трее(только иконка)
	tray.hIcon = LoadIcon(NULL, IDI_APPLICATION);//назначаем иконку
}

BOOL InitOpenDialog(OPENFILENAME &ofn, HWND hWnd, const char *_type, char * fileName)
{
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = fileName;
	ofn.nMaxFile = sizeof(fileName);
	ofn.lpstrFilter = _type;
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	return TRUE;
}

void ThreadStart(HWND hWnd)
{
	HDC hdc;
	hdc = GetDC(hWnd);

	//создание 4 потоков
	HANDLE thread[4];
	thread[0] = CreateThread(NULL, 0, thread1, NULL, 0, &threadID[0]);
	thread[1] = CreateThread(NULL, 0, thread2, NULL, 0, &threadID[1]);
	thread[2] = CreateThread(NULL, 0, thread3, hdc, 0, &threadID[2]); // hdc - параметр передающийся в поток
	thread[3] = CreateThread(NULL, 0, thread4, NULL, 0, &threadID[3]);
}

void ThreadStop()
{
	//посылаем 4 сообщения в потоки которые прервут выполнение цикла
	for (int i = 0; i < 4; i++)
		PostThreadMessage(threadID[i], WM_QUIT, 0, 0);
}

unsigned long long Fibonacci_nums(unsigned long long n)
{
	if (n < 2) return n;
	return Fibonacci_nums(n - 1) + Fibonacci_nums(n - 2);
}

DWORD WINAPI thread1(LPVOID)
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	static int sequence = 0;
	while (true) {
		if (PeekMessage(&msg, NULL, WM_QUIT, WM_QUIT, PM_REMOVE))
			break;

		char buffer[20];
		int EditTextlen = GetWindowTextLength(Text[0]);
		wsprintf(buffer, "%i", sequence++);

		SendMessage(Text[0], EM_SETSEL, EditTextlen, EditTextlen);
		SendMessage(Text[0], EM_REPLACESEL, 0, (LPARAM)buffer);
		SendMessage(Text[0], EM_REPLACESEL, 0, (LPARAM)", ");
		threadCounter[0]++;
		Sleep(500);
	}
	ExitThread(0);
}

DWORD WINAPI thread2(LPVOID)
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	static unsigned long long sequence;
	while (true) {
		if (PeekMessage(&msg, NULL, WM_QUIT, WM_QUIT, PM_REMOVE))
			break;

		char buffer[20] = { 0 };
		int EditTextlen = GetWindowTextLength(Text[0]);
		wsprintf(buffer, "%i", Fibonacci_nums(sequence++));

		SendMessage(Text[0], EM_SETSEL, EditTextlen, EditTextlen);
		SendMessage(Text[1], EM_REPLACESEL, 0, (LPARAM)buffer);
		SendMessage(Text[1], EM_REPLACESEL, 0, (LPARAM)", ");
		threadCounter[1]++;
		Sleep(1500);
	}
	return 0;
}

DWORD WINAPI thread3(LPVOID hdc)
{
	SetBkColor((HDC)hdc, RGB(255, 255, 255));
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	srand(time(NULL));
	while (true) {
		if (PeekMessage(&msg, NULL, WM_QUIT, WM_QUIT, PM_REMOVE))
			break;

		RECT rt;
		rt.top = 250 + rand() % 500;
		rt.left = 0 + rand() % 250;
		rt.right = 0 + rand() % 250;
		rt.bottom = 250 + rand() % 500;
		FillRect((HDC)hdc, &rt, HBRUSH(CreateSolidBrush(RGB(rand(), rand(), rand()))));
		threadCounter[2]++;
		Sleep(1000);
	}
	return 0;
}

DWORD WINAPI thread4(LPVOID)
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	while (true) {
		if (PeekMessage(&msg, NULL, WM_QUIT, WM_QUIT, PM_REMOVE))
			break;
		std::string buffer;

		for (int i = 0; i < 3; i++) {
			char buff[20] = { 0 };
			wsprintf(buff, "%i", i + 1);
			buffer += buff;
			buffer += " поток вызван  - ";
			wsprintf(buff, "%i", threadCounter[i]);
			buffer += buff;
			buffer += '\n';
		}
		SetWindowText(Text[2], buffer.c_str());
		Sleep(500);
	}
	return 0;
}

void closeProgram(HWND hWnd, DWORD _exitCode) {
	if (_exitCode != STILL_ACTIVE)
		TerminateProcess(pi.hProcess, -1);

	ThreadStop();
	ShowWindow(hWnd, SW_HIDE);
}

void ReadFromFile(HWND ListBox, HWND VScroll, HWND hWnd, char * fileName, bool bytes) {
	//инициализация OpenFileDialog для откртия в бинарном виде и в обычном
	OPENFILENAME ofn;       // Диалоговое окно открытия файла
	if (bytes)
		InitOpenDialog(ofn, hWnd, "All file (*)\0*.*\0", fileName);
	else
		InitOpenDialog(ofn, hWnd, "Text file (.txt)\0*.txt\0", fileName);

	GetOpenFileName(&ofn);// открытие openFileDialog
	SendMessage(ListBox, LB_RESETCONTENT, 0, 0); //очищяет listbox
	DWORD NumOfReadByte;//Кол-во прочитаных байтов, если 0 то уже конец файла
	HANDLE myFile = CreateFile(
		fileName, //имя файла
		GENERIC_READ,  //в режим чтения GENERIC_WRITE то в запись 
		FILE_SHARE_READ, NULL,
		OPEN_EXISTING, //открыаем УЖЕ СУЩЕСТВУЮЩИЙ файл
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	int size = 0;
	char buff[100];
	if (myFile != INVALID_HANDLE_VALUE)
	{
		do //пока не конец файла
		{
			ReadFile(myFile, buff, 99, &NumOfReadByte, NULL);
			if (!NumOfReadByte)
				break; //выход из цикла

			SendMessage(ListBox, LB_ADDSTRING, 0, (LPARAM)buff);//добавить строку в listbox
			buff[0] = 0;
			size++;
		} while (NumOfReadByte);
	}
	SetScrollRange(VScroll, SB_CTL, 0, size * 20, TRUE);
	CloseHandle(myFile); //закрыть дискрептор в данном случае для файла.
}
