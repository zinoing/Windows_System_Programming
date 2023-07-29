// execption__finally.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <tchar.h>
#include <windows.h>

int _tmain(int argc, TCHAR* argv[]) {
	TCHAR str[2];

	__try {
		_tcscpy(str, _T("ABCDEFGHIJKLMNOPQRSTUVWXYZ~"));
		_tprintf(_T("%s \n"), str);
	}
	__finally {
		_tprintf(_T("__finally block! \n"));
	}

	return 0;
}
