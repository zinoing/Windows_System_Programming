// KernelObjProb2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <Windows.h>
#include <tchar.h>

int _tmain(int argc, TCHAR* argv[]) {
	DWORD n = 0;
	while (n < 100)
	{
		for (DWORD i = 0; i < 10000; i++)
			for (DWORD i = 0; i < 10000; i++);

		_fputts(_T("KernelObjectProb2.exe \n"));
		n++;
	}
	return 0;
}
