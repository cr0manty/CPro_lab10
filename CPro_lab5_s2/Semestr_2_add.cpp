#include "include.h"

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
	bool cmp = 0;
	_asm {
		cld
		mov esi, _first
		mov edi, _second
		call _strlen

		mov ecx, eax
		rep cmpsb
		jnz exit_asm
		mov cmp, 1

		exit_asm:
	}

	return cmp;
}
