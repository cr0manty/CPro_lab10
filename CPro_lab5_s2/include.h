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
static HWND Text[3];

void ReadFromFile(HWND, HWND, HWND, char*, bool = false);
BOOL CALLBACK DlgExitAnswer(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgPloc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgAdditional(HWND, UINT, WPARAM, LPARAM);
void trayInit(HWND, NOTIFYICONDATA &);
BOOL InitOpenDialog(OPENFILENAME &,HWND hWnd, const char *_type, char*);
DWORD WINAPI thread1(LPVOID);
DWORD WINAPI thread2(LPVOID);
DWORD WINAPI thread3(LPVOID);
DWORD WINAPI thread4(LPVOID);
unsigned long long Fibonacci_nums(unsigned long long n);
void ThreadStart(HWND);
void ThreadStop();
void closeProgram(HWND, DWORD);
extern "C" __declspec(dllimport) void rectangle_paint(HDC &, POINT);
extern "C" __declspec(dllimport) long long factorial(int);
extern "C" __declspec(dllimport) long long fibonach(int);

int _strlen(const char *);
void _strcpy(char *, const char *);
void _strcat(char *, const char *);
bool _strcmp(const char *, const char *);
void print(HDC &, POINT, int, int, const char *);

LRESULT CALLBACK MAINFUNC(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK INFODLG(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK LAB1(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK LAB2(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK LAB3(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK LAB4(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK LAB5(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK LAB6(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK LAB7(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK LAB8(HWND, UINT, WPARAM, LPARAM);
//LRESULT CALLBACK LAB9(HWND, UINT, WPARAM, LPARAM);
