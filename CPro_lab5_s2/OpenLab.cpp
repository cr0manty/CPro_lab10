#include "include.h"

ATOM OpenLab::register_class(const char *_class_name, int _brush)
{
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;	
	wcex.lpfnWndProc = (WNDPROC)func; 
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = NULL;		
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);   
	wcex.hbrBackground = (HBRUSH)GetStockObject(_brush);  
	wcex.lpszMenuName = NULL;	
	wcex.lpszClassName = _class_name;
	wcex.hIconSm = NULL;

	return RegisterClassEx(&wcex); 
}

BOOL OpenLab::init_window(const char *_class_name, const char *_window_name)
{
	hWnd = CreateWindow(_class_name, 
		_window_name, 
		WS_OVERLAPPEDWINDOW,
		size.left,	
		size.top, 
		size.right,
		size.bottom, 
		NULL,	
		menu,    
		NULL, 
		NULL);    

	if (!hWnd) 
	{
		return FALSE;
	}
	ShowWindow(hWnd, SW_NORMAL);	
	UpdateWindow(hWnd);			
	return TRUE;				
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

OpenLab::~OpenLab()
{
	//ShowWindow(hWnd, SW_HIDE);
	DestroyWindow(hWnd);
}
