#pragma once
#include <Windows.h>

class OpenLab
{
	WNDPROC func;
	HMENU menu;
	RECT size;
	HWND hWnd;
	WNDCLASSEX wcex;

	ATOM register_class(const char *, int);
	BOOL init_window(const char *, const char *);
public:
	OpenLab(WNDPROC, const char *, const char*, RECT, HMENU, int);
	operator bool() const;
	~OpenLab();
};
