#include "include.h"

BOOL InitOpenDialog(HWND hWnd)
{
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = fileName;
	ofn.nMaxFile = sizeof(fileName);
	ofn.lpstrFilter = "Text file(.txt)\0 * .txt\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	return TRUE;
}

BOOL CALLBACK CreateMyNewFile(HWND hDlg, UINT msg, WPARAM wParm, LPARAM lParam) {
	switch (msg)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		if (LOWORD(wParm) == IDOK) {
			HWND hEdit = GetDlgItem(hDlg, IDC_EDIT1);
			SendMessage(hEdit, WM_GETTEXT, (WPARAM)31, (LPARAM)new_file_name);
			strcat(new_file_name, ".txt");
			EndDialog(hDlg, LOWORD(wParm));
			return TRUE;
		}
		else if (LOWORD(wParm) == IDCANCEL) {
			EndDialog(hDlg, LOWORD(wParm));
			return TRUE;
		}
	}
	return FALSE;
}

void SaveFile(HWND hWnd)
{
	InitOpenDialog(hWnd);
	if (!GetSaveFileName(&ofn))
		return;

	if (!strstr(fileName, ".txt"))
		strcat(fileName, ".txt");
	HANDLE myFile = CreateFile(fileName, GENERIC_WRITE,
		FILE_SHARE_WRITE,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	int len = SendDlgItemMessage(hWnd, ID_EDIT3, WM_GETTEXTLENGTH, 0, 0);

	char *buffer = new char[len + 1];
	GetDlgItemText(hWnd, ID_EDIT3, buffer, len + 1);
	buffer[len] = '\0';
	WriteFile(myFile, buffer, len, NULL, NULL);

	CloseHandle(myFile);
	delete[] buffer;
}

void DeleteMyFile(HWND hWnd)
{
	char const *pSearchMask = "*.txt";
	WIN32_FIND_DATA file;
	HANDLE hFind;
	char *to_delete;
	FILETIME ft;
	if (hFind = FindFirstFile(pSearchMask, &file)) {
		to_delete = new char[100];
		ft = file.ftCreationTime;
		strcpy(to_delete, file.cFileName);
		do {
			if ((0 == (file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) &&
				(0 == (file.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT)))
				if (CompareFileTime(&ft, &file.ftCreationTime) == -1) {
					ft = file.ftCreationTime;
					strcpy(to_delete, file.cFileName);
				}
		} while (FALSE != FindNextFile(hFind, &file));

		FindClose(hFind);
		DeleteFile(to_delete);
		MessageBox(hWnd, "Файл был успешно удален!", to_delete, MB_OK);
		delete[] to_delete;
		return;
	}
	MessageBox(hWnd, "Подходящих файлов не было найдено!", "Error", MB_OK);
}

void OpenFile(HWND hWnd, HWND Edit) 
{
	InitOpenDialog(hWnd);
	if(!GetOpenFileName(&ofn))
		return;

	SendMessageA(Edit, WM_SETTEXT, WPARAM(0), LPARAM(""));
	HANDLE myFile = CreateFile(fileName, GENERIC_READ, FILE_SHARE_READ, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (myFile != INVALID_HANDLE_VALUE) {
		int len = GetFileSize(myFile, NULL);
		char *buffer = new char[len + 1];
		ReadFile(myFile, buffer, len, NULL, NULL);
		buffer[len] = '\0';
		SendMessage(Edit, EM_REPLACESEL, 0, (LPARAM)buffer);
		delete[] buffer;
	}
	CloseHandle(myFile);
}

void CreateNewFile(HWND hWnd)
{

	DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG1), hWnd, (DLGPROC)CreateMyNewFile);
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	if (hFind = FindFirstFile(new_file_name, &FindFileData)) {
		do {
			if (tchar_strcmp(FindFileData.cFileName, new_file_name)) {
				MessageBox(hWnd, "Такой файл уже существует!", "Error", MB_OK);
				FindClose(hFind);
				return;
			}
		} while (FindNextFile(hFind, &FindFileData) != 0);
		FindClose(hFind);
	}
	CreateFile(new_file_name, NULL, NULL, NULL, CREATE_NEW, NULL, NULL);
}

bool tchar_strcmp(TCHAR *_first, TCHAR *_second)
{
	while (*_first != '\0' || *_second != '\0')
		if (*_first++ != *_second++)
			return false;

	return true;
}

void print(HDC & _hdc, POINT _point, int _eax, int _edx, const char * _type)
{
	char * buffer = new char[20];
	TextOut(_hdc, _point.x, _point.y, buffer, wsprintf(buffer, _type));
	TextOut(_hdc, _point.x, _point.y + 20, buffer, wsprintf(buffer, "EAX - %d", _eax));
	TextOut(_hdc, _point.x, _point.y + 40, buffer, wsprintf(buffer, "EDX - %d", _edx));

	delete[] buffer;
}

int _strlen(const char * _string)
{
	int len = 0;
	_asm {
		mov edi, _string
		xor eax, eax
		dec eax
		strln :
		inc eax
			cmp byte ptr[eax + edi], 0
			jnz strln
			mov len, eax
	}

	return len;
}

void _strcpy(char *_to, const char *_from)
{
	_asm {
		mov esi, _from
		push esi
		call _strlen
		add esp, 4

		mov ecx, eax
		mov edi, _to
		rep movsb
		mov byte ptr[edi], 0
	}
}

void _strcat(char *_to, const char *_from)
{
	_asm {
		cld
		mov esi, _to
		push esi
		call _strlen
		add esp, 4

		mov ecx, eax
		mov edi, _to
		rep movsb

		mov esi, _from
		push esi
		call _strlen
		add esp, 4
		mov ecx, eax
		rep movsb

		mov byte ptr[edi], 0
		mov _to, edi
	}
}

bool _strcmp(const char *_first, const char *_second)
{
	bool comp = 0;
	_asm {
		cld
		mov esi, _first
		mov edi, _second
		call _strlen

		mov ecx, eax
		rep cmpsb
		jnz exit_asm
		mov comp, 1

		exit_asm:
	}

	return comp;
}

