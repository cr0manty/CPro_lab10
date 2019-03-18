#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>     
#include <ctime>
#include <string>
#include "resource.h"
#include "OpenLab.h"
#pragma comment(lib, "Rectangle_paint.lib")
#pragma comment(lib, "Fibon_fact.lib")

static NOTIFYICONDATA tray;
static STARTUPINFO si;
static PROCESS_INFORMATION pi;
static DWORD threadID[4];
static unsigned int threadCounter[3];
static char fileName[MAX_PATH];
static OPENFILENAME ofn;   
static char new_file_name[36];

BOOL CALLBACK DlgExitAnswer(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgPloc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgAdditional(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK CreateMyNewFile(HWND, UINT, WPARAM, LPARAM);

void trayInit(HWND, NOTIFYICONDATA &);
BOOL InitOpenDialog(HWND, const char *);
DWORD WINAPI thread1(LPVOID);
DWORD WINAPI thread2(LPVOID);
DWORD WINAPI thread3(LPVOID);
DWORD WINAPI thread4(LPVOID);
unsigned long long Fibonacci_nums(unsigned long long n);
void ReadFromFile(HWND, HWND, bool = false);
void ThreadStart(HWND, HWND*);
void ThreadStop();
void closeProgram(HWND, DWORD);

extern "C" __declspec(dllimport) void rectangle_paint(HDC &, POINT);
extern "C" __declspec(dllimport) long long factorial(int);
extern "C" __declspec(dllimport) long long fibonach(int);
BOOL InitOpenDialog(HWND);
void CreateNewFile(HWND);
void OpenFile(HWND, HWND);
void SaveFile(HWND);
void DeleteMyFile(HWND);
bool tchar_strcmp(TCHAR*, TCHAR*);
int _strlen(const char *);
void _strcpy(char *, const char *);
void _strcat(char *, const char *);
bool _strcmp(const char *, const char *);
void print(HDC &, POINT, int, int, int);
char * asm_print(int);

BOOL CALLBACK INFODLG(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK MAINFUNC(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK LAB1(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK LAB2(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK LAB3(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK LAB4(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK LAB5(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK LAB6(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK LAB7(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK LAB8(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK LAB9(HWND, UINT, WPARAM, LPARAM);
