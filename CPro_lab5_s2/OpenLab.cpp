#include "include.h"

ATOM OpenLab::register_class(const char *_class_name, int _brush)
{
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;	// стиль окна
	wcex.lpfnWndProc = (WNDPROC)func; // оконна€ процедура
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = NULL;		// указатель приложени€
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);		// определение иконки
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);    // определение курсора
	wcex.hbrBackground = (HBRUSH)GetStockObject(_brush);   // установка фона
	wcex.lpszMenuName = NULL;		// определение меню
	wcex.lpszClassName = _class_name;	// им€ класса
	wcex.hIconSm = NULL;

	return RegisterClassEx(&wcex); // регистраци€ класса окна
}

BOOL OpenLab::init_window(const char *_class_name, const char *_window_name)
{
	hWnd = CreateWindow(_class_name, // им€ класса окна
		_window_name,   // им€ приложени€
		WS_OVERLAPPEDWINDOW, // стиль окна
		size.left,	// положение по ’
		size.top, 	// положение по Y
		size.right,    // размер по ’
		size.bottom,    // размер по Y
		NULL,	// описатель родительского окна
		menu,       // описатель меню окна
		NULL,  // указатель приложени€
		NULL);     // параметры создани€.

	if (!hWnd) // ≈сли окно не создалось, функци€ возвращает FALSE
	{
		return FALSE;
	}
	ShowWindow(hWnd, SW_NORMAL);		// ѕоказать окно
	UpdateWindow(hWnd);			// ќбновить окно
	return TRUE;				//”спешное завершение функции
}

OpenLab::OpenLab(WNDPROC _func, const char * _class, const char *_window, RECT _rt, HMENU _menu, int _brush) :
	func(_func), menu(_menu), size(_rt)
{
	this->register_class(_class, _brush);
	this->init_window(_class, _window);
}

OpenLab::operator bool() const
{
	return hWnd;
}
